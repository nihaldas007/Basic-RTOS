#pragma once
#include <Arduino.h>

void ButtonTask(void *param)
{
  TickType_t lastWakeTime = xTaskGetTickCount();
  for (;;)
  {
    if (digitalRead(pins::RIGHT_BUTTON_PIN) == LOW)
    {
      cfg::BUTTON_STATE = true;
    }
    else if (digitalRead(pins::RIGHT_BUTTON_PIN) == HIGH)
    {
      cfg::BUTTON_STATE = false;
    }
    vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(cfg::LOOP_INTERVAL_TEST_SHORT));
  }
}