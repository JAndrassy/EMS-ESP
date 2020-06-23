#include "MyESP.h"
#define BLYNK_PRINT myESP.getDebugStream()
#define BLYNK_NO_BUILTIN // Blynk doesn't handle pins
#include <BlynkSimpleEsp8266.h>
#include "ems.h"

#define BOILER_TEMP_WIDGET V0
#define SEL_FLOW_TEMP_WIDGET V1
#define CUR_FLOW_TEMP_WIFGET V2
#define WARM_WATER_TEMP_WIDGET V3
#define RETURN_TEMP_WIDGET V4
#define PRESURE_WIDGET V5
#define FLAME_CURRENT_WIDGET V6
#define BURNER_POWER_WIDGET V7
#define GAS_VALVE_WIDGET V8
#define WW_VALVE_WIDGET V9
#define ACTIVE_WIDGET V10
#define WW_ONETIME_BUTTON V31

const unsigned long PUSH_LONG_INTERVAL = 900000; // 15 minutes
const unsigned long PUSH_SHORT_INTERVAL = 60000; // 1 minute

bool initialized = false;
unsigned long previousMillis = 0;
unsigned long nextInterval = PUSH_LONG_INTERVAL;
bool oneMoreShortInterval;

BLYNK_WRITE(WW_ONETIME_BUTTON) {
  ems_setWarmWaterOnetime(param.asInt());
}

void blynkSetup(const char* authKey) {
  Blynk.config(authKey, BLYNK_DEFAULT_DOMAIN, BLYNK_DEFAULT_PORT);
  initialized = true;
}

void blynkLoop() {
  if (!initialized)
    return;

  unsigned long currentMillis = millis();

  unsigned long interval = (EMS_Boiler.heatingActive || oneMoreShortInterval) ? PUSH_SHORT_INTERVAL : nextInterval;

  if (currentMillis - previousMillis >= interval || !previousMillis) {
    previousMillis = currentMillis;
    oneMoreShortInterval = EMS_Boiler.heatingActive;

    Blynk.virtualWrite(BOILER_TEMP_WIDGET, (float) EMS_Boiler.boilTemp / 10.0);
    Blynk.virtualWrite(SEL_FLOW_TEMP_WIDGET, EMS_Boiler.selFlowTemp);
    Blynk.virtualWrite(CUR_FLOW_TEMP_WIFGET, (float) EMS_Boiler.curFlowTemp / 10.0);
    Blynk.virtualWrite(WARM_WATER_TEMP_WIDGET, (float) EMS_Boiler.wWCurTmp / 10.0);
    Blynk.virtualWrite(RETURN_TEMP_WIDGET, (float) EMS_Boiler.retTemp / 10.0);
    Blynk.virtualWrite(PRESURE_WIDGET, (float) EMS_Boiler.sysPress / 10.0);
    Blynk.virtualWrite(FLAME_CURRENT_WIDGET, (float) EMS_Boiler.flameCurr / 10.0);
    Blynk.virtualWrite(BURNER_POWER_WIDGET, EMS_Boiler.curBurnPow);
    Blynk.virtualWrite(GAS_VALVE_WIDGET, EMS_Boiler.burnGas ? 0Xff: 0);
    Blynk.virtualWrite(WW_VALVE_WIDGET, EMS_Boiler.wWHeat ? 0Xff: 0);
    Blynk.virtualWrite(ACTIVE_WIDGET, EMS_Boiler.heatingActive ? 0Xff: 0);
    Blynk.virtualWrite(WW_ONETIME_BUTTON, EMS_Boiler.wWOneTime);
  }
  nextInterval = EMS_Boiler.heatingActive ? PUSH_SHORT_INTERVAL : PUSH_LONG_INTERVAL;
  Blynk.run();
}
