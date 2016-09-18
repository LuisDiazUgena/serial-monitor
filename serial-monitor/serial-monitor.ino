#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define okBtn 7
#define moveBtn 8
#define delayTime 250

int serialIndex = 4;
float serialSpeedOptions[12]={300,1200,2400,4800,9600,19200,38400,57600,74880,115200,230400,250000};
float serialSpeed = 9600;
boolean bootAnimation = true;

void setup() {
  //loadConfig(); // KEEP ALWAYS IN FIRST PLACE AT SETUP!!!!!
  Serial.begin(serialSpeed);
  Serial.println("Serial init!");
  pinMode(okBtn,INPUT_PULLUP);
  pinMode(moveBtn,INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showInitInfo();
}
String str;
void loop() {
  //Serial.println("loop");
  if (digitalRead(okBtn) == 0){
    delay(delayTime);
    showMenu();
  }
  if (Serial.available() > 0) {
    display.clearDisplay();
    str = Serial.readString();
    int lenght = str.length();
    display.setCursor(0, 0);
    display.println(str);
    display.display();
  }

}

void showMenu(){

  int spacingY = 10,spacingX=10;
  int index= 0;
  int options = 4;

  while(digitalRead(okBtn)!=0){
    if(digitalRead(moveBtn)==0){
      index++;
      if(index==options){
        index=0;
      }
      delay(delayTime);

    }

    display.clearDisplay();
    if(index!=3){
      display.setCursor(0,spacingY*index);
    }else{
      display.setCursor(70,spacingY*2);
    }
    display.println("#");
    display.setCursor(spacingX, 0);
    display.println("Serial speed");
    display.setCursor(85,0);
    display.println(serialSpeedOptions[serialIndex],0);
    display.setCursor(spacingX,spacingY);
    display.println("Boot animation");
    display.setCursor(105,spacingY);
    display.println(bootAnimation);
    display.setCursor(spacingX,spacingY*2);
    display.println("Back");
    display.setCursor(8*spacingX,spacingY*2);
    display.println("Save");

    display.display();
  }
  //We have pressed the ok button, so..
  //now we need to choose what to do :)
  if(index==0){ //Serial option
    serialIndex++;
    if(serialIndex>11){
      serialIndex=0;
    }
    serialSpeed=serialSpeedOptions[serialIndex];

    Serial.print("Serial index =");
    Serial.println(serialIndex);
    Serial.print("Serial speed =");
    Serial.println(serialSpeed);

    delay(delayTime);
    callMenuFunc();
  }
  if(index==1){
    bootAnimation=!bootAnimation;
    delay(delayTime);
    callMenuFunc();
  }

  if(index==2){
    //go to main loop
    display.clearDisplay();

    delay(delayTime);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Waiting...");
    display.display();

  }
  if(index==3){
    //save data
    saveData();
    delay(delayTime);
  }
}

#define serialSpeedAddress 1
#define bootScreenAddress 2

void saveData(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Saving Data...");
  display.display();
  delay(delayTime);
  EEPROM.write(serialSpeedAddress,serialIndex);
  EEPROM.write(bootScreenAddress,bootAnimation);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Data Saved...");
  display.display();
  delay(delayTime*3);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Waiting...");
  display.display();

  Serial.print("Data saved");
  Serial.print("Speed = ");
  Serial.println(EEPROM.read(serialSpeedAddress));
  Serial.print("boot = ");
  Serial.println(EEPROM.read(bootScreenAddress));

}

void loadConfig(){
  serialSpeed = serialSpeedOptions[EEPROM.read(serialSpeedAddress)];
  bootAnimation = EEPROM.read(bootScreenAddress);
  Serial.print("Data loaded");
  Serial.print("Speed = ");
  Serial.println(EEPROM.read(serialSpeedAddress));
  Serial.print("boot = ");
  Serial.println(EEPROM.read(bootScreenAddress));
}

void callMenuFunc(){
  showMenu();
}
void showInitInfo() {
  if(bootAnimation){

    display.clearDisplay();
    delay(10);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Serial");
    display.setCursor(0, 17);
    display.println("Monitor");
    display.display();
    delay(750);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("DrMaker.es");
    display.setCursor(0, 17);
    display.display();
    delay(750);
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Waiting...");
  display.display();
}
