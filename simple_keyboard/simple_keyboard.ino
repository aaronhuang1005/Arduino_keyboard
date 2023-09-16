#include <SPI.h> 
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
#include "Keyboard.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

// 設定OLED
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ascii=65;

void show(){
    display.clearDisplay();
    
    if(ascii<32){
      ascii=126;
    }else if(ascii>126){
      ascii=32;
    }
    
    if(ascii==32){
      display.setTextSize(3);       
      display.setTextColor(1);        
      display.setCursor(20,12); 
      display.print("space");      
    }else{
      char s = ascii;
      display.setTextSize(6);        
      display.setTextColor(1);         
      display.setCursor(25,10);  
      display.print(s);   
    }
    display.display(); 
    delay(300);
}


void setup() {
  Keyboard.begin();
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.setTextSize(3);        
  display.setTextColor(1);         
  display.setCursor(20,20);  
  display.print("|ABC|");
  display.display(); 
  delay(5000);
  display.clearDisplay();
  char s = ascii;
  display.setTextSize(6);        
  display.setTextColor(1);         
  display.setCursor(25,10);  
  display.print(s);
  display.display(); 
  
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

}


void loop() {
  int val_down=digitalRead(7);
  int val_up=digitalRead(8);
  int num=digitalRead(6);
  int cap=digitalRead(9);
  int enter=digitalRead(10);
  int backspace=digitalRead(11);
  
  if(val_down==LOW){
    ascii--;
    show();
    while(digitalRead(7)==LOW){}
  }else if(val_up==LOW){
    ascii++;
    show();
    while(digitalRead(8)==LOW){}
  }else if(num==LOW){
    ascii=48;
    display.clearDisplay();
    display.setTextSize(3);        
    display.setTextColor(1);         
    display.setCursor(20,20);  
    display.print("|123|");
    display.display(); 
    delay(350);
    show();
    while(digitalRead(6)==LOW){}
  }else if(cap==LOW){
    if(ascii>64 && ascii<91){
      ascii+=32;
      display.clearDisplay();
      display.setTextSize(3);        
      display.setTextColor(1);         
      display.setCursor(20,20);  
      display.print("|abc|");
      display.display(); 
      delay(350);
    }else if(ascii>96 && ascii<123){
      ascii-=32;
      display.clearDisplay();
      display.setTextSize(3);        
      display.setTextColor(1);         
      display.setCursor(20,20);  
      display.print("|ABC|");
      display.display(); 
      delay(350);
    }else{
      ascii=65;
      display.clearDisplay();
      display.setTextSize(3);        
      display.setTextColor(1);         
      display.setCursor(20,20);  
      display.print("|ABC|");
      display.display(); 
      delay(350);
    }
    show();
    while(digitalRead(9)==LOW){}
  }else if(enter==LOW){
    bool st=false;
    int i;
    for(i=0;i<5;i++){
      delay(100);
      if(digitalRead(10)==HIGH){
        st=true;
        break;
      }
    }
    if(st){
      Keyboard.write(ascii);
      delay(300);
      Keyboard.releaseAll();
    }else{
      Keyboard.write(0xB0);
      delay(500);
      Keyboard.releaseAll();
    }
    while(digitalRead(10)==LOW){}
    
  }else if(backspace==LOW){
    Keyboard.write(0xB2);
    delay(300);
    Keyboard.releaseAll();
    while(digitalRead(11)==LOW){}
  }
  
  Serial.println(ascii);

}
