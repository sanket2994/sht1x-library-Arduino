#include<Arduino.h>

float readTempC(int ,int);	//calc temp in celcius
float readTempF(int, int);	//calculate temp in farhenite
float readHumidity(int ,int);	//calculate relative humidity
int getTempfrmSensor(int, int);	//get temperature raw data
int getHumidityfrmSensor(int, int);	//get humidity raw data
void sendCmd(int, int, int);	//send command to start measurement
void waitForResult(int, int);	//wait till sensor has finished measuring data
void skipCRC(int, int);		//skip the CRC check
