/*
 * led_while
 * 
//https://www.circuitar.com.br/projetos/while-then/index.html

O código abaixo faz com que o LED amarelo fique ligado enquanto o botão RIGHT não é apertado.
*/
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor1;
VL53L0X sensor2;
#define LONG_RANGE
#define PIN1 23 //23
#define PIN2 25 //25
int ledAmarelo = 48;
int ledverde = 46;

//-----sensor s1------
float distance=0; //sensor s1
float realDistance=0;//sensor s1
int whatDistance(){
    distance =  sensor1.readRangeContinuousMillimeters();
    return distance;
    }
//---------------------------------------------------

//-----sensor s2------
float distance_S2=0; //sensor s2
float realDistance_S2=0;//sensor s2
int whatDistance_S2(){
    distance_S2 =  sensor2.readRangeContinuousMillimeters();
    return distance_S2;
    }
//---------------------------------------------------

void setup()
  {
Wire.begin();
Serial.begin (115200);
pinMode(PIN1, OUTPUT);
pinMode(PIN2, OUTPUT);
digitalWrite(PIN1, LOW);
digitalWrite(PIN2, LOW);
  pinMode(ledAmarelo,OUTPUT); 
  pinMode(ledverde,OUTPUT); 
  #if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor1.setSignalRateLimit(0.1);
  sensor2.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default
  //---------
  sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default
 //------------
  //---------
  #endif


pinMode(PIN1, INPUT);
delay(150);
Serial.println("00");
sensor1.init(true);
Serial.println("01");
delay(100);
sensor1.setAddress((uint8_t)30);

pinMode(PIN2, INPUT);
delay(150);
sensor2.init(true);
Serial.println("03");
delay(100);
sensor2.setAddress((uint8_t)28);

// end configuration
sensor1.setTimeout(500);
sensor2.setTimeout(500);
sensor1.startContinuous();
sensor2.startContinuous();
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
int distance2 =sensor2.readRangeContinuousMillimeters();// get distance for sensor 2
Serial.print(sensor1.readRangeContinuousMillimeters());
if (sensor1.timeoutOccurred()) { Serial.print(" TIMEOUT S1"); }
Serial.print("\t");

Serial.print(sensor2.readRangeContinuousMillimeters());
if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT S2"); }
Serial.print("\t");

//-------------------------------
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
// realDistance = whatDistance();
 realDistance_S2 = whatDistance_S2();  
 
 if (realDistance_S2<=0) {
    realDistance_S2 = whatDistance_S2();
    }    
 // Enquanto  leitura for maior mm
  while (realDistance_S2>350&&realDistance>250)
  {
    //Acende o LED verde
    digitalWrite(ledverde, HIGH);
  //  digitalWrite(ledverde, LOW);
    realDistance_S2 = whatDistance_S2();
    realDistance = whatDistance();
  } 
 if (realDistance_S2 < 200&&realDistance>250)
    { 
        // Enquanto  leitura for menor mm
        while (realDistance_S2 < 150)
          {
            //Apaga o LED verde
            digitalWrite(ledverde, LOW);
         /// digitalWrite(ledverde, HIGH);
             realDistance_S2 = whatDistance_S2();      
          } 

  }     
}  
