#include<stdlib.h>
int dustPin=0;
int ledPower=2;
int delayTime=280;
int delayTime2=40;
float offTime=9680;
 
int dustVal=0;
int i=0;
float ppm=0;
char s[32];
float voltage=0;
float dustdensity=0;
float ppmpercf=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(ledPower,OUTPUT);
 
// give the ethernet module time to boot up:
delay(1000);
 
i=0;
ppm=0;
}

void loop() {
  // put your main code here, to run repeatedly:
i=i+1;
digitalWrite(ledPower,LOW);// power on the LED
delayMicroseconds(delayTime);
dustVal=analogRead(A0);// read the dust value
ppm=ppm+dustVal;
delayMicroseconds(delayTime2);
digitalWrite(ledPower,HIGH);// turn the LED off
delayMicroseconds(offTime);
 
voltage=ppm/i*0.0049;//电压转换：单位电压= 5（V）/1024=0.0049
dustdensity=0.17*voltage-0.1;//将电压值转换为粉尘密度（毫克/立方米），颗粒浓度（依据说明书图3曲线）
//ppmpercf=(voltage-0.0256)*120000;//颗粒数
ppmpercf=dustdensity*1000;//换算成ug/立方米
if(ppmpercf<0)
ppmpercf=0;
if(dustdensity<0)
dustdensity=0;
if(dustdensity>0.5)
dustdensity=0.5;
String dataString="";
dataString+=dtostrf(voltage,9,4,s);
dataString+=",";
dataString+=dtostrf(dustdensity,5,2,s);
dataString+=",";
dataString+=dtostrf(ppmpercf,8,0,s);
i=0;
ppm=0;
Serial.println(dataString);
delay(1000);
}
