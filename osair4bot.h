/*
 * OSAIR4bot.h
 * Author: RG
 * Created: 2016-01-14 
 */
#define SPDNORM  100     //正常速度，循迹直行
#define SPDSLOW  60      //较慢速度，循迹转弯
#define BOTCODEMODE  0    //编程模式
#define BOTAVOIDMODE 1    //避障模式
#define BOTFDLINEMODE 2   //循迹模式
#define BOTDANCEMODE 3    //舞蹈模式
#define CLEARSRCN  "CLS(15);"    //清空液晶屏 

#define MOTORDIR_L 4//左边马达方向控制
#define MOTORDIR_R 7//右边马达方向控制
#define MOTORPWM_L 5//左边马达速度控制
#define MOTORPWM_R 6//右边马达速度控制

#define SENSOR_SCREEN 0   //显示模块序号
#define SENSOR_AVOID 1    //避障模块序号
#define SENSOR_FDLINE 2   //循迹模块序号
#define SENSOR_SPDTST 3   //码盘测速模块序号
#define SENSOR_RELAY 4    //继电器模块序号
#define SENSOR_UTRSONIC 5 //超声波模块序号

typedef struct
{
    uint8_t IO1;
    uint8_t IO2;
} OsPort_Sig;
extern OsPort_Sig osPort[6];

class OSAIR4bot {
public:
	OSAIR4bot();
	void loop();
	void sendText(char *pp, int len=0);
	void sendCommand(char *cmd, char *param=0);
	void publish(char *topic, char *body=0);
	void subscribe(char *topic);
	void setHandler(void(*fn)(char*));
	void setMode(unsigned char v_mode);
	void setControlPin(unsigned char v_pin);
	void setLoadMode();
	unsigned char getMode();
	void init();
	void airConfig(char *pp);
	unsigned char airRead();
private:
	void analogRequest(char *pp);
	void digitalRequest(char *pp);
	void doRequest();
private:
	unsigned char m_cmdlen = 0;
	unsigned char m_mode = 0;
	unsigned char m_cmdbuf[32];
	unsigned char m_controlPin = 0;
	long m_lastRead = 0;
	void(*m_fn)(char *);
};
