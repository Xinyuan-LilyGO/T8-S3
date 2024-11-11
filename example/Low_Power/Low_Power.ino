/*
 * @Description: After 5 seconds, it will enter a deep sleep mode
 * @Author: LILYGO_L
 * @Date: 2023-08-18 15:26:31
 * @LastEditTime: 2024-11-11 16:11:36
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "pin_config.h"

#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex

RTC_DATA_ATTR int bootCount = 0;

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/
void print_wakeup_reason()
{
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason)
    {
    case 1:
        Serial.println("Wakeup caused by external signal using RTC_IO");
        break;
    case 2:
        Serial.println("Wakeup caused by external signal using RTC_CNTL");
        break;
    case 3:
        Serial.println("Wakeup caused by timer");
        break;
    case 4:
        Serial.println("Wakeup caused by touchpad");
        break;
    case 5:
        Serial.println("Wakeup caused by ULP program");
        break;
    default:
        Serial.println("Wakeup was not caused by deep sleep");
        break;
    }
}

void setup()
{
    pinMode(Power_Enable_Pin, OUTPUT); // Power Enable
    digitalWrite(Power_Enable_Pin, HIGH);

    Serial.begin(115200);
    delay(1000); // Take some time to open up the Serial Monitor

    // Increment boot number and  print it every reboot
    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));

    Serial.printf("Boot number: %d ", bootCount);

    // Print the wakeup reason for ESP32
    print_wakeup_reason();

    // ext0 wake-up
    // pinMode(GPIO_NUM_2, OUTPUT); // Power Enable
    // digitalWrite(GPIO_NUM_2, HIGH);
    // esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 0); // 1 = High, 0 = Low

    // If you were to use ext1, you would use it like
    // esp_sleep_enable_ext1_wakeup(,);

    // After 10 seconds, it will enter a deep sleep mode
    Serial.println("After 5 seconds, it will enter a deep sleep mode");
    for (int i = 0; i < GPIO_NUM_MAX; i++)
    {
        digitalWrite(i, LOW);
    }
    delay(5000);
    esp_deep_sleep_start();
    Serial.println("If deep sleep mode has been entered, this message will not be printed");
}

void loop()
{
    // This is not going to be called
}
