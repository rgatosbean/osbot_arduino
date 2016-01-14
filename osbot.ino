/*
 * osbot.c
 * Author: RG
 * Created: 2015-12-08
 */
#include <Arduino.h> 
#include <string.h>
#include "osair4bot.h"
#include <SoftwareSerial.h>
#include <EEPROM.h>


int  defcnt=0;//计数变量
char readcmd[64];//Serial接收到的命令
int cmdcnt=0;//Serial接收到字符计数
OSAIR4bot _osair;//声明对象实例
unsigned char airmode=0;//air模式 0:默认,此时可接收PC串口数据;1:8266配置模式，可以执行reset\info\wifiscan\apcon\ifconfig等命令;
                        //2:osbot配置命令，包括模式、端口映射等(串口和wifi都可以配置)
unsigned char osbotmode=0;//机器人工作模式
unsigned char faceCmd=0;//第一次设置表情，必须清空屏幕
OsPort_Sig osPort[6]={{11, 8}, {A2, A3},{10, 9},{A0, A1},{A4, A5},{MISO, SCK}};//6个RJ25接口第5、第6脚对应IO
unsigned char SensorIndex[40];//传感器模块缓存，从eeprom中读出，接收配置更改指令后，写入eeprom中
//SensorIndex[n]=i;表示n号传感器对应第i个RJ25端口；例：SensorIndex[1]=2;表示避障模块接在IO{D10, D9}所在的RJ25端口

unsigned char cfgBuff[6];//RJ25端口配置
SoftwareSerial mySerial(11, 8); // 软件模拟串口11为RX, 8为TX

void OSWfunc(char*pp)//自定义函数处理网络数据
{
  char rcvnum[3];
  unsigned char txtbuf[5];
  if(pp[0]=='O'&&pp[1]=='S'&&pp[2]=='W')//判断命令字
   {    
    memset(rcvnum,0,3);
    rcvnum[0]=pp[4];rcvnum[1]=pp[5];
    if(atoi(rcvnum)==0)//设置工作模式
    {
      memset(rcvnum,0,3);
      rcvnum[0] = pp[7];
      osbotmode= atoi(rcvnum);
      Serial.println(osbotmode); Serial.println("end"); 
      }
    else if(atoi(rcvnum)==1)//表情设置
    {
      memset(rcvnum,0,3);
      airmode=2;//当前不接收串口命令
      int i,j,k;
      char *p=pp+9;
      for(i=0;i<3;i++)
      {
        if(*p=='.')
        break;
        rcvnum[i]=*p;
        p++;
        }
        p++;
        j=atoi(rcvnum);
        memset(rcvnum,0,3);
        for(i=0;i<3;i++)
      {
        if(*p=='.')
        break;
        rcvnum[i]=*p;
        p++;
        }
        k=atoi(rcvnum);
        Serial.println(j); Serial.println(k); Serial.println("end");
      //setface(j,k);//眼睛和嘴巴对应图标索引号      
      airmode=0;//开启接收串口数据
      }else if(atoi(rcvnum)==2)//文本颜色设置及坐标
      {
        memset(rcvnum,0,3);
        airmode=2;//当前不接收串口命令
      int i,j;
      char *p=pp+7;
      for(j=0;j<4;j++)
      {
        for(i=0;i<3;i++)
      {
        if(*p=='.')
        break;
        rcvnum[i]=*p;
        p++;
        }
        p++;
        txtbuf[j]=atoi(rcvnum);
        Serial.println(txtbuf[j]); 
        memset(rcvnum,0,3);
        }
        rcvnum[0]=*p;p++;rcvnum[1]=*p;p++;rcvnum[2]=*p;p++;
        txtbuf[4]=atoi(rcvnum);
        Serial.println(txtbuf[4]);Serial.println("end");
        airmode=0;//开启接收串口数据
        }else if(atoi(rcvnum)==3)//显示文本内容
      {
        memset(rcvnum,0,3);
        char *p=pp+7;
        Serial.println(p);
        setText(txtbuf[0],txtbuf[1],txtbuf[2],txtbuf[3],txtbuf[4],p);
        }else if(atoi(rcvnum)==4)//播放声音文件
      {
        memset(rcvnum,0,3);
        airmode=2;//当前不接收串口命令
      int i,j,k;
        char *p=pp+7;
        for(i=0;i<3;i++)
      {
        if(*p=='.')
        break;
        rcvnum[i]=*p;
        p++;
        }
        p++;
        j=atoi(rcvnum);
        memset(rcvnum,0,3);
        for(i=0;i<3;i++)
      {
        if(*p=='.')
        break;
        rcvnum[i]=*p;
        p++;
        }
        p++;
        k=atoi(rcvnum);
        Serial.println(j);Serial.println(k);Serial.println("end");
        setVoice(j,k);
        }else if(atoi(rcvnum)==5)//获取当前工作模式
        {
          char sbuf[32];
          sprintf(sbuf,"OSB.00.%d",osbotmode);
          _osair.sendText(sbuf);//向网络发送文本
              
          }
    
    }
   
}
void setup() {
  // put your setup code here, to run once:
  _osair.init();//初始化对象实例
  Serial.begin(115200);//打开串口用于监视
  _osair.setLoadMode();//设置烧写模式，可更新固件
  _osair.setHandler(OSWfunc);//设置自定义函数句柄
  delay(200);  
  
  
  mySerial.begin(115200); 
  delay(200);
}
void loop() {

  
  // put your main code here, to run repeatedly:
_osair.loop();//ARDUINO AIR主循环函数
////////////////////////////
if(airmode==0)//接收上位机串口命令
{  
  delay(1); 
  if(Serial.available())
    GetSerialCMD();    
  }else if(airmode==1){
    defcnt++;   
    delay(1);
    if(defcnt==1)
    {        
      _osair.airConfig(readcmd+5);//向8266发送配置命令             
    }
    //Serial.println(strlen(readcmd));
     if(defcnt==strlen(readcmd)-5)//延时后读取8266配置结果
     {
        long m_lastRead = millis()/1000;
       while(1)
       {
          long m_now = millis()/1000;
          if(( m_now-m_lastRead) > 4)//持续4秒，读取8266返回信息
              break;
              _osair.airRead();
       }
        memset(readcmd,0,64);
         defcnt=0;
         airmode =0;
         Serial.println("end"); 
         _osair.setMode(0);
        }    
    }
  ////////////////////////////
  }
void GetSerialCMD()//判断上位机串口命令
{
  char c = char(Serial.read()); //读取串口数据
  readcmd[cmdcnt++] = c;//保存接收字符
  //判断命令字
  if(cmdcnt==1)
  {
    if(readcmd[0]!='O')
    {
      cmdcnt=0;return; 
      }
  }else if(cmdcnt==2)
  {
    if(readcmd[1]!='S')
    {   
         cmdcnt=0;return; 
    }
    }else if(cmdcnt==3)
    {
      if(readcmd[2]!='M')
      {   
           cmdcnt=0;return;
      }
   }
  //命令结束
  if(c==0xa)
  {
      cmdcnt=0;    
      if(readcmd[3]=='0')
      {
         //配置AIR,将字符串直接发送给AIR        
          _osair.setMode(1);            
         airmode=1;
      }else if(readcmd[3]=='1')//
      {
        if(readcmd[5]=='M'&&readcmd[6]=='o'&&readcmd[7]=='d'&&readcmd[8]=='e')
        {//设置osbot工作模式
          char num[2];
          num[0]=readcmd[10];
          osbotmode = atoi(num);
          Serial.println(osbotmode); 
          Serial.println("end");
         }else if(readcmd[5]=='I'&&readcmd[6]=='O'&&readcmd[7]=='M'&&readcmd[8]=='A'&&readcmd[9]=='P')
         {//自定义配置，写入eeprom端口对应关系
          char num[3];
          char * p=readcmd+11;
          int i,j;
          for(j=0;j<6;j++)
          {
            for(i=0;i<3;i++)
            {
              if(*p=='.'||*p==0xa)
              break;
              num[i]=*p;p++;
            }
            p++;
            cfgBuff[j]=atoi(num);
            Serial.println(cfgBuff[j]);
            memset(num,0,3);
            }    
             Serial.println("end");      
          //wtCfg();
          }
          
           
      }     
  } 
}
void doAvoid()//避障函数
{
  unsigned char bL;
  unsigned char bR;
  if(SensorIndex[SENSOR_AVOID]>=6)
  return;
  bL = digitalRead(osPort[SensorIndex[SENSOR_AVOID]].IO1);
  bR = digitalRead(osPort[SensorIndex[SENSOR_AVOID]].IO2);
  if(bL>bR)
  {
      digitalWrite(MOTORDIR_L,1);//正转
      digitalWrite(MOTORDIR_R,0);//反转
      analogWrite(MOTORPWM_R,SPDNORM);
      analogWrite(MOTORPWM_L,SPDNORM);
    }else if(bL<bR){
      digitalWrite(MOTORDIR_L,0);//正转
      digitalWrite(MOTORDIR_R,1);//反转
      analogWrite(MOTORPWM_R,SPDNORM);
      analogWrite(MOTORPWM_L,SPDNORM);
      }else if(bL==0&&bR==0)
      {
        analogWrite(MOTORPWM_R,0);
        analogWrite(MOTORPWM_L,0);
      }else{
        digitalWrite(MOTORDIR_L,0);//正转
        digitalWrite(MOTORDIR_R,0);//反转
        analogWrite(MOTORPWM_R,SPDNORM);
        analogWrite(MOTORPWM_L,SPDNORM);
        }
   
  }
void doFdline()//循迹函数
{
  unsigned char bL;
  unsigned char bR;
  if(SensorIndex[SENSOR_FDLINE]>=6)
  return;
  digitalWrite(MOTORDIR_L,1);//正转
  digitalWrite(MOTORDIR_R,1);//正转
  bL = digitalRead(osPort[SensorIndex[SENSOR_FDLINE]].IO1);
  bR = digitalRead(osPort[SensorIndex[SENSOR_FDLINE]].IO2);
  if(bL>bR)
  {
      analogWrite(MOTORPWM_R,SPDSLOW);//右边减速
      analogWrite(MOTORPWM_L,SPDNORM);
    }else if(bL<bR){
      analogWrite(MOTORPWM_L,SPDSLOW);//左边减速
      analogWrite(MOTORPWM_R,SPDNORM);
      }
   
  }
void rdCfg()//读取配置
{
  int i=0;
  int address = 0;
  byte value;
  for(i=0;i<6;i++)
  {
    value = EEPROM.read(address);
    cfgBuff[i]=value;
    address++;
    if(0<=(int)value&&(int)value<40)
    {
      SensorIndex[value]=i;
      }
  }
  
 }
 void wtCfg()//存储配置
{
  int i=0;
  int address = 0;  
  for(i=0;i<6;i++)
  {
    EEPROM.write(address, cfgBuff[i]);
    address++;
    }
 }
void setface(unsigned char eye,unsigned char mth)//设置屏幕表情
{
  char cmd[128];
  faceCmd++;  
  setComx(0);
  if(faceCmd==1)
  {
      Serial.println(CLEARSRCN);
      mySerial.println(CLEARSRCN);//第一次需要清屏
      delay(100);     
    }
  sprintf(cmd,"ICON(20,20,%d,2,4,%d);ICON(120,20,%d,2,4,%d);",2+(eye/8),eye%8,4+(mth/8),mth%8);
    //if (mySerial.available())
  {
    Serial.println(cmd);
    mySerial.println(cmd);
    delay(200);
    airmode=0;
    } 
  
 }
 void setText(unsigned char r,unsigned char g,unsigned char b,int x,int y,char*txt)//显示文本
 {
    char cmd[128];
    setComx(0);
    faceCmd=0;//
    mySerial.println(CLEARSRCN);//清屏
  }
void setVoice(unsigned char mp3Index,unsigned char volunm)//设置声音及音量
{
  setComx(1);
  
  }
void setComx(unsigned char comid)//设置串口选择，把软串口通过D2、D3两根地址线扩展为4路串口
{
    if(comid==0)//选择0号串口
    {
      digitalWrite(2,0);
      digitalWrite(3,0);
      }else if(comid==1)//选择1号串口
      {
        digitalWrite(2,0);
        digitalWrite(3,1);
        }
}
