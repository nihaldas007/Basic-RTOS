#include <Arduino.h>
#include "app_config.h"
#include "oled.h"
#include "button.h"

/// @brief Stack sizes for tasks
constexpr int BUTTON_STACK = 4096;
constexpr int SERIAL_STACK = 4096;
constexpr int DISPLAY_STACK = 8192;

/// @brief Task priorities
constexpr UBaseType_t BUTTON_PRIORITY = 1;
constexpr UBaseType_t SERIAL_PRIORITY = 1;
constexpr UBaseType_t DISPLAY_PRIORITY = 1;

/// @brief Task handles
TaskHandle_t button_t = nullptr;
TaskHandle_t serial_t = nullptr;
TaskHandle_t display_t = nullptr;

/// @brief Setup function
void ButtonTask(void *param);
void SerialTask(void *param);
void displayTask(void *param);

static const int rightButton = 23;        // GPIO23
static const int LED_BUILTIN = 2; // GPIO2
// bool button_check = false;

void setup()
{
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.setRotation(2);
  display.clearDisplay();
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  debugln("======Starup========");
  configASSERT(xTaskCreatePinnedToCore(ButtonTask, "ButtonTask", BUTTON_STACK, 0, BUTTON_PRIORITY, &button_t, 0) == pdPASS);
  delay(50); // Give some time for the listener task to start
  configASSERT(xTaskCreatePinnedToCore(SerialTask, "SerialTask", SERIAL_STACK, 0, SERIAL_PRIORITY, &serial_t, 0) == pdPASS);
  delay(50); // Give some time for the handler task to start
  configASSERT(xTaskCreatePinnedToCore(displayTask, "DisplayTask", DISPLAY_STACK, 0, DISPLAY_PRIORITY, &display_t, 1) == pdPASS);
  delay(50); // Give some time for the display task to start
  debugln("======Setup Done========");
}

void loop()
{
  vTaskDelete(nullptr); // Delete the loop task as it's not needed
}

void SerialTask(void *param)
{
  TickType_t lastWakeTime = xTaskGetTickCount();
  for (;;)
  {
    if (cfg::BUTTON_STATE == true)
      debugln("LED ON"), digitalWrite(LED_BUILTIN, HIGH);
    else if (cfg::BUTTON_STATE == false)
      debugln("LED OFF"), digitalWrite(LED_BUILTIN, LOW);
    vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(cfg::LOOP_INTERVAL_TEST_SHORT));
  }
}