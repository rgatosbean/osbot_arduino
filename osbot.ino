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

#define LOOPTIP 2

int cntNocamd=0;//闲置状态计数
bool isComwork=0;//串口工作标志
int cntVirbtn = 0;//虚拟按钮计数，当两个避障传感器都有信号时开始计数

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
unsigned char txtbuf[5];
unsigned char oldmp3=0;
unsigned char oldvol=0;
void OSWfunc(char*pp)//自定义函数处理网络数据
{
  char rcvnum[3];  
  Serial.println(pp); 
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
      mySerial.begin(115200); 
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
      setface(k+2,j);//眼睛和嘴巴对应图标索引号      
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
        mySerial.begin(115200); 
        memset(rcvnum,0,3);
        char *p=pp+7;
        Serial.println(p);
        setText(txtbuf[0],txtbuf[1],txtbuf[2],txtbuf[3],txtbuf[4],p);
        }else if(atoi(rcvnum)==4)//播放声音文件
      {
        mySerial.begin(9600); 
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
  unsigned char cmd[6];
  _osair.init();//初始化对象实例
  Serial.begin(115200);//打开串口用于监视
  _osair.setLoadMode();//设置烧写模式，可更新固件
  _osair.setHandler(OSWfunc);//设置自定义函数句柄
  delay(200);  
  rdCfg();//读取RJ25端口配置
  pinMode(MOTORDIR_L,OUTPUT);
  pinMode(MOTORDIR_R,OUTPUT);
  pinMode(MOTORPWM_L,OUTPUT);
  pinMode(MOTORPWM_L,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  mySerial.begin(9600); 
  setComx(1);
  cmd[0]=0x7E;cmd[1]=0x03;cmd[2]=0x35;cmd[3]=0x01;cmd[4]=0xEF;  //切换到tf卡播放模式  
  mySerial.write(cmd,5); delay(100);  
  setVoice(1,15);delay(100);
  mySerial.begin(115200); 
  setface(2,0);delay(100);
  
}
void loop() {
  unsigned char mL=1-digitalRead(A2);
  unsigned char mR=1-digitalRead(A3);
    if(!isComwork)
    {    doAvoid(mL,mR);
         delay(LOOPTIP);
         if(mL==0&&mR==0)
        {
          digitalWrite(13,0);
          cntNocamd++;
          if(cntNocamd>9000)
          {
            cntNocamd=0;
            setMode(100);//睡眠模式           
            delay(200);
            }
          if(cntVirbtn>2000)
            {
              setMode(BOTDANCEMODE);//舞蹈模式
              delay(100);
              }else if(cntVirbtn>1200)
              {
                setMode(BOTFDLINEMODE);//循迹模式
                delay(100);
                }else if(cntVirbtn>10)
                {
                  setMode(BOTCODEMODE);//编程模式
                  delay(100);
                  }
                  cntVirbtn=0;   
          }else if(mL==1&&mR==1)
          {
            cntVirbtn++;
            cntNocamd=0; 
            digitalWrite(13,1);     
                  
            }
      }
  
  
  if(osbotmode==BOTCODEMODE)//编程模式
  {
    ////////////////////////////
  if(airmode==0)//接收上位机串口命令
  {  
    delay(1); 
    if(Serial.available())
      GetSerialCMD();    
    }else if(airmode==1){
      isComwork=1;
      defcnt++;   
      delay(1);
      if(defcnt==1)
      {        
        _osair.airConfig(readcmd+5);//向8266发送配置命令    
        digitalWrite(13,0);         
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
                digitalWrite(13,m_now%2);  
         }
         digitalWrite(13,0);  
          memset(readcmd,0,64);
           defcnt=0;
           airmode =0;
           isComwork=0;
           Serial.println("end"); 
           _osair.setMode(0);
          }    
      }
    ////////////////////////////
    
    }else if(osbotmode==BOTAVOIDMODE)//壁障模式
    {
      
      }else if(osbotmode==BOTFDLINEMODE)//循迹模式
      {
        doFdline();
        }else if(osbotmode==BOTDANCEMODE)//舞蹈模式
        {
          
          }
  // put your main code here, to run repeatedly:
_osair.loop();//ARDUINO AIR主循环函数

  }
void GetSerialCMD()//判断上位机串口命令
{
  char c = char(Serial.read()); //读取串口数据
  readcmd[cmdcnt++] = c;//保存接收字符
  //判断命令字
  if(cmdcnt==1)
  {
    //Serial.println("rec");
    digitalWrite(13,0);
    if(readcmd[0]!='O')
    {
      cmdcnt=0;return; 
      }
  }else if(cmdcnt==2)
  {
    digitalWrite(13,1);
    if(readcmd[1]!='S')
    {   
         cmdcnt=0;return; 
    }
    }else if(cmdcnt==3)
    {
      digitalWrite(13,0);
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
         digitalWrite(13,1);
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
          wtCfg();//写入端口配置信息
          rdCfg();//读出端口配置信息
          }
          
           
      }     
  } 
}
void doAvoid(unsigned char bL,unsigned char bR)//避障函数
{
  //int bL;
  //int bR;
  //if(SensorIndex[SENSOR_AVOID]>=6)
  //return;
  //bL = 1-digitalRead(osPort[SensorIndex[SENSOR_AVOID]].IO1);
  //bR = 1-digitalRead(osPort[SensorIndex[SENSOR_AVOID]].IO2);
  //bL=1-digitalRead(A2);
  //bR=1-digitalRead(A3);  
  
  //char cmd[50];
  //sprintf(cmd,"left=%d right=%d",bL,bR);
  //Serial.println(cmd);
  //return;
  if(bL==1&&bR==0)//右转
  {
      digitalWrite(MOTORDIR_L,0);//向后
      digitalWrite(MOTORDIR_R,0);//向前
      analogWrite(MOTORPWM_R,SPDNORM);
      analogWrite(MOTORPWM_L,SPDNORM);
      delay(100);
    }else if(bL==0&&bR==1){//左转
      
      digitalWrite(MOTORDIR_L,1);//向前
      digitalWrite(MOTORDIR_R,1);//向后      
      analogWrite(MOTORPWM_R,SPDNORM);
      analogWrite(MOTORPWM_L,SPDNORM);
      delay(100);
      }else if(bL==0&&bR==0)
      {
        digitalWrite(MOTORPWM_R,0);
        digitalWrite(MOTORPWM_L,0);
      }else{
        digitalWrite(MOTORPWM_R,0);
        digitalWrite(MOTORPWM_L,0);
        //digitalWrite(MOTORDIR_L,1);//向后
        //digitalWrite(MOTORDIR_R,0);//向后
        //analogWrite(MOTORPWM_R,SPDNORM);
        //analogWrite(MOTORPWM_L,SPDNORM);
        }
   
  }
void doFdline()//循迹函数
{
  unsigned char bL;
  unsigned char bR;
  //if(SensorIndex[SENSOR_FDLINE]>=6)
  //return;
  digitalWrite(MOTORDIR_L,1);//正转,测试用反转
  digitalWrite(MOTORDIR_R,0);//正转
  //bL = digitalRead(osPort[SensorIndex[SENSOR_FDLINE]].IO1);
  //bR = digitalRead(osPort[SensorIndex[SENSOR_FDLINE]].IO2);
  bL = 1-digitalRead(10);
  bR = 1-digitalRead(9);
  if(bL>bR)
  {
      analogWrite(MOTORPWM_R,SPDSLOW);//右边减速
      analogWrite(MOTORPWM_L,SPDNORM);
    }else if(bL<bR){
      analogWrite(MOTORPWM_L,SPDSLOW);//左边减速
      analogWrite(MOTORPWM_R,SPDNORM);
      }else if(bL==0&&bR==0)
      {
        analogWrite(MOTORPWM_L,SPDNORM);//左边减速
        analogWrite(MOTORPWM_R,SPDNORM);
        }else{
          analogWrite(MOTORPWM_L,0);//左边减速
        analogWrite(MOTORPWM_R,0);
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
  Serial.println(osPort[SensorIndex[SENSOR_AVOID]].IO1);
  Serial.println(osPort[SensorIndex[SENSOR_AVOID]].IO2);
  Serial.println(osPort[SensorIndex[SENSOR_FDLINE]].IO1);
  Serial.println(osPort[SensorIndex[SENSOR_FDLINE]].IO2);
  Serial.println("read portcfg ok!");
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
  //sprintf(cmd,"ICON(0,0,%d,2,4,%d);",2+(eye/8),eye%8);
  sprintf(cmd,"PIC(0,0,%d);",eye);
    //if (mySerial.available())
  {
    Serial.println(cmd);
    mySerial.println(cmd);
    delay(100);
    airmode=0;
    } 
  
 }
 void setText(unsigned char r,unsigned char g,unsigned char b,int x,int y,char*txt)//显示文本
 {
    char cmd[128];
    setComx(0);
    faceCmd=0;//
    mySerial.println(CLEARSRCN);//清屏
    //DS16(20,40,'Hello!',1);
    sprintf(cmd,"DS24(%d,%d,'%s',4);",x,y,txt);
    Serial.println(cmd);
    mySerial.println(cmd);
    delay(100);
  }
void setVoice(unsigned char mp3Index,unsigned char volunm)//设置声音及音量
{
  unsigned char cmd[6]; 
  int i;
  setComx(1);
  if(oldvol!=volunm)//设置音量
  {
    cmd[0]=0x7E;cmd[1]=0x03;cmd[2]=0x31;cmd[3]=volunm;cmd[4]=0xEF;    
    mySerial.write(cmd,5);  delay(100);
      Serial.println("set volunm !");    
  }  
   // if(oldmp3!=mp3Index)//播放声音
    {
      cmd[0]=0x7E;cmd[1]=0x04;cmd[2]=0x41;cmd[3]=0x0;cmd[4]=mp3Index;cmd[5]=0xEF;
      mySerial.write(cmd,6); delay(100);
        Serial.println("play sound !");
      }
   oldvol=volunm;
  // oldmp3=mp3Index;
  }
void setComx(unsigned char comid)//设置串口选择，把软串口通过D2、D3两根地址线扩展为4路串口
{
    if(comid==0)//选择0号串口
    {
      digitalWrite(2,0);
      digitalWrite(3,0);
      Serial.println("choose com0.");
      }else if(comid==1)//选择1号串口
      {
        digitalWrite(2,0);
        digitalWrite(3,1);
        Serial.println("choose com1.");
        }
}
void setMode(unsigned char botMode)
{
  char cmd[128]; 
    if(osbotmode==botMode)
        return;
    else
        osbotmode=botMode;
        isComwork = 1;
     mySerial.begin(9600); 
    if(osbotmode==BOTCODEMODE)
    {
      setVoice(3,15);delay(100);
      sprintf(cmd,"BPIC(3,0,0,3);PS32(3,50,156,'CODE MODE!',15,200)");
      }else if(osbotmode==BOTFDLINEMODE)
      {
        setVoice(13,15);delay(100);
        sprintf(cmd,"BPIC(4,0,0,4);PS32(4,50,16,'FIND LINE MODE!',15,200)");
        }else if(osbotmode==BOTDANCEMODE)
        {
          setVoice(27,15);delay(100);
          sprintf(cmd,"BPIC(5,0,0,5);PS32(5,50,156,'DANCING MODE!',15,200)");
          }else if(osbotmode==100)
          {
            setVoice(23,15);delay(100);
          sprintf(cmd,"BPIC(6,0,0,6);PS32(5,50,156,'SLEEP MODE!',15,200)");
          osbotmode=2;
            }
    mySerial.begin(115200); 
    setComx(0);
    mySerial.println(cmd);
  delay(100);   
  isComwork = 0;
  }

