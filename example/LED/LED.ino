/*
 * @Description: LED brightness changes from dark to bright and then from
 *                      bright to dark
 * @Author: LILYGO_L
 * @Date: 2023-08-18 15:35:51
 * @LastEditTime: 2024-11-11 16:11:25
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "pin_config.h"

void setup()
{
    pinMode(Power_Enable_Pin, OUTPUT); // Power Enable
    digitalWrite(Power_Enable_Pin, HIGH);

    Serial.begin(115200);

    ledcAttachPin(LED_Pin, 1); // assign TFT_BL pin to channel 1
    ledcSetup(1, 2000, 8);     // 2 kHz PWM, 8-bit resolution
    ledcWrite(1, 0);           // brightness 0 - 255
}

void loop()
{
    for (int i = 0; i < 100; i++)
    {
        ledcWrite(1, i);
        delay(50);
    }
    for (int i = 100; i > 0; i--)
    {
        ledcWrite(1, i);
        delay(50);
    }
}