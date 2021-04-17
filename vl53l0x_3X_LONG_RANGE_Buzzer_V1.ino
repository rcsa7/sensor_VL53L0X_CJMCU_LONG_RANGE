/*
 * vl53l0x_multiple_test_v1
 * http://dami.azw.pt/usar-varios-vl53l0x-com-enderecos-i2c-diferentes/
 * 
 * 
 */



#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;
#define LONG_RANGE
#define PIN1 23
#define PIN2 25
#define PIN3 27

#define ledverde 31//LED D31
#define ledAzul 35//LED D35
#define BUZZER_PIN  49  // AX-1205-2 5V

void setup() {
Wire.begin();
Serial.begin (115200);

pinMode(PIN1, OUTPUT);
pinMode(PIN2, OUTPUT);
pinMode(PIN3, OUTPUT);
digitalWrite(PIN1, LOW);
digitalWrite(PIN2, LOW);
digitalWrite(PIN3, LOW);
pinMode(ledverde, OUTPUT);
digitalWrite(ledverde, LOW); 
pinMode(ledAzul, OUTPUT);
digitalWrite(ledAzul, LOW); 
pinMode(BUZZER_PIN, OUTPUT); 
tone(BUZZER_PIN, 200, 200); delay(200); 
tone(BUZZER_PIN, 500, 400); delay(500);  
delay(500);

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor1.setSignalRateLimit(0.1);
  sensor2.setSignalRateLimit(0.1);
  sensor3.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default
  //---------
  sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default
 //------------
 //---------
  sensor3.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor3.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default 
#endif


pinMode(PIN1, INPUT);
delay(150);
Serial.println("00");
sensor1.init(true);

Serial.println("01");
delay(100);
sensor1.setAddress((uint8_t)30);
Serial.println("02");

pinMode(PIN2, INPUT);
delay(150);
sensor2.init(true);
Serial.println("03");
delay(100);
sensor2.setAddress((uint8_t)20);

pinMode(PIN3, INPUT);
delay(150);
sensor3.init(true);
Serial.println("03");
delay(100);
sensor3.setAddress((uint8_t)40);

Serial.println("04");

Serial.println("addresses set");

// end configuration
sensor1.setTimeout(500);
sensor2.setTimeout(500);
sensor3.setTimeout(500);
sensor1.startContinuous();
sensor2.startContinuous();
sensor3.startContinuous();

// scan i2c
Serial.println ("I2C scanner. Scanning ...");
byte count = 0;

for (byte i = 1; i < 120; i++) {

Wire.beginTransmission (i);
if (Wire.endTransmission () == 0) {
Serial.print ("Found address: ");
Serial.print (i, DEC);
Serial.print (" (0x");
Serial.print (i, HEX);
Serial.println (")");
count++;
delay (1); // maybe unneeded?
} // end of good response
} // end of for loop
Serial.println ("Done.");
Serial.print ("Found ");
Serial.print (count, DEC);
Serial.println (" device(s).");
}

void loop() {
   int distance1 =sensor1.readRangeContinuousMillimeters();// get distance for sensor 1
  int distance2 =sensor2.readRangeContinuousMillimeters();// get distance for sensor 2
  int distance3 =sensor3.readRangeContinuousMillimeters();// get distance for sensor 3
  //------------------------------------------------------
  if(distance1<=200)
  {
    digitalWrite(ledAzul, HIGH); 
    tone(BUZZER_PIN, 300, 300); // 
  }
  else
  {
     digitalWrite(ledAzul, LOW);
  }
  //------------------------------------------------------
  if(distance2<=300)
  {
    digitalWrite(ledverde, HIGH); 
    tone(BUZZER_PIN, 400, 400); // 
  }
  else
  {
     digitalWrite(ledverde, LOW);
  }

   if(distance3<=400)
  {
    digitalWrite(ledverde, HIGH); 
    tone(BUZZER_PIN, 500, 500); // 
  }
  else
  {
     digitalWrite(ledverde, LOW);
  }
//-------------------------------------------------------------
Serial.print(sensor1.readRangeContinuousMillimeters());
if (sensor1.timeoutOccurred()) { Serial.print(" TIMEOUT S1"); }
Serial.print("\t");

Serial.print(sensor2.readRangeContinuousMillimeters());
if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT S2"); }
Serial.print("\t");
Serial.print(sensor3.readRangeContinuousMillimeters());
if (sensor3.timeoutOccurred()) { Serial.print(" TIMEOUT S3"); }
Serial.print("\t");
Serial.println();
}
