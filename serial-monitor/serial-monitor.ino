#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define okBtn 7
#define moveBtn 8
#define delay_time 750
void setup() {

  Serial.begin(19200);
  pinMode(okBtn,INPUT_PULLUP);
  pinMode(moveBtn,INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showInitInfo();
}
String str;
void loop() {
  if (digitalRead(okBtn) == 1){
    showMenu();
  }
  if (Serial.available() > 0) {
    display.clearDisplay();
    str = Serial.readString();
    display.setCursor(0, 0);
    display.println(str);
    display.display();
  }


}
void menuOptions(){
  display.setCursor(10,0);
  display.println("Serial speed");
  display.setCursor(10,20);
  display.println("Back");
  display.display();
}
void showMenu(){
  display.clearDisplay();
  int posCursor = 0;
  menuOptions();

  display.setCursor(0,posCursor);
  display.print("#");
  display.display();
  while(1){

    if(digitalRead(okBtn) == 1){
      delay(delay_time);
      if(posCursor==0){
        Serial.println("Pos = 0");
          showSerial();
      }else if(posCursor == 20){
        Serial.println("Pos = 20");
        break;
      }

    }
    if(digitalRead(moveBtn) == 1){
      delay(delay_time);
      display.clearDisplay();
      if (posCursor==0){
        posCursor = 20;
      }else{
        posCursor = 0;
      }
      display.setCursor(0,posCursor);
      display.print("#");
      display.display();
      menuOptions();
    }
  }
}
void showSerial(){
  Serial.println("showSerial menu");
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Serial speed is:");
  display.display();
  while(digitalRead(okBtn)!=1){

  }
  delay(delay_time);
}
void showInitInfo() {
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
  display.setTextSize(1);
  display.println("Waiting...");
  display.display();
}
