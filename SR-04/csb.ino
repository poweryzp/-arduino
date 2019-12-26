#include <Adafruit_GFX.h>    
#include <Arduino_ST7789.h> 
#include <SPI.h>

#define Trig 2
#define Echo 3
#define TFT_DC    8
#define TFT_RST   9
#define TFT_MOSI  11   
#define TFT_SCLK  13
Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST);

float cm;
float temp;

void setup(){
  Serial.begin(9600);
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  tft.init(240, 240);
  tft.fillScreen(BLACK);
  delay(500);
}

void loop(){
  digitalWrite(Trig, LOW);//给Trig发送一个低电平
  delayMicroseconds(2);    //等待 2微妙
  digitalWrite(Trig,HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);    //等待 10微妙
  digitalWrite(Trig, LOW); //给Trig发送一个低电平
  temp = float(pulseIn(Echo, HIGH)); //存储回波等待时间,
  cm = (temp * 17 )/1000;//把回波时间换算成cm
  tft.fillScreen(BLACK);
  tft.setCursor(20, 50);
  tft.setTextColor(BLUE);
  tft.setTextSize(4);
  tft.println("Distance  ");
  tft.setTextColor(GREEN);
  tft.print("  ");
  tft.print(cm);//输出距离换算成cm的结果
  tft.println("cm");
  delay(300);
}
