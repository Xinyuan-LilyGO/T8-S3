<!--
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-08-18 15:58:58
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-08-18 18:07:49
 * @License: GPL 3.0
-->
<h1 align = "center">🌟LILYGO T8 ESP32-S3🌟</h1>

## **English | [中文](./README_CN.MD)**

<h3 align = "left">Quick start:</h3>

**USE PlatformIO**

1. Install[VSCODE](https://code.visualstudio.com/)and[Python](https://www.python.org/)
2. Search for the PlatformIO plug-in in the VSCODE extension and install it.
3. After the installation is complete and the reload is completed, there will be a small house icon in the lower left corner. Click to display the Platformio IDE home page。
4. Uncomment "default_envs=xxx" in the platformio.ini file to select the program to burn.
5. Go to file - > Open folder - > Select the T8-S3 folder and click the (√) symbol in the lower left corner to compile (→) for upload.

**USE Arduino IDE**

1. Install the current upstream Arduino IDE at the 1.8 level or later. The current version is at the [Arduino website](http://www.arduino.cc/en/main/software).
2. Start Arduino and open Preferences window. In additional board manager add url: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json .separating them with commas.
3. Select Tools -> Board -> dfrobot_firebeetle2_esp32s3.
4. Arduino users need to move all files in lib, along with folders, to the library file directory in the Arduino IDE. The default path is as shown in the figure.
![](image/Arduino_user_readme_01.png)
![](image/Arduino_user_readme_02.png)

**USE Micropython**

1. [Download and upload the firmware]()
2. Note that the firmware upload address is 0x0, not 0x1000.

<h3 align = "left">Product 📷:</h3>

| Product |                            Product  Link                            |
| :-----: | :-----------------------------------------------------------------: |
|  T8-S3  | [AliExpress]() |

## Pinout

![](image/T8-S3_V1.0.jpg)








