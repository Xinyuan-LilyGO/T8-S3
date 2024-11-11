/*
 * @Description: Factory testing documents
 * @Author: LILYGO_L
 * @Date: 2023-07-13 09:54:00
 * @LastEditTime: 2024-11-11 16:11:42
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "WiFi.h"
#include "pin_config.h"
#include <HTTPClient.h>

#define WIFI_SSID "xinyuandianzi"
#define WIFI_PASSWORD "AA15994823428"
// #define WIFI_SSID "LilyGo-AABB"
// #define WIFI_PASSWORD "xinyuandianzi"

#define WIFI_CONNECT_WAIT_MAX (30 * 1000)

#define NTP_SERVER1 "pool.ntp.org"
#define NTP_SERVER2 "time.nist.gov"
#define GMT_OFFSET_SEC 8 * 3600 // 时区设置函数，东八区（UTC/GMT+8:00）写成8*3600
#define DAY_LIGHT_OFFSET_SEC 0  // 夏令时填写3600，否则填0

File testFile;

bool SelfLocking_Flag = false;

void SD_Test()
{

    uint8_t cardType = 0;
    uint64_t cardSize = 0;
    uint8_t numSectors = 0;

    if (!SD.begin(SD_CS, SPI, 40000000)) // SD boots
    {
        SelfLocking_Flag = false;

        Serial.println("Detecting SD card");

        Serial.println("SD card initialization failed !");
        delay(100);

        Serial.println(".");
        delay(100);

        Serial.println(".");
        delay(100);

        Serial.println(".");
        delay(100);

        Serial.println(".");
        delay(100);

        Serial.println(".");
        delay(100);

        Serial.println(".");
        delay(100);
    }
    else
    {
        delay(50); // Wait for the SD card

        if (SelfLocking_Flag == false)
        {
            SelfLocking_Flag = true;
            delay(50);
        }

        Serial.println("SD card initialization successful !");
        delay(100);

        cardType = SD.cardType();
        cardSize = SD.cardSize() / (1024 * 1024);
        numSectors = SD.numSectors();
        switch (cardType)
        {
        case CARD_NONE:
            Serial.println("No SD card attached");
            delay(100);

            break;
        case CARD_MMC:
            Serial.print("SD Card Type: ");
            Serial.println("MMC");
            Serial.printf("SD Card Size: %lluMB\n", cardSize);
            delay(100);

            break;
        case CARD_SD:
            Serial.print("SD Card Type: ");
            Serial.println("SDSC");
            Serial.printf("SD Card Size: %lluMB\n", cardSize);
            delay(100);

            break;
        case CARD_SDHC:
            Serial.print("SD Card Type: ");
            Serial.println("SDHC");
            Serial.printf("SD Card Size: %lluMB\n", cardSize);
            delay(100);

            break;
        default:
            Serial.println("UNKNOWN");
            delay(100);

            break;
        }
    }
    SD.end();
}

void printLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println("Get time success");
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S"); // 格式化输出
}

void wifi_test(void)
{
    String text;
    int wifi_num = 0;

    Serial.println("\nScanning wifi");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    wifi_num = WiFi.scanNetworks();
    if (wifi_num == 0)
    {
        text = "\nWiFi scan complete !\nNo wifi discovered.\n";
    }
    else
    {
        text = "\nWiFi scan complete !\n";
        text += wifi_num;
        text += " wifi discovered.\n\n";

        for (int i = 0; i < wifi_num; i++)
        {
            text += (i + 1);
            text += ": ";
            text += WiFi.SSID(i);
            text += " (";
            text += WiFi.RSSI(i);
            text += ")";
            text += (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " \n" : "*\n";
            delay(10);
        }
    }

    Serial.println(text);

    text = "Connecting to ";
    Serial.print("Connecting to ");
    text += WIFI_SSID;
    text += "\n";

    Serial.print(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    uint32_t last_tick = millis();
    uint32_t i = 0;
    bool is_smartconfig_connect = false;

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        text += ".";
        delay(100);

        if (millis() - last_tick > WIFI_CONNECT_WAIT_MAX)
        { /* Automatically start smartconfig when connection times out */
            text += "\nConnection timed out, start smartconfig";

            is_smartconfig_connect = true;
            WiFi.mode(WIFI_AP_STA);
            Serial.println("\r\n wait for smartconfig....");
            text += "\r\n wait for smartconfig....";
            text += "\nPlease use #ff0000 EspTouch# Apps to connect to the distribution network";
            WiFi.beginSmartConfig();

            while (1)
            {
                if (WiFi.smartConfigDone())
                {
                    Serial.println("\r\nSmartConfig Success\r\n");
                    Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
                    Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
                    text += "\nSmartConfig Success";
                    text += "\nSSID:";
                    text += WiFi.SSID().c_str();
                    text += "\nPSW:";
                    text += WiFi.psk().c_str();
                    last_tick = millis();
                    break;
                }
            }
        }
    }

    if (!is_smartconfig_connect)
    {
        text += "\nThe connection was successful ! \nTakes ";
        Serial.print("\nThe connection was successful ! \nTakes ");
        text += millis() - last_tick;
        Serial.print(millis() - last_tick);
        text += " ms\n";
        Serial.println(" ms\n");
    }
}

void setup()
{
    pinMode(Power_Enable_Pin, OUTPUT);
    digitalWrite(Power_Enable_Pin, HIGH);
    Serial.begin(115200);
    Serial.println("Ciallo");

    ledcAttachPin(LED_Pin, 1);
    ledcSetup(1, 2000, 8); // 2 kHz PWM, 8-bit resolution
    ledcWrite(1, 0);       // brightness 0 - 255

    for (int i = 0; i < 20; i++)
    {
        ledcWrite(1, i);
        delay(50);
    }
    for (int i = 20; i > 0; i--)
    {
        ledcWrite(1, i);
        delay(50);
    }

    ledcWrite(1, 0); // brightness 0 - 255

    pinMode(SD_MISO, INPUT_PULLUP);              // MISO pull-up resistor
    SPI.begin(SD_SCLK, SD_MISO, SD_MOSI, SD_CS); // SPI boots

    SD_Test();

    wifi_test();

    // 从网络时间服务器上获取并设置时间
    // 获取成功后芯片会使用RTC时钟保持时间的更新
    configTime(GMT_OFFSET_SEC, DAY_LIGHT_OFFSET_SEC, NTP_SERVER1, NTP_SERVER2);
    printLocalTime();

    // esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1); // 1 = High, 0 = Low
    Serial.println("After 1 seconds, it will enter a deep sleep mode");
    // WiFi.setSleep(1);
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    SPI.end();
    SD.end();
    ledcDetachPin(LED_Pin);
    for (int i = 0; i < GPIO_NUM_MAX; i++)
    {
        digitalWrite(i, LOW);
    }
    delay(1000);
    esp_deep_sleep_start();
    Serial.println("If deep sleep mode has been entered, this message will not be printed");
}
void loop()
{
}