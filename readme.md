//https://lastminuteengineers.com/getting-started-with-esp32-cam/
//https://github.com/MateKingGamer/ESP-32-CAM-to-ESP-32-TFT-DISPLAY/tree/main

//How to Fix the Serial Monitor in Arduino IDE for ESP32-C3
To enable the USB CDC On Boot option, follow these steps in the Arduino IDE:
Open the "Tools" menu.
Scroll down to the "USB CDC On Boot" option.
Click on it and select "Enabled" from the submenu.
Re-upload your sketch to the board.


//ESP32-C3-Super Mini Pinout - Can define its own SDA and SCL. Built-in LED = 8
***************************
*Left            Right:   *
***************************
*5 A5 MISO       5V       *
*6    MOSI       GND      *
*7    SS         3V3      *
*8    SDA        4 A4 SCK *
*9    SCL        3 A3     *
*10              2 A2     *
*20   RX         1 A1     *
*21   TX         0 A0     *
***************************

// ESP32-C3 SuperMini    1.8" TFT LCD  
================     ============
3.3V  -------------> VCC
GND   -------------> GND
GPIO7 -------------> SDA 
GPIO6 -------------> SCL 
GPIO4 ------------>  DC
GPIO3  ------------> CS
GPIO5  ------------> RES
3.3V  ------------> BLK

### Dual WS2812B LED Rings (48 LEDs Chained)
| LED Pad | Connection | Notes |
| :--- | :--- | :--- |
| **Ring 1 `DI`** | `GPIO 2` | Place a $330\ \Omega$ resistor in series |
| **Ring 1 `DO`** | `Ring 2 DI` | Chains pixels `0–23` into `24–47` |
| **Both `5V`** | `5V` (`TP4056 OUT+`) | Do **not** power from `3.3V` |
| **Both `GND`** | `GND` (`TP4056 OUT-`) | Common ground |

//https://notisrac.github.io/FileToCArray/
Resize 138x160
Color Format 16bit RRRRRGGGGGBBBBB (2bytes/pixel)
Data type unit16_t
Check both static and const for efficient storage





