// Enhanced ESP32-C3 SuperMini ST7735 TFT Test (Adafruit Libs)
// Refactored: ScreenTest function + Fancy animated geometry + Animated Robot + Pong Animation
// Pins: MOSI=7, SCK=6, CS=3, DC=4, RST=5, VCC=3.3V, GND=GND, BL=3.3V
// Libs: Adafruit_GFX, Adafruit_ST7735

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "ColorManager.h"
#include "Animations.h"
#include "Bitmap.h"
#include "BitmapManager.h"

// TFT Pin Definitions
#define TFT_CS   3   // GPIO3
#define TFT_RST  5   // GPIO5
#define TFT_DC   4   // GPIO4
#define TFT_MOSI 7   // GPIO7 for SDA/MOSI
#define TFT_SCLK 6   // GPIO6 for SCL/SCLK

// Screen dimensions (landscape rot 3)
#define SCREEN_WIDTH  160
#define SCREEN_HEIGHT 128

// Create display object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Create animation manager
AnimationManager* animManager;
BitmapManager* bm;  // ADD: Global declaration

// Globals (add before setup)
bool inBitmapMode = true;
int imageCount = 0;
unsigned long modeStart = 0;
const int IMAGE_TIME = 3000;  // 3s per image
const int ANIM_TIME = 30000;  // 30s animations


// Simple function to display bitmap from PROGMEM
void displayBitmap() {
  Serial.println("Displaying Windows XP bitmap...");
  
  tft.startWrite();
  tft.setAddrWindow(0, 0, IMG_WIDTH, IMG_HEIGHT);
  
  // Buffer 32 pixels at a time (saves RAM)
  uint16_t buffer[32];
  uint32_t totalPixels = (uint32_t)IMG_WIDTH * IMG_HEIGHT;
  
  for (uint32_t i = 0; i < totalPixels; i += 32) {
    uint16_t pixelsToRead = min((uint32_t)32, totalPixels - i);
    
    // Read from Flash memory (PROGMEM)
    for (uint16_t j = 0; j < pixelsToRead; j++) {
      buffer[j] = pgm_read_word(&bitmapWindowsXP[i + j]);
    }
    
    // Write to display
    tft.writePixels(buffer, pixelsToRead);
  }
  
  tft.endWrite();
  Serial.println("Bitmap displayed!");
}

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("TFT Animation ");

  // Initialize SPI with C3 pins (remap for hardware SPI)
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, -1);  // SCLK, MISO (unused), MOSI, SS (unused)
  SPI.setFrequency(10000000);

  // Ensure CS is set as output
  pinMode(TFT_CS, OUTPUT);
  digitalWrite(TFT_CS, LOW);

  // Initialize display with BLACKTAB
  tft.initR(INITR_BLACKTAB);  //tft.initR(INITR_GREENTAB);// keep this to try INITR_GREENTAB
  tft.setRotation(3);  // Landscape
  tft.setAddrWindow(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);  //tft.setAddrWindow(2, 2, SCREEN_WIDTH, SCREEN_HEIGHT); //Keep this to try Blacktab
  tft.fillScreen(ST7735_BLACK);
  delay(50);  
  Serial.println("TFT Initialized!");

  // Create animation manager
  animManager = new AnimationManager(&tft);
  animManager->init();
  
  Serial.println("Animation system ready");
  Serial.println("Sequence: 3 color tests, then animations loop");

// CHANGE: Global allocation
  bm = new BitmapManager(&tft, 3000);  // Now global; 3s per bitmap
  Serial.println("Bitmap system ready");

}

void loop() {
  unsigned long now = millis();

  if (inBitmapMode) {
    bm->displayNext();
    if (now - modeStart >= IMAGE_TIME) {
      modeStart = now;
      imageCount++;
      if (imageCount >= 2) {  // After 2 images
        inBitmapMode = false;
        modeStart = now;
        Serial.println("Switch to animations");
      }
    }
    delay(10);
  } else {
    animManager->update();
    if (now - modeStart >= ANIM_TIME) {
      inBitmapMode = true;
      imageCount = 0;
      modeStart = now;
      Serial.println("Switch to bitmaps");
    }
    delay(20);
  }

  yield();
}