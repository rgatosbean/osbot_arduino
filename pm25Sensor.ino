#include<stdlib.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define CLEARSRCN  "CLS(0);"    //清空液晶屏 
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
unsigned char isClear=0;//是否清屏
unsigned char cmdMode=0;
int bkpic=0;//图片号
int oldval=0;//旧pm2.5值
int oldaqi=0;//旧AQI指数值
int prmK=560;//斜率系数K
int prmD=320;//偏移系数D
char readcmd[64];//Serial接收到的命令
int cmdcnt=0;//Serial接收到字符计数
SoftwareSerial mySerial(10, 9); // 软件模拟串口10为RX, 9为TX
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(ledPower,OUTPUT);
 
// give the ethernet module time to boot up:
delay(1000);
mySerial.begin(115200); 
 isClear=1;
i=0;
ppm=0;
delay(100);
rdCfg();
delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  int j;
  if(Serial.available())
      GetSerialCMD(); 
  if(cmdMode)//读取串口数据
  {
    for(j=0;j<64;j++)
    {
      delay(1);
      GetSerialCMD(); 
      if(!cmdMode)
      break;      
      }
    }
i=i+1;
digitalWrite(ledPower,LOW);// power on the LED
delayMicroseconds(delayTime);
dustVal=analogRead(A0);// read the dust value
ppm=ppm+dustVal;//累计读取ppm值
delayMicroseconds(delayTime2);
digitalWrite(ledPower,HIGH);// turn the LED off
delayMicroseconds(offTime);
 
voltage=ppm/i*0.0049;//电压转换：单位电压= 5（V）/1024=0.0049
dustdensity=0.17*voltage-0.1;//将电压值转换为粉尘密度（毫克/立方米），颗粒浓度（依据说明书图3曲线）
//ppmpercf=(voltage-0.0256)*100;//颗粒数ug/立方米
ppmpercf=(voltage-0.0256)*prmK-prmD;

if(ppmpercf<0)
ppmpercf=0;
if(dustdensity<0)
dustdensity=0;
if(dustdensity>0.5)
dustdensity=0.5;

if(voltage<0.6)//0.6为静态零点电压，此时i计数清零
{
  i=0;
ppm=0;
return;
  }
float aqi =  calcAQI(ppmpercf);
DisplayPm25(ppmpercf,aqi,bkpic);

//String dataString="";
//dataString+=dtostrf(voltage,9,4,s);
//dataString+=",";
//dataString+=dtostrf(dustdensity*1000,5,2,s);
//dataString+=",";
//dataString+=dtostrf(calcAQI(dustdensity*1000),8,0,s);

Serial.println(ppmpercf);
delay(1000);
}
void DisplayPm25(float val,float aqi,int pic)//显示数值颗粒数、AQI、背景图号
{
  char cmd[128];  
  if(isClear)
  {
    isClear=0;
      mySerial.println(CLEARSRCN);//第一次需要清屏
      delay(100);     
   }
   if(oldval==(int)val&&oldaqi==(int)aqi)//数值不变就不更新
   return;
   if((int)val>=1000)
   {
    sprintf(cmd,"BPIC(%d,0,0,%d);PS64(%d,18,56,'%d',15,200);PS24(%d,143,79,'%d',15,200);",pic,pic,pic,(int)val,pic,(int)aqi);
    }else if((int)val>=100)
    {
      sprintf(cmd,"BPIC(%d,0,0,%d);PS64(%d,30,56,'%d',15,200);PS24(%d,143,79,'%d',15,200);",pic,pic,pic,(int)val,pic,(int)aqi);
      }else if((int)val>=10)
      {
        sprintf(cmd,"BPIC(%d,0,0,%d);PS64(%d,46,56,'%d',15,200);PS24(%d,149,79,'%d',15,200);",pic,pic,pic,(int)val,pic,(int)aqi);     
        }else{
          sprintf(cmd,"BPIC(%d,0,0,%d);PS64(%d,61,56,'%d',15,200);PS24(%d,154,75,'%d',15,200);",pic,pic,pic,(int)val,pic,(int)aqi);   
          }
    
  oldval=(int)val;//保存当前值
  oldaqi=(int)aqi;
  //Serial.println(cmd);
  mySerial.println(cmd);
  delay(100);   
  }
 float calcAQI(float val)//计算AQI值
 {
    if(0<val&&val<=50)
    {
      bkpic=2;return val*1.42857;
      }else if(50<val&&val<=100)
      {
        bkpic=3;return val*1.25;
        }else if(100<val&&val<=150)
      {
        bkpic=4;return val*1.25;
        }else if(150<val&&val<=300){
          bkpic=5;return val*0.66666667;
          }else{
            bkpic=6;return val*0.66666667;
            }
  }
  void wtCfg()//存储配置
{
  int i=0;
  int address = 0; 
  int param[2]; 
  param[0]=prmK;
  param[1]=prmD;
  for(i=0;i<2;i++)
  {
    EEPROM.write(address, param[i]);
    address++;
    }  
 }
 void rdCfg()//读取配置
{
  int i=0;
  int address = 0;
  int param[2]; 
  for(i=0;i<2;i++)
  {
    param[i]=EEPROM.read(address);
    address++;
    if(0<=(int)param[i])
    {
        param[0]=prmK;
        param[1]=prmD;
        break;
      }
  }
  Serial.println(param[0]);
  Serial.println(param[1]);  
  Serial.println("read param ok!");
 }
 void GetSerialCMD()//判断上位机串口命令
{
  char c = char(Serial.read()); //读取串口数据
  readcmd[cmdcnt++] = c;//保存接收字符
  //判断命令字
  if(cmdcnt==1)
  {
    if(readcmd[0]!='P')
    {
      cmdcnt=0;return; 
      }
      cmdMode=1;
  }else if(cmdcnt==2)
  {
     if(readcmd[1]!='M')
    {   
         cmdcnt=0;return; 
    }
    }else if(cmdcnt==3)
    {
       if(readcmd[2]!='C')
      {   
           cmdcnt=0;return;
      }
        
      
   }
  //命令结束
  if(c=='#')
  {    
      cmdcnt=0;    
      //自定义配置，写入eeprom端口对应关系
          char num[6];
          char * p=readcmd+3;
          int i,j;
          int param[2];
          for(j=0;j<2;j++)
          {
            for(i=0;i<6;i++)
            {
              if(*p==','||*p==0xa||*p=='#')
              break;
              num[i]=*p;p++;
            }
            p++;
            param[j]=atoi(num);            
            memset(num,0,6);
            }  
            prmK = param[0];
            prmD = param[1];
          Serial.println("end");      
          wtCfg();//写入配置参数信息
          rdCfg();//读出配置参数信息
          cmdMode=0;
      }     
   
}
