/*
 * osbeanair.cpp
 * Author: RG
 * Created: 2016-01-14
 */
#include <Arduino.h> 
#include <string.h>
#include "osair.h"


OSAIR::OSAIR(){
}

void OSAIR::init(){
	Serial1.begin(115200);
	m_cmdlen = 0;
	m_fn = NULL;
	m_lastRead = 0;
	m_mode = 0;
	sendCommand("reboot");
	delay(2000);
	setMode(0);
}

void OSAIR::analogRequest(char *pp){
 	char spin[3];
  	unsigned char pin = 0;
  	unsigned char val = 0;
  
  	spin[0] = pp[1];
  	spin[1] = pp[2];
  	spin[2] = 0;
  	pin = atoi(spin);
  
  	switch(pp[0]){
    		case 'W': // PWM
       			val = atoi(pp+3);
       			analogWrite(pin, val);
       	 	break;        
    		case 'R': // AnalogRead
   		{
      			/* A0=18 */
      			int v = analogRead(pin+18);
      			char buf[10];
      			sprintf(buf, "@ A%02d%d", pin, v);
      			Serial1.println(buf);
      		}
       		break;
  	}      
}


void OSAIR::digitalRequest(char *pp){
  	char spin[3];
  	unsigned char pin = 0;
  	unsigned char val = 0;
 
	spin[0] = pp[1];
  	spin[1] = pp[2];
  	spin[2] = 0;
  	pin = atoi(spin);
  
  	switch(pp[0]){
    		case 'W':
        		val = atoi(pp+3);
        		if(val != 0)
            			val = 1;
         		pinMode(pin, OUTPUT);
        		digitalWrite(pin, val);
        		val = digitalRead(pin);
      
			char buf[10];
      			sprintf(buf, "D%02d%d", pin, val);
			sendText(buf);
        	break;        
    		case 'R':
    		{
      			int v = digitalRead(pin);
      			char buf[10];
      			sprintf(buf, "D%02d%d", pin, v);
			sendText(buf);
      		}
   
        	break;
  	}      
}

void OSAIR::doRequest(){
  	char *pp;
  //Serial.print("ReceivedCMD:<");
  //	Serial.print((char*)m_cmdbuf);
  //	Serial.print(">\r\n");
  	m_cmdbuf[m_cmdlen] = 0;
  	if(m_cmdlen == 0){
      		return ;
  	}
  	if(m_cmdbuf[0] != '@'){
		if(m_fn)
			m_fn(pp);
		m_cmdlen = 0;
	}

 	if(m_cmdlen<2 || m_cmdlen>30){
  		m_cmdlen = 0;
    		return;
  	}
  
  	pp = (char*)m_cmdbuf+1;

  	

  	if(pp[0] == 'A'){
    		analogRequest(pp+1);
  	}
  	else if(pp[0] == 'D'){
    		digitalRequest(pp+1);
  	}
	else{
		if(m_fn)
			m_fn(pp);
	}
  
  	m_cmdlen = 0;
}

void OSAIR::loop(){
  	if(m_mode ==0 && Serial1.available()){
    		unsigned char c = (unsigned char)Serial1.read();
    	//	Serial.print((char)c);
    		if(c=='\n'){
        		doRequest();
    		}else if(c=='\r'){
    		}else{
      			m_cmdbuf[m_cmdlen] = c;
      			m_cmdlen ++;
      			if(m_cmdlen>=32){
        			m_cmdlen = 0;
      			}
    		}
  	}
	else if(m_mode == 1){
  		if (Serial.available()) {
	   		unsigned char c = (unsigned char)Serial.read();
	    		Serial1.write(c);
	  	}
  		if (Serial1.available()) {
    			unsigned char c = (unsigned char)Serial1.read();
    			Serial.write(c);
  		}
	}

	if(m_controlPin ==18){
		long m_now = millis()/1000;
		if((m_now-m_lastRead) > 2){
			int v = analogRead(18);//��ȡA0
			
			if(v >1000&&!m_mode)
				{
					setMode(1);
					Serial.println(v);
					}
				
			else if(v<=1000&&m_mode==1)
				{
					setMode(0);
					Serial.println(v);
					}
				

			m_lastRead = m_now;
		}
	}
}

void OSAIR::sendText(char *buf, int len){
	Serial1.write("@ ");
	if(len == 0)
		len = strlen(buf);
	Serial1.write((uint8_t*)buf, len);
	Serial1.write("\r\n");
}

void OSAIR::sendCommand(char *cmd, char *param){
	if(param == NULL)
		Serial1.println(cmd);
	else{
		Serial1.print(cmd);
		Serial1.print(" ");
		Serial1.println(param);
	}	
}
void OSAIR::publish(char *topic, char *body){
	Serial1.write("$PUB ");
	if(body){
		Serial1.write(topic);
		Serial1.write("|");
		Serial1.println(body);
	}
	else
		Serial1.println(topic);
}
void OSAIR::subscribe(char *topic){
	Serial1.write("$SUB ");
	Serial1.println(topic);
}


void OSAIR::setHandler(void(*fn)(char*)){
	m_fn = fn;
}
void OSAIR::setMode(unsigned char v_mode){
	m_mode = v_mode;
	if(m_mode == 1){
		//sendText("@@EnterCommandMode");
		//delay(5);
		sendCommand("echo");
	//	Serial.begin(115200);
	}
	else{
		//sendText("@@EnterMessageMode");
		//delay(5);
		sendCommand("noecho");
	}
}
void OSAIR::setControlPin(unsigned char v_pin){
	if(v_pin > 2){
		m_controlPin = v_pin;
		pinMode(m_controlPin, INPUT);
	}
}
void OSAIR::setLoadMode(){
	
		m_controlPin = 18;

	
}
unsigned char OSAIR::getMode(){
	return m_mode;
}
