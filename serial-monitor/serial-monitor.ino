#include <EEPROM.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>

//TFT init
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
boolean backlightStatus = true;
int serialSpeed=9600;
//eeprom addresses
#define firstTimeAddress 0
#define serialSpeedAddress 1
#define backlightAddress 2

void firstTimeInit(){
  if (EEPROM.read(firstTimeAddress)==0){
    EEPROM.write(serialSpeedAddress,serialSpeed);
    EEPROM.write(backlightAddress,1);

    EEPROM.write(firstTimeAddress,1);
  }
}
void loadConfig(){
  serialSpeed = EEPROM.read(serialSpeedAddress);
  backlightStatus = EEPROM.read(backlightStatus)
}

void setup(){
  firstTimeInit(); // Check if there is a custom config or the program should create it.
  loadConfig();
  Serial.begin(serialSpeed);

}
