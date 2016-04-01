#include <TimerOne.h>
#include <SoftwareSerial.h>

#define S0     3   // Please notice the Pin's define
#define S1     4
#define S2     5
#define S3     6
#define OUT    2
#define CLEARSRCN  "CLS(0);"    //清空液晶屏  
int   g_count = 0;    // count the frequecy
int   g_array[3];     // store the RGB value
int   g_flag = 0;     // filter of RGB queue
float g_SF[3];        // save the RGB Scale factor
unsigned char sflag = 0;
 SoftwareSerial mySerial(10, 9); // 软件模拟串口10为RX, 9为TX 
// Init TSC230 and setting Frequency.
void TSC_Init()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
 
  digitalWrite(S0, LOW);  // OUTPUT FREQUENCY SCALING 2%
  digitalWrite(S1, HIGH); 
}
 
// Select the filter color 
void TSC_FilterColor(int Level01, int Level02)
{
  if(Level01 != 0)
    Level01 = HIGH;
 
  if(Level02 != 0)
    Level02 = HIGH;
 
  digitalWrite(S2, Level01); 
  digitalWrite(S3, Level02); 
}
 
void TSC_Count()
{
  g_count ++ ;
}
 
void TSC_Callback()
{
  switch(g_flag)
  {
    case 0: 
         //Serial.println("->WB Start");
         TSC_WB(LOW, LOW);              //Filter without Red
         break;
    case 1:
         //Serial.print("->Frequency R=");
         //Serial.println(g_count);
         g_array[0] = g_count;
         TSC_WB(HIGH, HIGH);            //Filter without Green
         break;
    case 2:
         //Serial.print("->Frequency G=");
         //Serial.println(g_count);
         g_array[1] = g_count;
         TSC_WB(LOW, HIGH);             //Filter without Blue
         break;
 
    case 3:
         //Serial.print("->Frequency B=");
         //Serial.println(g_count);
         //Serial.println("->WB End");
         g_array[2] = g_count;
         TSC_WB(HIGH, LOW);             //Clear(no filter)   
         break;
   default:
         g_count = 0;
         g_flag = 0;
         break;
  }
}
 
void TSC_WB(int Level0, int Level1)      //White Balance
{
  g_count = 0;
  g_flag ++;
  TSC_FilterColor(Level0, Level1);
  Timer1.setPeriod(1000000);             // set 1s period
}
 
void setup()
{
  TSC_Init();
  Serial.begin(115200);delay(100);
  mySerial.begin(115200); 
 
}
 
void loop()
{
  char col[4]="rgb";
  unsigned long colorbuf[4];
  
  if(!sflag)
  {
    if(analogRead(A0)>950)
    {
      sflag=1;
      startTSC();
         
      }
      delay(200);
    }else{
      //g_flag = 0;
   for(int i=0; i<3; i++)
   {
    colorbuf[i]=int(g_array[i]*g_SF[i]);
    if(colorbuf[i]>255)
    colorbuf[i]=255;
    Serial.print(col[i]);
    Serial.print(":");
    Serial.println(colorbuf[i]);    
    }
    DisplayColor(colorbuf[0]*32/256,colorbuf[1]*64/256,colorbuf[2]*32/256);
    delay(4000);
      }  
 
}
void startTSC()
{
  TSC_Init();
  Timer1.initialize();             // defaulte is 1s
  Timer1.attachInterrupt(TSC_Callback);  
  attachInterrupt(1, TSC_Count, RISING);  
 
  delay(4000);
 
  for(int i=0; i<3; i++)
    Serial.println(g_array[i]);
 
  g_SF[0] = 255.0/ g_array[0];     //R Scale factor
  g_SF[1] = 255.0/ g_array[1] ;    //G Scale factor
  g_SF[2] = 255.0/ g_array[2] ;    //B Scale factor
 
  Serial.println(g_SF[0]);
  Serial.println(g_SF[1]);
  Serial.println(g_SF[2]);
  mySerial.println(CLEARSRCN);//第一次需要清屏
      delay(100);  
  }
void DisplayColor(unsigned long r,unsigned long g,unsigned long b)
{
  char cmd[128];  
  unsigned long color = ((r&0x1f)<<11)+((g&0x3f)<<5)+(b&0x1f);
  color&=0xffff;
  Serial.print("color is:");
  Serial.println((r&0x1f)<<11,HEX);Serial.println((g&0x3f)<<5,HEX);Serial.println(b&0x1f,HEX);
  Serial.println(color);
  sprintf(cmd,"SCC(16,%ld);",color);  
  mySerial.println(cmd);delay(100); 
  sprintf(cmd,"CBOF(20,20,100,100,5,16);");
   // sprintf(cmd,"DS24(0,0,'r:%dg:%db:%d',4);",r,g,b);
  mySerial.println(cmd);delay(100); 
    
  }

