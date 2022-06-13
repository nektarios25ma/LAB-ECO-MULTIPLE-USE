#include <Arduino.h>
#include "MHZ19.h"                                        
#include <SoftwareSerial.h>                                // Remove if using HardwareSerial
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"

// Example for demonstrating the TSL2591 library - public domain!

// connect SCL to I2C Clock
// connect SDA to I2C Data
// connect Vin to 3.3-5V DC
// connect GROUND to common ground

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); //2591//pass in a number for the sensor identifier (for your use later)

#define RX_PIN 10                                         // Rx pin which the MHZ19 Tx pin is attached to 10
#define TX_PIN 11                                          // Tx pin which the MHZ19 Rx pin is attached to 11
#define BAUDRATE 9600                                      // Device to MH-Z19 Serial baudrate (should not be changed)
#define pinFUN 5   
#define pinBUZZ 6  
MHZ19 myMHZ19;                                             // Constructor for library
SoftwareSerial mySerial(RX_PIN, TX_PIN);                   // (Uno example) create device to MH-Z19 serial
   
unsigned long getDataTimer = 0;
 // Δημιούργησε μια μεταβλητή τύπου unsigned long integer με όνομα start_time2
unsigned long start_time2; 


 #include "DHT.h"

float h, t;
DHT DHT_sens(2, DHT22); // datapin sensor connected to pin 2 Arduino

#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27,16,2); 
void LCD1602_init(void) //液晶初始化用到的函数，包罗在这里
{
lcd.init(); //调用LiquidCrystal_I2C.h里的LCD初始化函数
delay(10); //延时10毫秒
lcd.backlight(); //开LCD1602的背光灯
lcd.clear(); //清除屏幕
}
void configureSensor(void)
{
  // You can change the gain on the fly, to adapt to brighter/dimmer light situations
 // tsl.setGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
  tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
  //tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain
  
  // Changing the integration time gives you a longer time over which to sense light
  // longer timelines are slower, but are good in very low light situtations!
  //tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // shortest integration time (bright light)
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS);
 // tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
 //  tsl.setTiming(TSL2591_INTEGRATIONTIME_400MS);
   tsl.setTiming(TSL2591_INTEGRATIONTIME_500MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);  // longest integration time (dim light)

  /* Display the gain and integration time for reference sake */  
//  Serial.println(F("------------------------------------"));
 // Serial.print  (F("Gain:         "));
  tsl2591Gain_t gain = tsl.getGain();
  switch(gain)
  {
    case TSL2591_GAIN_LOW:
   //   Serial.println(F("1x (Low)"));
      break;
    case TSL2591_GAIN_MED:
   //   Serial.println(F("25x (Medium)"));
      break;
    case TSL2591_GAIN_HIGH:
      Serial.println(F("428x (High)"));
      break;
    case TSL2591_GAIN_MAX:
      Serial.println(F("9876x (Max)"));
      break;
  }
//  Serial.print  (F("Timing:       "));
//  Serial.print((tsl.getTiming() + 1) * 100, DEC); 
// Serial.println(F(" ms"));
// Serial.println(F("------------------------------------"));
//  Serial.println(F(""));
}
int sensorValue;

void setup() 
{
  pinMode(pinFUN,OUTPUT);
  digitalWrite(pinFUN,HIGH);
  
  DHT_sens.begin();
  Serial.begin(9600);
  
 
    mySerial.begin(BAUDRATE);                               // (Uno example) device to MH-Z19 serial start   
    myMHZ19.begin(mySerial);                                // *Serial(Stream) refence must be passed to library begin(). 

    myMHZ19.autoCalibration();                              // Turn auto calibration ON (OFF autoCalibration(false))
 configureSensor();
LCD1602_init();
lcd.setCursor(0, 0); 
lcd.print(" Wait Signal ");

  delay(2000); 
  lcd.clear();
   Serial.println("CO2(ppm) , LIGHT(lux) , Humidity% ,Temp(Celsious)"); 
  //uint16_t lux = LightSensor.GetLightIntensity(); 
  start_time2=millis();  
}
void loop()
{ sensorValue = analogRead(A0);
  while (sensorValue<200)   //GREENHOUSE MODE
  {
    
  if ((millis() - getDataTimer >= 1900UL))
  {
  
         h = DHT_sens.readHumidity();
         t = DHT_sens.readTemperature();
     uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;

        int CO2; 

        /* note: getCO2() default is command "CO2 Unlimited". This returns the correct CO2 reading even 
        if below background CO2 levels or above range (useful to validate sensor). You can use the 
        usual documented command with getCO2(false) */

        CO2 = myMHZ19.getCO2();                             // Request CO2 (as ppm)
     
                                  
       
        int8_t Temp;
        Temp = myMHZ19.getTemperature();                     // Request Temperature (as Celsius)
    //    Serial.print("Temperature (C): ");                  
    //    Serial.println(Temp);                               
  lcd.setCursor(0,0);  
  lcd.print(" CO2-ppm:");//lcd.setCursor(8,0);
  lcd.print(CO2);lcd.print("ppm");
 lcd.setCursor(0,1);  
  lcd.print(t);
  lcd.setCursor(5,1);
  lcd.print("*C ");
//lcd.setCursor(9,1);
//lcd.print(lux);lcd.print("Lux ");
 lcd.print("Lux");
 lcd.print(tsl.calculateLux(full, ir), 1);     
  if ((millis() - start_time2 >= 20000UL))  
{
 Serial.print(CO2); Serial.print(",");
 Serial.print(tsl.calculateLux(full, ir), 1);
 //Serial.print((lux)); 
 Serial.print(",");
 Serial.print(h,0); Serial.print(",");
 Serial.println(t,1);
 sensorValue = analogRead(A0); 
 start_time2=millis(); 
 
}
        
      
if ((CO2 >= 4900)||(CO2 <= 399)) 
{
digitalWrite(pinFUN,HIGH); 
}
else 
{digitalWrite(pinFUN,LOW);}

//delay (1000); // pause a... 
getDataTimer=millis();

 
  }
  sensorValue = analogRead(A0);
}
while (sensorValue>700)    //CLASS MODE
{
  if ((millis() - getDataTimer >= 1900UL))
  {
  
         h = DHT_sens.readHumidity();
         t = DHT_sens.readTemperature();
     uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;

        int CO2; 

        /* note: getCO2() default is command "CO2 Unlimited". This returns the correct CO2 reading even 
        if below background CO2 levels or above range (useful to validate sensor). You can use the 
        usual documented command with getCO2(false) */

        CO2 = myMHZ19.getCO2();                             // Request CO2 (as ppm)
     
                                  
       
        int8_t Temp;
        Temp = myMHZ19.getTemperature();                     // Request Temperature (as Celsius)
    //    Serial.print("Temperature (C): ");                  
    //    Serial.println(Temp);                               
  lcd.setCursor(0,0);  
  lcd.print(" CO2-ppm:");//lcd.setCursor(8,0);
  lcd.print(CO2);lcd.print("ppm");
 lcd.setCursor(0,1);  
  lcd.print(t);
  lcd.setCursor(5,1);
  lcd.print("*C ");
//lcd.setCursor(9,1);
//lcd.print(lux);lcd.print("Lux ");
 lcd.print("Lux");
 lcd.print(tsl.calculateLux(full, ir), 1);     
  if ((millis() - start_time2 >= 20000UL))  
{
 Serial.print(CO2); Serial.print(",");
 Serial.print(tsl.calculateLux(full, ir), 1);
 //Serial.print((lux)); 
 Serial.print(",");
 Serial.print(h,0); Serial.print(",");
 Serial.println(t,1);
 sensorValue = analogRead(A0); 
 start_time2=millis(); 
 
}
if ((CO2 >= 1900)) 
{
digitalWrite(pinBUZZ,HIGH); 
lcd.setCursor(0,0);
 lcd.print("Open the window ");
 lcd.setCursor(0,1);
 lcd.print("   HIGH CO2!!! ");
 delay(3000);
 lcd.clear();
}
else if (CO2 < 1900)
{digitalWrite(pinBUZZ,LOW);
 
}        
if ((((tsl.calculateLux(full, ir))) <= 50)) 
{
digitalWrite(pinBUZZ,HIGH); 
lcd.setCursor(0,0);
 lcd.print("OPEN THE LIGHTS ");
 lcd.setCursor(0,1);
 lcd.print(" LOW LUX VALUE  ");
 delay(3000);
 lcd.clear();
}
else if (((tsl.calculateLux(full, ir)))>50)
{digitalWrite(pinBUZZ,LOW);
 
}              
sensorValue = analogRead(A0);

//delay (1000); // pause a... 
getDataTimer=millis();

 
  }
  
}
}
