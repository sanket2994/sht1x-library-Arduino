# sht1x-library-Arduino
This is a library in c for sht1x sensor for Arduino

This is a library in c which contains the following functions:

1. float readTempC();	//calc temp in celcius
    Include this function in your main file to get the temperature values in celcius
    note that the calculation is done considering 14-bit raw data

2. float readTempF();	//calculate temp in farhenite
    Include this function in your main file to get the temperature values in farhenite
    note that the calculation is done considering 14-bit raw data

3. float readHumidity();	//calculate relative humidity
    Include this function in your main file to calculate the humidity.
    The calculation is done for 12 bit raw data.
    Also the function returns temperature compensated humidity.
    refer the datasheet for details.
    
No need to include the following functions in the main as they re internally called by the above functions
4. int getTempfrmSensor();	//get temperature raw data
    Get the 14-bit raw data from sensor to calculate temperature

5. int getHumidityfrmSensor();	//get humidity raw data
    Get the 12-bit raw data from sensor to caculate humidity
    
6. void sendCmd(int );	//send command to start measurement
    send a command to sensor to start measuring temperature or humidity.
    cmd_temp=00011;
    cmd_humidity=00101;
   

7. void waitForResult();	//wait till sensor has finished measuring data
    Waiting for sensor to complete measuring the data and acknowledging the completion of measurement by pulling the data line low

8. void skipCRC();		//skip the CRC check
    Skip the CRC check.


Note: Since this is a c library while including the header file in your code do it in:
extern "c"{
    #include<sht11.h>
    }
