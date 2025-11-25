#pragma once

#include <Arduino.h>
#include <cstdint>

#define DEBUGGING true

#if DEBUGGING == true
    #define debug(x)    Serial.print(x)
    #define debugln(x)  Serial.println(x)
#else
    #define debug(x)
    #define debugln(x)
#endif

namespace cfg {
    constexpr int LOOP_INTERVAL_MS = 10;
    constexpr int LOOP_INTERVAL_TEST_SHORT = 100; 
    constexpr int LOOP_INTERVAL_TEST_LONG = 1000;
    constexpr uint32_t BTN_DEBOUNCE_MS = 50;
    constexpr uint32_t BTN_SHORT_MS = 200;
    constexpr uint32_t BTN_LONG_MS = 1000;

    bool BUTTON_STATE;

}

namespace pins {
    constexpr int RIGHT_BUTTON_PIN = 23; // GPIO23
    constexpr int LED_BUILTIN_PIN = 2;   // GPIO2
}