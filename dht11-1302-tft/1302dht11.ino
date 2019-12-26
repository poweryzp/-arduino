#include <stdio.h>
#include <DS1302.h>
#include <Adafruit_GFX.h>    // Core graphics library by Adafruit
#include <Arduino_ST7789.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <SPI.h>
#include <DHT.h>
#include <DHT_U.h>

#define TFT_DC    4
#define TFT_RST   5 
#define TFT_MOSI  11
#define TFT_SCLK  13
#define DHTPIN 10
#define DHTTYPE DHT11

DS1302 rtc(6, 7, 8); //rst,dat,scl
Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST);
DHT dht(DHTPIN, DHTTYPE);

String comdata = "";
int numdata[7] ={0}, j = 0, mark = 0;
char buf[50];
void setup() {
  Serial.begin(9600);
  rtc.writeProtect(false);
  rtc.halt(false);
  tft.init(240, 240);
  dht.begin();
}

void loop() {
 float sd = dht.readHumidity();
 float wd = dht.readTemperature();
  Time t = rtc.time(); 
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",t.yr, t.mon, t.date,t.hr, t.min, t.sec);
  Serial.print(buf);
  Serial.print("  wd=");
  Serial.print(wd);
  Serial.print("C");
  Serial.print("  sd=");
  Serial.print(sd);
  Serial.println("%");
  sheding();
  tft.fillScreen(BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.print("  ");
  tft.print("sd=");
  tft.print(sd);
  tft.println("%");
  tft.println("");
  tft.print("  ");
  tft.print("wd=");
  tft.print(wd);
  tft.println("C");
  tft.println("");
  tft.print("  ");
  tft.print(t.hr);
  tft.print(":");
  tft.print(t.min);
  tft.print(":");
  tft.println(t.sec);
  tft.println("");
  tft.print("  ");
  tft.print(t.yr);
  tft.print("-");
  tft.print(t.mon);
  tft.print("-");
  tft.print(t.date);
  delay(600);
 }
 void sheding() {
   /* 一下为串口输入改变数据程序, 当串口有数据的时候，将数据拼接到变量comdata */
    while (Serial.available() > 0)
    {
        comdata += char(Serial.read());
        delay(2);
        mark = 1;
    }
     /* 以逗号分隔分解comdata的字符串，分解结果变成转换成数字到numdata[]数组 */
    if(mark == 1)
    {
        Serial.print("You inputed : ");
        Serial.println(comdata);
        for(int i = 0; i < comdata.length() ; i++)
        {
            if(comdata[i] == ',' || comdata[i] == 0x10 || comdata[i] == 0x13)
            {
                j++;
            }
            else
            {
                numdata[j] = numdata[j] * 10 + (comdata[i] - '0');
            }
        }
          /* 将转换好的numdata凑成时间格式，写入DS1302 */
        Time t(numdata[0], numdata[1], numdata[2], numdata[3], numdata[4], numdata[5], numdata[6]);
        rtc.time(t);
        mark = 0;j=0;   /* 清空 comdata 变量，以便等待下一次输入 */
        comdata = String("");  /* 清空 numdata */
        for(int i = 0; i < 7 ; i++) {numdata[i]=0;}
    }
 }
