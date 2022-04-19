#include <Arduino.h>
#include "MHZ19.h"                                        
#include <SoftwareSerial.h>                                // Remove if using HardwareSerial

#define RX_PIN 10                                         // Rx pin which the MHZ19 Tx pin is attached to 10
#define TX_PIN 11                                          // Tx pin which the MHZ19 Rx pin is attached to 11
#define BAUDRATE 9600                                      // Device to MH-Z19 Serial baudrate (should not be changed)

MHZ19 myMHZ19;                                             // Constructor for library
SoftwareSerial mySerial(RX_PIN, TX_PIN);                   // (Uno example) create device to MH-Z19 serial
SoftwareSerial BLUE2(7,8);
SoftwareSerial BLUE3(12,3);   
unsigned long getDataTimer = 0;
unsigned long start_time; // Δημιούργησε μια μεταβλητή τύπου unsigned long integer με όνομα start_time
unsigned long start_time2; 
#include <BH1750FVI.h>
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

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
#define Lpwm_pin 6 
#define Rpwm_pin 5 
int pinLB=A3; 
int pinLF=A2; 
int pinRB=4; 
int pinRF=9; 
unsigned char Lpwm_val = 160;
unsigned char Rpwm_val = 160;

void M_Control_IO_config(void)
{
pinMode(pinLB,OUTPUT); 
pinMode(pinLF,OUTPUT); 
pinMode(pinRB,OUTPUT); 
pinMode(pinRF,OUTPUT); 
pinMode(Lpwm_pin,OUTPUT); // (PWM)
pinMode(Rpwm_pin,OUTPUT); //  (PWM)
}
void Set_Speed(unsigned char Left,unsigned char Right)
{
analogWrite(Lpwm_pin,Left);
analogWrite(Rpwm_pin,Right);
}
void advance(void) 
{

digitalWrite(pinLB,LOW); // 使馬達（左後）動作
digitalWrite(pinLF,HIGH);
digitalWrite(pinRB,LOW); // 使馬達（右後）動作
digitalWrite(pinRF,HIGH);

}
void stopp(void) 
{
digitalWrite(pinRB,HIGH);   //OR ALL LOW if this doesn't work
digitalWrite(pinRF,HIGH);
digitalWrite(pinLB,HIGH);
digitalWrite(pinLF,HIGH);

}

void setup() 
{
  
  DHT_sens.begin();
  Serial.begin(9600);
  LightSensor.begin();
 BLUE2.begin(9600);
 BLUE3.begin(9600);
    mySerial.begin(BAUDRATE);                               // (Uno example) device to MH-Z19 serial start   
    myMHZ19.begin(mySerial);                                // *Serial(Stream) refence must be passed to library begin(). 

    myMHZ19.autoCalibration(false);                              // Turn auto calibration ON (OFF autoCalibration(false))

LCD1602_init();
lcd.setCursor(0, 0); 
lcd.print(" Wait Signal ");

  delay(2000); 
  lcd.clear();
   Serial.println("CO2(ppm) , LIGHT(lux) , Humidity% ,Temp(Celsious)"); 
   BLUE2.println("CO2(ppm) , LIGHT(lux) , Humidity% ,Temp(Celsious)"); 
M_Control_IO_config();
Set_Speed(Lpwm_val,Rpwm_val);
 
  start_time=millis();
  start_time2=millis();  
}
void loop()
{
  if ((millis() - getDataTimer >= 1850UL))
  {
  Set_Speed(Lpwm_val,Rpwm_val);
         h = DHT_sens.readHumidity();
         t = DHT_sens.readTemperature();     

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

    uint16_t lux = LightSensor.GetLightIntensity();
//---------  Serial.print(",");
//------  Serial.print(lux);
//---------  Serial.print(",");
//  h = DHT_sens.readHumidity();
//  t = DHT_sens.readTemperature();

 

//------Serial.print(h,0); // zero decimal
//---------Serial.print(",");

//-----Serial.println(t,1); // one decimal
 BLUE2.print(CO2); BLUE2.print(",");
BLUE2.print(lux); BLUE2.print(",");
BLUE2.print(h,0); BLUE2.print(",");
BLUE2.println(t,1); 

 lcd.setCursor(0,1);  
  lcd.print(t);
  lcd.setCursor(5,1);
  lcd.print("*C ");
//lcd.setCursor(9,1);
lcd.print(lux);lcd.print("Lux ");
      
  if ((millis() - start_time2 >= 20000UL))  
{
 Serial.print(CO2); Serial.print(",");
 Serial.print((lux)); Serial.print(",");
 Serial.print(h,0); Serial.print(",");
 Serial.println(t,1); 
 start_time2=millis(); 
 
}
        
        if ((millis() - start_time >= 600000UL))  //send every 10 minute print port BLUE3
{
 BLUE3.print((CO2*1.0)/10);BLUE3.print(",");
 BLUE3.print((lux*1.0)/10); BLUE3.print(",");
 BLUE3.print(h,0); BLUE3.print(",");
 BLUE3.println(t*10,1); 
 start_time=millis();  
 
}
if ((CO2 >= 4900)||(CO2 <= 200)) 
{
 advance();
 
}
else 
{stopp();}
//start_time=millis(); 
    
//delay (1000); // pause a... 
getDataTimer=millis();

 
  }
}
