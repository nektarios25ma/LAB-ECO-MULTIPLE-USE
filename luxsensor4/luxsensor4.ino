#include <BH1750FVI.h>
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
#include <PCD8544.h>
 PCD8544 lcd;
 #include "DHT.h"

float h, t;
DHT DHT_sens(2, DHT11); // datapin sensor connected to pin 2 Arduino

void setup() 
{
  DHT_sens.begin();
  Serial.begin(9600);
  LightSensor.begin();
  lcd.begin(84, 48);
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME  ");
  lcd.setCursor(0, 1);
  lcd.print("     To");
  lcd.setCursor(0,2);
  lcd.print("EkfeChanion");
  lcd.setCursor(0,3);
 // lcd.begin(16,2);
 lcd.print("  BH1750 Light  ");
  lcd.setCursor(0,4);
  lcd.print("Intensity ... Sensor");
  delay(2000);  
}
void loop()
{
  uint16_t lux = LightSensor.GetLightIntensity();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println("Lux");
  h = DHT_sens.readHumidity();
t = DHT_sens.readTemperature();

//delay (1000); // pause a second
Serial.print ("Humidity: ");
Serial.print (h,0); // zero decimal
Serial.print (" %\t");
Serial.print ("Temperature: ");
Serial.print (t,1); // one decimal
Serial.println (" *C");
delay (50); // pause a...

  lcd.clear();
  lcd.print("Intensity in.. LUX:");
   lcd.setCursor(6,2);
   lcd.print(lux);
   lcd.setCursor(0,3);
   lcd.print ("Humidity:");
  // lcd.setCursor(10,3);
   lcd.print (h,0); // zero decimal
  // lcd.setCursor(12,3);
  lcd.print ("%");
   lcd.setCursor(0,4);

lcd.print ("Temp:");
//lcd.setCursor(6,4);
lcd.print (t,1); // one decimal
//lcd.setCursor(10,4);
lcd.println ("*C");
  delay(1000);
}
