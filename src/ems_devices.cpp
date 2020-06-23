
#include "ems_devices.h"
#include <inttypes.h>

/*
 * Table of all known EMS Devices
 * ProductID, DeviceType, Description, Flags
 */
const _EMS_Device EMS_Devices[] = {

    //
    // UBA Masters - must have device_id of 0x08
    //
    {72, EMS_DEVICE_TYPE_BOILER, "MC10 Module", EMS_DEVICE_FLAG_NONE},
    {123, EMS_DEVICE_TYPE_BOILER, "Buderus GBx72/Nefit Trendline/Junkers Cerapur/Worcester Greenstar Si/27i", EMS_DEVICE_FLAG_NONE},
    {133, EMS_DEVICE_TYPE_BOILER, "Buderus GB125/Logamatic MC110", EMS_DEVICE_FLAG_NONE},
    {115, EMS_DEVICE_TYPE_BOILER, "Nefit Topline/Buderus GB162", EMS_DEVICE_FLAG_NONE},
    {203, EMS_DEVICE_TYPE_BOILER, "Buderus Logamax U122/Junkers Cerapur", EMS_DEVICE_FLAG_NONE},
    {208, EMS_DEVICE_TYPE_BOILER, "Buderus Logamax plus/GB192/Bosch Condens GC9000", EMS_DEVICE_FLAG_NONE},
    {64, EMS_DEVICE_TYPE_BOILER, "Sieger BK13,BK15/Nefit Smartline/Buderus GB1x2", EMS_DEVICE_FLAG_NONE},
    {234, EMS_DEVICE_TYPE_BOILER, "Buderus Logamax Plus GB122", EMS_DEVICE_FLAG_NONE},
    {84, EMS_DEVICE_TYPE_BOILER, "Buderus Logamax Plus GB022", EMS_DEVICE_FLAG_NONE},
    {95, EMS_DEVICE_TYPE_BOILER, "Bosch Condens 2500/Buderus Logamax,Logomatic/Junkers Cerapur Top/Worcester Greenstar i/Generic HT3", EMS_DEVICE_FLAG_NONE},
    {122, EMS_DEVICE_TYPE_BOILER, "Nefit Proline", EMS_DEVICE_FLAG_NONE},
    {170, EMS_DEVICE_TYPE_BOILER, "Buderus Logano GB212", EMS_DEVICE_FLAG_NONE},
    {172, EMS_DEVICE_TYPE_BOILER, "Nefit Enviline", EMS_DEVICE_FLAG_NONE},

    //
    // Solar Modules - type 0x30
    //
    {73, EMS_DEVICE_TYPE_SOLAR, "SM10 Solar Module", EMS_DEVICE_FLAG_SM10},
    {163, EMS_DEVICE_TYPE_SOLAR, "SM100 Solar Module", EMS_DEVICE_FLAG_SM100},
    {164, EMS_DEVICE_TYPE_SOLAR, "SM200 Solar Module", EMS_DEVICE_FLAG_SM100},
    {101, EMS_DEVICE_TYPE_SOLAR, "Junkers ISM1 Solar Module", EMS_DEVICE_FLAG_SM100},
    {162, EMS_DEVICE_TYPE_SOLAR, "SM50 Solar Module", EMS_DEVICE_FLAG_SM100},

    //
    // Mixing Devices - type 0x20 or 0x21
    //
    {160, EMS_DEVICE_TYPE_MIXING, "MM100 Mixing Module", EMS_DEVICE_FLAG_MMPLUS},
    {161, EMS_DEVICE_TYPE_MIXING, "MM200 Mixing Module", EMS_DEVICE_FLAG_MMPLUS},
    {69, EMS_DEVICE_TYPE_MIXING, "MM10 Mixing Module", EMS_DEVICE_FLAG_MM10},
    {159, EMS_DEVICE_TYPE_MIXING, "MM50 Mixing Module", EMS_DEVICE_FLAG_MMPLUS},

    //
    // HeatPump - type 0x38
    //
    {252, EMS_DEVICE_TYPE_HEATPUMP, "HeatPump Module", EMS_DEVICE_FLAG_NONE},
    {200, EMS_DEVICE_TYPE_HEATPUMP, "HeatPump Module", EMS_DEVICE_FLAG_NONE},

    //
    // Other devices like controllers and modems
    // such as 0x11 for Switching, 0x09 for controllers, 0x02 for Connect, 0x48 for Gateway
    //
    {71, EMS_DEVICE_TYPE_SWITCH, "WM10 Switch Module", EMS_DEVICE_FLAG_NONE},                                   // 0x11
    {68, EMS_DEVICE_TYPE_CONTROLLER, "BC10/RFM20 Receiver", EMS_DEVICE_FLAG_NONE},                              // 0x09
    {218, EMS_DEVICE_TYPE_CONTROLLER, "Junkers M200/Buderus RFM200 Receiver", EMS_DEVICE_FLAG_NONE},            // 0x50
    {190, EMS_DEVICE_TYPE_CONTROLLER, "BC10 Base Controller", EMS_DEVICE_FLAG_NONE},                            // 0x09
    {114, EMS_DEVICE_TYPE_CONTROLLER, "BC10 Base Controller", EMS_DEVICE_FLAG_NONE},                            // 0x09
    {125, EMS_DEVICE_TYPE_CONTROLLER, "BC25 Base Controller", EMS_DEVICE_FLAG_NONE},                            // 0x09
    {169, EMS_DEVICE_TYPE_CONTROLLER, "BC40 Base Controller", EMS_DEVICE_FLAG_NONE},                            // 0x09
    {152, EMS_DEVICE_TYPE_CONTROLLER, "Controller", EMS_DEVICE_FLAG_NONE},                                      // 0x09
    {95, EMS_DEVICE_TYPE_CONTROLLER, "HT3 Controller", EMS_DEVICE_FLAG_NONE},                                   // 0x09
    {209, EMS_DEVICE_TYPE_CONTROLLER, "W-B ErP Boiler Control Panel", EMS_DEVICE_FLAG_NONE},                    // 0x09
    {230, EMS_DEVICE_TYPE_CONTROLLER, "BC Base Controller", EMS_DEVICE_FLAG_NONE},                              // 0x09
    {205, EMS_DEVICE_TYPE_CONNECT, "Nefit Moduline Easy Connect", EMS_DEVICE_FLAG_NONE},                        // 0x02
    {206, EMS_DEVICE_TYPE_CONNECT, "Bosch Easy Connect", EMS_DEVICE_FLAG_NONE},                                 // 0x02
    {171, EMS_DEVICE_TYPE_CONNECT, "EMS-OT OpenTherm converter", EMS_DEVICE_FLAG_NONE},                         // 0x02
    {189, EMS_DEVICE_TYPE_GATEWAY, "Web Gateway KM200", EMS_DEVICE_FLAG_NONE},                                  // 0x48
    {94, EMS_DEVICE_TYPE_GATEWAY, "RC Remote Device", EMS_DEVICE_FLAG_NONE},                                    // 0x18
    {207, EMS_DEVICE_TYPE_CONTROLLER, "Worcester Sense II/Bosch CS200 Solar Controller", EMS_DEVICE_FLAG_NONE}, // 0x10

    //
    // Thermostats, typically device id of 0x10, 0x17, 0x18, 0x38 (RC100), 0x39 (Easy)
    //

    // Easy devices - not currently supporting write operations
    {202, EMS_DEVICE_TYPE_THERMOSTAT, "Logamatic TC100/Nefit Moduline Easy", EMS_DEVICE_FLAG_EASY | EMS_DEVICE_FLAG_NO_WRITE}, // 0x18, cannot write
    {203, EMS_DEVICE_TYPE_THERMOSTAT, "Bosch EasyControl CT200", EMS_DEVICE_FLAG_EASY | EMS_DEVICE_FLAG_NO_WRITE},             // 0x18, cannot write
    {157, EMS_DEVICE_TYPE_THERMOSTAT, "Buderus RC200/Bosch CW100/Junkers CW100", EMS_DEVICE_FLAG_NO_WRITE},                    // 0x18, cannot write

    // Buderus/Nefit specific
    {79, EMS_DEVICE_TYPE_THERMOSTAT, "RC10/Moduline 100", EMS_DEVICE_FLAG_RC10},                                    // 0x17
    {80, EMS_DEVICE_TYPE_THERMOSTAT, "Moduline 200", EMS_DEVICE_FLAG_RC10},                                         // 0x17
    {77, EMS_DEVICE_TYPE_THERMOSTAT, "RC20/Moduline 300", EMS_DEVICE_FLAG_RC20},                                    // 0x17
    {67, EMS_DEVICE_TYPE_THERMOSTAT, "RC30", EMS_DEVICE_FLAG_RC30N},                                                // 0x10 - based on RC35
    {78, EMS_DEVICE_TYPE_THERMOSTAT, "Moduline 400", EMS_DEVICE_FLAG_RC30},                                         // 0x10
    {86, EMS_DEVICE_TYPE_THERMOSTAT, "RC35", EMS_DEVICE_FLAG_RC35},                                                 // 0x10
    {93, EMS_DEVICE_TYPE_THERMOSTAT, "RC20RF", EMS_DEVICE_FLAG_RC20},                                               // 0x19
    {158, EMS_DEVICE_TYPE_THERMOSTAT, "RC300/RC310/Moduline 3000/Bosch CW400/W-B Sense II", EMS_DEVICE_FLAG_RC300}, // 0x10
    {165, EMS_DEVICE_TYPE_THERMOSTAT, "RC100/Moduline 1000/1010", EMS_DEVICE_FLAG_RC100},                           // 0x18, 0x38

    // Sieger
    {76, EMS_DEVICE_TYPE_THERMOSTAT, "Sieger ES73", EMS_DEVICE_FLAG_RC35},                // 0x10
    {113, EMS_DEVICE_TYPE_THERMOSTAT, "Sieger ES72/Buderus RC20", EMS_DEVICE_FLAG_RC20N}, // 0x17

    // Junkers - all 0x10
    {105, EMS_DEVICE_TYPE_THERMOSTAT, "Junkers FW100", EMS_DEVICE_FLAG_JUNKERS1}, // 0x10
    {106, EMS_DEVICE_TYPE_THERMOSTAT, "Junkers FW200", EMS_DEVICE_FLAG_JUNKERS1}, // 0x10
    {107, EMS_DEVICE_TYPE_THERMOSTAT, "Junkers FR100", EMS_DEVICE_FLAG_JUNKERS2}, // 0x10
    {108, EMS_DEVICE_TYPE_THERMOSTAT, "Junkers FR110", EMS_DEVICE_FLAG_JUNKERS2}, // 0x10
    {111, EMS_DEVICE_TYPE_THERMOSTAT, "Junkers FR10", EMS_DEVICE_FLAG_JUNKERS1},  // 0x10
    {147, EMS_DEVICE_TYPE_THERMOSTAT, "Junkers FR50", EMS_DEVICE_FLAG_JUNKERS1},  // 0x10
    {191, EMS_DEVICE_TYPE_THERMOSTAT, "Junkers FR120", EMS_DEVICE_FLAG_JUNKERS1}, // 0x10
    {192, EMS_DEVICE_TYPE_THERMOSTAT, "Junkers FW120", EMS_DEVICE_FLAG_JUNKERS1}  // 0x10


};

uint8_t _EMS_Devices_max       = sizeof(EMS_Devices) / sizeof(_EMS_Device);

