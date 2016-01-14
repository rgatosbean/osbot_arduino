/*
 * osair.h
 * Author: Jianbing Qu
 * Created: 2015-07-21
 */
 

class OSAIR {
public:
	OSAIR();
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
