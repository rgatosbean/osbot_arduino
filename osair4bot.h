/*
 * OSAIR4bot.h
 * Author: RG
 * Created: 2016-01-14 
 */
#define SPDNORM  100     //�����ٶȣ�ѭ��ֱ��
#define SPDSLOW  60      //�����ٶȣ�ѭ��ת��
#define BOTCODEMODE  0    //���ģʽ
#define BOTAVOIDMODE 1    //����ģʽ
#define BOTFDLINEMODE 2   //ѭ��ģʽ
#define BOTDANCEMODE 3    //�赸ģʽ
#define CLEARSRCN  "CLS(15);"    //���Һ���� 

#define MOTORDIR_L 4//�����﷽�����
#define MOTORDIR_R 7//�ұ���﷽�����
#define MOTORPWM_L 5//�������ٶȿ���
#define MOTORPWM_R 6//�ұ�����ٶȿ���

#define SENSOR_SCREEN 0   //��ʾģ�����
#define SENSOR_AVOID 1    //����ģ�����
#define SENSOR_FDLINE 2   //ѭ��ģ�����
#define SENSOR_SPDTST 3   //���̲���ģ�����
#define SENSOR_RELAY 4    //�̵���ģ�����
#define SENSOR_UTRSONIC 5 //������ģ�����

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
