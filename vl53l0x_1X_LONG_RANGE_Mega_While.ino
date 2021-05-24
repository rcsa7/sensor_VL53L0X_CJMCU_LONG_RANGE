/*
 * led_while
 * 
//https://www.circuitar.com.br/projetos/while-then/index.html

O código abaixo faz com que o LED amarelo fique ligado enquanto o botão RIGHT não é apertado.
*/
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor1;
#define LONG_RANGE
#define PIN1 23 //23
int ledAmarelo = 48;



float distance=0; //sensor frontal
float realDistance=0;//sensor frontal
int whatDistance(){

    distance =  sensor1.readRangeContinuousMillimeters();
    return distance;
    }


void setup()
  {
Wire.begin();
Serial.begin (115200);
pinMode(PIN1, OUTPUT);
digitalWrite(PIN1, LOW);
  pinMode(ledAmarelo,OUTPUT); 
 
  #if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor1.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default
  //---------
  #endif


pinMode(PIN1, INPUT);
delay(150);
Serial.println("00");
sensor1.init(true);
Serial.println("01");
delay(100);
sensor1.setAddress((uint8_t)30);
// end configuration
sensor1.setTimeout(500);
sensor1.startContinuous();
/////callI2Cscanner();
}
/*
void callI2Cscanner()
{
  // scan i2c
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

  for (byte i = 1; i < 120; i++) 
  {  
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0) 
    {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);  // maybe unneeded?
    }             // end of good response
  }               // end of for loop
  
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");  
  
}

*/
void loop() {
 int distance1 =sensor1.readRangeContinuousMillimeters();// get distance for sensor 1  
Serial.print(sensor1.readRangeContinuousMillimeters());
if (sensor1.timeoutOccurred()) { Serial.print(" TIMEOUT S1"); }
Serial.print("\t");
 realDistance = whatDistance();
 if (realDistance<=0) {
    realDistance = whatDistance();
    }    
 
  // Enquanto  leitura for maior mm
  while (realDistance>250)
  {
    //Acende o LED Amarelo
    digitalWrite(ledAmarelo, HIGH);
    realDistance = whatDistance();
  } 
  if (realDistance < 200)
    { 
       // Enquanto  leitura for menor mm 
        while (realDistance < 100)
          {
            //Apaga o LED Amarelo
            digitalWrite(ledAmarelo, LOW);
             realDistance = whatDistance();      
          } 
      }  
}  
