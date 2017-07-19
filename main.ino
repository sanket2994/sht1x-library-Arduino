extern "C"{
  #include <sht11.h>
}

int data,clk;
void setup() {
  Serial.begin(38400);
  Serial.println("Start the SHT11 sensor");

}
void loop() 
{
    float tempValC,tempValF;
    float humVal;

    tempValC = readTempC(data,clk);
    tempValF= readTempF(data,clk);
    humVal = readHumidity(data,clk);

    Serial.print("Temperature in celcius: "); 
    Serial.println(tempValC,DEC);
    
    Serial.print("Temperature in Farhenite : "); 
    Serial.println(tempValF,DEC);
  
    Serial.print("Humidity:");
    Serial.println(humVal,DEC);

  delay(2000);
}
