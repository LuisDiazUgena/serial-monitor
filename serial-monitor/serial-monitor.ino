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
  if (digitalRead(okBtn) == 0){
    Serial.println("button pressed!");
    delay(delay_time);
    //showMenu();
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
  display.println("DrMaker.es");
  display.setCursor(0, 17);
  display.display();
  delay(750);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Waiting...");
  display.display();
}
