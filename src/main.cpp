#include <Arduino.h>
#include <SPI.h> 

#include <BMP388.h>


float estimate_altitude(float pressure, float temperature){
  // assume a P0 of 101325
  float altitude = ((pow(101325/pressure,1/5.257) - 1) * (temperature + 273.15))/0.0065; 
  return altitude;
}

BMP388 bmp; 
BMP388::BMP388_data bmp_data; 
void setup() {
  // put your setup code here, to run once:
  SPI.begin(); 
  Serial.begin(115200); 
  delay(2000);
  Serial.println("BMP init status: " + String(bmp.begin(PA0)));
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000); 
  bmp.get_new_data(&bmp_data); 
  Serial.println("Temperature: " + String(bmp_data.temperature));
  Serial.println("Pressure: " + String(bmp_data.pressure));
  Serial.println("Estimated Sea Level: " + String(estimate_altitude(bmp_data.pressure, bmp_data.temperature))); 
  Serial.println(); 
}