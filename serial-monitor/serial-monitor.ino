#include <EEPROM.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>

//Colors init
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//TFT init
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
boolean bootScreenStatus = true;
int indexPos = 0; // Where to print the data
boolean backlightStatus = true;

int serialSpeed=9600;
//eeprom addresses
#define firstTimeAddress 0
#define serialSpeedAddress 1
#define backlightAddress 2
#define bootScreenAddress 3

void firstTimeInit(){
  if (EEPROM.read(firstTimeAddress)==0){
    EEPROM.write(serialSpeedAddress,serialSpeed);
    EEPROM.write(backlightAddress,1); // 1 to turn on the backlight
    EEPROM.write(bootScreenAddress,true); // 1 to turn on the bootScreen

    EEPROM.write(firstTimeAddress,1);
  }
}

void loadConfig(){
  serialSpeed = EEPROM.read(serialSpeedAddress);
  backlightStatus = EEPROM.read(backlightStatus);

  if(EEPROM.read(bootScreenAddress)){
    bootScreenStatus = true;
  }else{
    bootScreenStatus = false;
  }
}

void tftInit(){

  tft.begin();
  tft.clearScreen();

  if(bootScreenStatus==true){
    tft.setCursor(16,0);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.println("Hardware Serial Monitor");
    tft.setCursor(16,20);
    tft.setTextColor(RED);
    tft.setTextSize(4);
    tft.println("DrMaker.es");
    delay(750);
  }
  tft.clearScreen();
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
}

void setup(){
  loadConfig(); // must be first thing to do in the setup
  tftInit();
  firstTimeInit(); // Check if there is a custom config or the program should create it.

  Serial.begin(serialSpeed);
}

void loop() {
  if(Serial.available()>0){
    printData(Serial.readString());
  }
}
String str0="", str1="", str2="", str3="", str4="";
int spacing = 10;
void printData(String _str){
  if(indexPos==4){
  }
  if(_str.length()>0){
    if (indexPos == 0){
      str0=_str;
      tft.setCursor((5-indexPos)*spacing);
      tft.println(_str);
    }
    if (indexPos == 1){
      str1=_str;
      tft.setCursor((5-indexPos)*spacing);
      tft.println(_str);
    }
    if (indexPos == 2){
      str2=_str;
      tft.setCursor((5-indexPos)*spacing);
      tft.println(_str);
    }
    if (indexPos == 3){
      str3=_str;
      tft.setCursor((5-indexPos)*spacing);
      tft.println(_str);
    }
    if (indexPos == 4){
      changeStrPos();
      str4=_str;
      tft.setCursor((5-indexPos)*spacing);
      tft.println(_str);
    }
  }
}
void changeStrPos(){
  str0=str1;
  str1=str2;
  str2=str3;
  str3=str4;
  str4="";
  tft.setCursor(5*spacing);
  tft.println(str0);
  tft.setCursor(4*spacing);
  tft.println(str1);
  tft.setCursor(3*spacing);
  tft.println(str2);
  tft.setCursor(2*spacing);
  tft.println(str3);
}
