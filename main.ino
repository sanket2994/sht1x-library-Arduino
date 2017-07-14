extern "C"{
  #include <sht11.h>
}

void setup() {
  Serial.begin(38400);
  Serial.println("Start the SHT11 sensor");

}
void loop() 
{
    float tempVal;
    float humVal;

    tempVal = readTemp();
    humVal = readHumidity();

    Serial.print("Temperature: "); 
    Serial.println(tempVal,DEC);
    Serial.print("Humidity:");
    Serial.println(humVal,DEC);

  delay(2000);
}
