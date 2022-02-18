#include <Arduino.h>
#include "MHZ19.h"                                        
#include <SoftwareSerial.h>                                // Remove if using HardwareSerial

#define RX_PIN 10                                         // Rx pin which the MHZ19 Tx pin is attached to 10
#define TX_PIN 11                                          // Tx pin which the MHZ19 Rx pin is attached to 11
#define BAUDRATE 9600                                      // Device to MH-Z19 Serial baudrate (should not be changed)

MHZ19 myMHZ19;                                             // Constructor for library
SoftwareSerial mySerial(RX_PIN, TX_PIN);                   // (Uno example) create device to MH-Z19 serial

unsigned long getDataTimer = 0;
//lm35
//#define ADC_VREF_mV    1100.0 // in millivolt
//#define ADC_RESOLUTION 1024.0
//#define PIN_LM35       A0


#include <BH1750FVI.h>
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

 #include "DHT.h"

float h, t;
DHT DHT_sens(2, DHT11); // datapin sensor connected to pin 2 Arduino

#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27,16,2); 
void LCD1602_init(void) //液晶初始化用到的函数，包罗在这里
{
lcd.init(); //调用LiquidCrystal_I2C.h里的LCD初始化函数
delay(10); //延时10毫秒
lcd.backlight(); //开LCD1602的背光灯
lcd.clear(); //清除屏幕
}

void setup() 
{
  DHT_sens.begin();
  Serial.begin(9600);
  LightSensor.begin();
 
    mySerial.begin(BAUDRATE);                               // (Uno example) device to MH-Z19 serial start   
    myMHZ19.begin(mySerial);                                // *Serial(Stream) refence must be passed to library begin(). 

    myMHZ19.autoCalibration();                              // Turn auto calibration ON (OFF autoCalibration(false))
 //    LCD1602_init();
     // switch to Internal 1.1V Reference
//  analogReference(INTERNAL); //lm35
LCD1602_init();
lcd.setCursor(0, 0); 
lcd.print(" Wait Signal ");

  delay(2000); 
  lcd.clear();  
}
void loop()
{
 //  lcd.clear();//--------------test
    uint16_t lux = LightSensor.GetLightIntensity();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println("Lux");
  h = DHT_sens.readHumidity();
t = DHT_sens.readTemperature();

delay (1000); // pause a second
Serial.print ("Humidity: ");
Serial.print (h,0); // zero decimal
Serial.print (" %\t");
Serial.print ("1)Temperature: ");
Serial.print (t,1); // one decimal
Serial.println (" *C");
delay (1050); // pause a...
 lcd.setCursor(0,1);  
  lcd.print(t);
  lcd.setCursor(5,1);
  lcd.print("*C ");
//lcd.setCursor(9,1);
lcd.print(lux);lcd.print("Lux ");
  // get the ADC value from the temperature sensor
//  int adcVal = analogRead(PIN_LM35);
  // convert the ADC value to voltage in millivolt
//  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION); //  ADC_VREF_mV = 1100 mV
  // convert the voltage to the temperature in Celsius
//  float tempC = milliVolt / 10;
  // convert the Celsius to Fahrenheit
 // float tempF = tempC * 9 / 5 + 32;

  // print the temperature in the Serial Monitor:
 // Serial.print("2)Temp(LM35): ");
// Serial.print(tempC);   // print the temperature in Celsius
 // Serial.println("°C");
 // Serial.print("  ~  "); // separator between Celsius and Fahrenheit
 // Serial.print(tempF);   // print the temperature in Fahrenheit
 // Serial.println("°F");
 // lcd.setCursor(12,1);  
 // lcd.print(tempC);lcd.print("°C");   
if (millis() - getDataTimer >= 2000)
    {
        int CO2; 

        /* note: getCO2() default is command "CO2 Unlimited". This returns the correct CO2 reading even 
        if below background CO2 levels or above range (useful to validate sensor). You can use the 
        usual documented command with getCO2(false) */

        CO2 = myMHZ19.getCO2();                             // Request CO2 (as ppm)
        
        Serial.print("CO2 (ppm): ");                      
        Serial.println(CO2);                                

        int8_t Temp;
        Temp = myMHZ19.getTemperature();                     // Request Temperature (as Celsius)
    //    Serial.print("Temperature (C): ");                  
    //    Serial.println(Temp);                               
  lcd.setCursor(0,0);  
  lcd.print(" CO2-ppm:");//lcd.setCursor(8,0);
  lcd.print(CO2);lcd.print("ppm"); 
        getDataTimer = millis();
    }
delay(1000);
 
  delay(10);
}
