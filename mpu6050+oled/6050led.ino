#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
#include "math.h"
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);       

//====set offset of x,y,z===========
#define Gx_offset -3.06
#define Gy_offset 1.01
#define Gz_offset -0.88

MPU6050 accelgyro;

int16_t ax,ay,az;
int16_t gx,gy,gz;//Storing original data
float aax,aay,aaz,ggx,ggy,ggz;//The quantized data is stored
float Ax,Ay,Az;// g(9.8m/s^2)
float Gx,Gy,Gz;// °/s
int left,right,head,back;
float Angel_accX,Angel_accY,Angel_accZ,A,B,C;//Storing the calculated angle by acceleration
long LastTime,NowTime,TimeSpan;//Integral to the angular velocity


void setup()
{
  Wire.begin();
  accelgyro.initialize();
  pinMode(8,OUTPUT);
}

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void u8g_box_frame() {
  B = -Angel_accX+32;
  A = -Angel_accY+74;
  u8g.drawFrame(A, B, 20, 20);
}

void draw(void) {
  u8g_prepare();
  u8g_box_frame();
  u8g.setFont(u8g_font_6x10);
  u8g.setPrintPos(10, 16);
  u8g.print("X:");
  u8g.print(Angel_accX);
  u8g.setPrintPos(10, 32);
  u8g.print("Y:");
  u8g.print(Angel_accY);
  u8g.setPrintPos(10, 48);
  u8g.print("Z:");
  u8g.print(Angel_accZ);

  u8g.setPrintPos(10, 0);
  u8g.print(right);
  u8g.setPrintPos(18, 0);
  u8g.print("--");
  u8g.print(left);
  u8g.setPrintPos(34, 0);
   u8g.print("--");
  u8g.print(head);
  u8g.setPrintPos(50, 0);
  u8g.print("--");
  u8g.print(back);
}
void loop()
{
  accelgyro.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);//Being three-axis acceleration and angular velocity

//======get Acceleration values of x,y,z
   Ax=ax/16384.00;
   Ay=ay/16384.00;
   Az=az/16384.00;
   //==========there are calculated angle between thethree axes of coordinate system by acceleration
   Angel_accX=atan(Ax/sqrt(Az*Az+Ay*Ay))*180/3.14;
   Angel_accY=atan(Ay/sqrt(Ax*Ax+Az*Az))*180/3.14;
   Angel_accZ=atan(Az/sqrt(Ax*Ax+Ay*Ay))*180/3.14;
  //==============================
  delay(10);//This is used to control the sampling rate
  //stop
  if((-5<=Angel_accX)&&(Angel_accX<=5)&&(-5<=Angel_accY)&&(Angel_accY<=5)&&(80<=Angel_accZ)&&(Angel_accZ<=90))
  {
    right=0;left=0;head=0;back=0;
    analogWrite(8,0);
    analogWrite(9,0);
  }
  //right
  else if((-15<=Angel_accX)&&(Angel_accX<=15)&&(5<=Angel_accY)&&(Angel_accY<=15)&&(70<=Angel_accZ)&&(Angel_accZ<=80))
  {
    right=1;left=0;head=0;back=0;
  }
    //left
  else if((-15<=Angel_accX)&&(Angel_accX<=15)&&(-15<=Angel_accY)&&(Angel_accY<=-5)&&(50<=Angel_accZ)&&(Angel_accZ<=80))
  {
    right=0;left=1;head=0;back=0;
  }
    //head
  else if((20<=Angel_accX)&&(Angel_accX<=30)&&(-15<=Angel_accY)&&(Angel_accY<=15)&&(50<=Angel_accZ)&&(Angel_accZ<=70))
  {
    right=0;left=0;head=1;back=0;
    analogWrite(9,100);
    digitalWrite(8,0);
  }
    //back
  else if((-15<=Angel_accX)&&(Angel_accX<=-5)&&(-15<=Angel_accY)&&(Angel_accY<=15)&&(75<=Angel_accZ)&&(Angel_accZ<=84))
  {
    right=0;left=0;head=0;back=1;
    analogWrite(9,100);
    digitalWrite(8,1);
  }

    u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
}
