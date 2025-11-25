#include <Arduino.h>


#include "app_config.h"

/// @brief Stack sizes for tasks
constexpr int LISTENER_STACK = 2048;
constexpr int HANDELER_STACK = 4096;

/// @brief Task priorities
constexpr UBaseType_t LISTENER_PRIORITY = 1;
constexpr UBaseType_t HANDLER_PRIORITY = 2;

/// @brief Task handles
TaskHandle_t listener_t = nullptr;
TaskHandle_t handler_t = nullptr;

/// @brief Setup function for Arduino framework
void listenerTask(void *param);
void handlerTask(void *param);



void setup() {
  Serial.begin(115200);

  debugln("======Starup========");
  configASSERT(xTaskCreatePinnedToCore(listenerTask,"ListenerTask",LISTENER_STACK,0,LISTENER_PRIORITY,&listener_t,0) == pdPASS);
  delay(50); // Give some time for the listener task to start
  configASSERT(xTaskCreatePinnedToCore(handlerTask,"HandlerTask",HANDELER_STACK,0,HANDLER_PRIORITY,&handler_t,1) == pdPASS);
  delay(50); // Give some time for the handler task to start  
  debugln("======Setup Done========");
} 

void loop() {
  vTaskDelete(nullptr); // Delete the loop task as it's not needed
}
void listenerTask(void *param) {

  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;){
    debugln("Listener Task Running");
    vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(cfg::LOOP_INTERVAL_TEST_SHORT));
  }
}
void handlerTask(void *param) {
  TickType_t lastWakeTime = xTaskGetTickCount();
  for(;;){
    debugln("Handler Task Running");
    vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(cfg::LOOP_INTERVAL_TEST_SHORT));
  }
}