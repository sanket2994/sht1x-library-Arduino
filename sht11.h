#include<Arduino.h>

float readTempC();	//calc temp in celcius
float readTempF();	//calculate temp in farhenite
float readHumidity();	//calculate relative humidity
int getTempfrmSensor();	//get temperature raw data
int getHumidityfrmSensor();	//get humidity raw data
void sendCmd(int );	//send command to start measurement
void waitForResult();	//wait till sensor has finished measuring data
void skipCRC();		//skip the CRC check
