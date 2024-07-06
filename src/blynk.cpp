#include "MyESP.h"
#define BLYNK_TEMPLATE_ID "TMPLl0hKFgR-"
#define BLYNK_TEMPLATE_NAME "EMS ESP"
#define BLYNK_PRINT myESP.getDebugStream()
#define BLYNK_NO_BUILTIN // Blynk doesn't handle pins
#include <BlynkSimpleEsp8266.h>
#include "ems.h"

#define BOILER_TEMP_WIDGET V0
#define SEL_FLOW_TEMP_WIDGET V1
//#define CUR_FLOW_TEMP_WIFGET V2
#define WARM_WATER_TEMP_WIDGET V3
#define RETURN_TEMP_WIDGET V4
#define PRESURE_WIDGET V5
//#define FLAME_CURRENT_WIDGET V6
#define BURNER_POWER_WIDGET V7
//#define GAS_VALVE_WIDGET V8
#define WW_VALVE_WIDGET V9
#define ACTIVE_WIDGET V10
#define WW_ONETIME_BUTTON V31
#define MONITOR_BUTTON V13

const unsigned long PUSH_LONG_INTERVAL = 900000; // 15 minutes
const unsigned long PUSH_SHORT_INTERVAL = 60000; // 1 minute

const unsigned long MONITOR_INTERVAL = 60000 * 60 * 3; // 3 hours
const unsigned long PUSH_MONITOR_INTERVAL = 15000; // 15 seconds

bool initialized = false;
unsigned long previousMillis = 0;
unsigned long lastHeatingActiveMillis = 0;

unsigned long blynkMonitorStart = 0;

BLYNK_CONNECTED() {
  Blynk.syncVirtual(MONITOR_BUTTON);
}

BLYNK_WRITE(MONITOR_BUTTON) {
  blynkMonitorStart = param.asInt() ? millis() : 0;
}

BLYNK_WRITE(WW_ONETIME_BUTTON) {
  ems_setWarmWaterOnetime(param.asInt());
}

void blynkSetup(const char* authKey) {
  Blynk.config(authKey);
  initialized = true;
}

void blynkLoop() {
  if (!initialized)
    return;

  unsigned long currentMillis = millis();

  if (blynkMonitorStart && currentMillis - blynkMonitorStart > MONITOR_INTERVAL) {
    blynkMonitorStart = 0;
  }

  if (EMS_Boiler.heatingActive) {
    lastHeatingActiveMillis = currentMillis;
  }

  unsigned long interval;
  if (blynkMonitorStart) {
    interval = PUSH_MONITOR_INTERVAL;
  } else if (currentMillis - lastHeatingActiveMillis < PUSH_LONG_INTERVAL) {
    interval = PUSH_SHORT_INTERVAL;
  } else {
    interval = PUSH_LONG_INTERVAL;
  }

  if (currentMillis - previousMillis >= interval || !previousMillis) {
    previousMillis = currentMillis;

    Blynk.beginGroup();
    Blynk.virtualWrite(BOILER_TEMP_WIDGET, (float) EMS_Boiler.boilTemp / 10.0);
    Blynk.virtualWrite(SEL_FLOW_TEMP_WIDGET, EMS_Boiler.selFlowTemp);
//    Blynk.virtualWrite(CUR_FLOW_TEMP_WIFGET, (float) EMS_Boiler.curFlowTemp / 10.0);
    Blynk.virtualWrite(WARM_WATER_TEMP_WIDGET, (float) EMS_Boiler.wWCurTmp / 10.0);
    Blynk.virtualWrite(RETURN_TEMP_WIDGET, (float) EMS_Boiler.retTemp / 10.0);
    Blynk.virtualWrite(PRESURE_WIDGET, (float) EMS_Boiler.sysPress / 10.0);
//    Blynk.virtualWrite(FLAME_CURRENT_WIDGET, (float) EMS_Boiler.flameCurr / 10.0);
    Blynk.virtualWrite(BURNER_POWER_WIDGET, EMS_Boiler.curBurnPow);
//    Blynk.virtualWrite(GAS_VALVE_WIDGET, EMS_Boiler.burnGas ? 0Xff: 0);
    Blynk.virtualWrite(WW_VALVE_WIDGET, EMS_Boiler.wWHeat ? 0Xff: 0);
    Blynk.virtualWrite(ACTIVE_WIDGET, EMS_Boiler.heatingActive ? 0Xff: 0);
    Blynk.virtualWrite(WW_ONETIME_BUTTON, EMS_Boiler.wWOneTime);
    Blynk.virtualWrite(MONITOR_BUTTON, blynkMonitorStart ? 0xFF : 0);
    Blynk.endGroup();
  }
  Blynk.run();
}
