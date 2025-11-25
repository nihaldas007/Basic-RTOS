#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// Define Screen Dimensions
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// Standard ESP32 I2C pins: SDA = GPIO 21, SCL = GPIO 22
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void text(int x, int y, int size, String str);

void displayTask(void *param)
{
    TickType_t lastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        // display.clearDisplay();
        if(cfg::BUTTON_STATE == true)display.clearDisplay(),text(0, 10, 1, "LED_ON");
        else display.clearDisplay(),text(0, 10, 1, "LED_OFF");
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(cfg::LOOP_INTERVAL_TEST_SHORT));
    }
}
void text(int x, int y, int size, String str)
{
    display.setTextSize(size); // Normal 1:1 pixel scale
    display.setTextColor(WHITE);
    display.setCursor(x, y);
    display.println(str);
    display.display();
}