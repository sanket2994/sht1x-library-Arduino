#include<Arduino.h>
#include <sht11.h>

int data=10,clk=11; //set the SDA = PIN 10  & SCL = PIN11 ; 
//#define data 10
//#define clk 11
float readTempC()
{
  int obtVal;
  float temp;
  
  //Temoerature constants for sht11 at 14bit
  const float D1 =-39.7 ; //at 3.3v
  const float D2 =0.01;   //for 14 bits
  
  obtVal=getTempfrmSensor(); //get the temperature reading from sensor (raw data) 
  
  skipCRC(); //skip performing crc
  
  temp=D1+(D2*obtVal);  //calculation for temperature given in data sheet
  
  return temp;
}

float readTempF()
{
	int obtval;
	float temp;
	
	const float D1 = 39.5 ; //at 3.3V
	const float D2 = 0.018; //for 14 bit data
	
	obtVal=getTempfrmSensor(); //get the reading from sensor (raw data)
	
	skipCRC(); //skip performing CRC
	
	temp= D1 +(D2*obtVal); //calculation for temperature given in datasheet
	
	return temp;
}
float readHumidity()
{
  int obtVal,obtValTemp;
  float relHumidity;
  float HumidityTemp;
  
  //Humidity constants for 12 bit
  const float c1 = -2.0468; 
  const float c2 = 0.0367; 
  const float c3 = 0.00000155; //-1.5955e-6
 
 //Temperature constants for 12 bit 
  const float t1 = 0.01;   //for 12 bit
  const float t2 = 0.00008;//for 12 bit
  
  obtVal=getHumidityfrmSensor();  //get the sensor reading raw data for humidity
  skipCRC();
  relHumidity= c1 + (c2*obtVal) + (c3*obtVal*obtVal); //convert it into relative humidity for linear compensation
  
  obtValTemp=readTemp(); //get the senor reading raw data for temp
  skipCRC();
  HumidityTemp=(obtValTemp-25.0)*(t1+t2*obtVal)+relHumidity;  // calculate relative humidity with temperature compensation 
  
  return HumidityTemp;
}
 

  
int getTempfrmSensor()
{
  pinMode(data,INPUT);
  pinMode(clk,OUTPUT);
  
  int cmd= 0b00000011;
  
  sendCmd(cmd);    //Send command to read temperature from sensor
  
  waitForResult(); //wait till sensor finishes reading data
  
  int val=ShiftIn(); //read the data from the Sensor
  
  return val;
}   


//Read Humidity from the Sensor
int getHumidityfrmSensor()
{
  pinMode(data,INPUT);
  pinMode(clk,OUTPUT);
  //int val,i,read=0;
  int cmd = 0b000000101; // cmd to read humidity
  sendCmd(cmd);  // sendcmd to read humidity to sensor
  
  waitForResult(); //poll untill sensor has finished measuring data 
  
  int val=ShiftIn(); //read the data from sensor
  return val;
  
} 
  
//Send the command to read temp or humidity to microcontroller  
void sendCmd(int cmd)
{
  int ack;
  pinMode(data,OUTPUT);
  pinMode(clk,OUTPUT);
  
  //Initiate the start signal to sensor
  digitalWrite(data,HIGH);
  digitalWrite(clk,HIGH);
  digitalWrite(data,LOW);
  digitalWrite(clk,LOW);
  digitalWrite(clk,HIGH);
  digitalWrite(data,HIGH);
  digitalWrite(clk,LOW);
 
  
  shiftOut(data,clk,MSBFIRST,cmd); // send the command to sensor
  
  digitalWrite(clk,HIGH); 
  pinMode(data,INPUT);
  
  //Check acknowlwdgement if the sensor has ack the cmd
  if(digitalRead(data)!=LOW)
  {
    //Serial.println("Error: ack not received");//error;
  }
  digitalWrite(clk,LOW);
  //check if sensor has started measuring data after ack 
  if(digitalRead(data)!=HIGH)
  {
    //Serial.println("Error : not able to measure");
  }
}
  
  // pooling for the sensor to complete measuring data
void waitForResult() 
{
  
  int i,flag=0,ack;
  pinMode(data,INPUT);
  ack=digitalRead(data);
  for(i=0;i<1000;i++)
  {
    delay(10);
    ack=digitalRead(data);
    if(ack==LOW)
    {
      //flag=1;
      break;
    }
  }
  if(ack==HIGH){
    //Serial.println("Error: while giving measurement");
    }
 
  else
  return;
} 
 
//Read measurement from sensor
int ShiftIn() 
{
  pinMode(data,INPUT);
  pinMode(clk,OUTPUT);
  int i,val1,read1=0;
  read1=shiftIn(data,clk,MSBFIRST); // read MSB byte
  val1=(read1<<8);//read1*256;
  
  //Send acknowledgement to sensor that MSB byte is read
  pinMode(data,OUTPUT);
  digitalWrite(data,HIGH); 
  digitalWrite(data,LOW);
  digitalWrite(clk,HIGH);
  digitalWrite(clk,LOW);
  
  pinMode(data,INPUT);
  pinMode(clk,OUTPUT);
  read1=0;
  read1=shiftIn(data,clk,MSBFIRST); //read LSB byte of from the sensor
  val1|=read1; //add LSB to MSB

  return val1; //return the read value from sensor
}
 
//Skip the CRC 
void skipCRC()
{
  pinMode(data,OUTPUT);
  pinMode(clk,OUTPUT);
  
  digitalWrite(data,HIGH);
  digitalWrite(clk,HIGH);
  digitalWrite(clk,LOW);
} 
