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
VL53L0X sensor4;
VL53L0X sensor5;
VL53L0X sensor6;
VL53L0X sensor7;
VL53L0X sensor8;
#define LONG_RANGE
#define PIN1 23
#define PIN2 25
#define PIN3 27
#define PIN4 29
#define PIN5 33
#define PIN6 37
#define PIN7 41
#define PIN8 45

#define ledverde 31//LED D31
#define ledAzul 35//LED D35
#define BUZZER_PIN  49  // AX-1205-2 5V

void setup() {
Wire.begin();
Serial.begin (115200);

pinMode(PIN1, OUTPUT);
pinMode(PIN2, OUTPUT);
pinMode(PIN3, OUTPUT);
pinMode(PIN4, OUTPUT);
pinMode(PIN5, OUTPUT);
pinMode(PIN6, OUTPUT);
pinMode(PIN7, OUTPUT);
pinMode(PIN8, OUTPUT);
digitalWrite(PIN1, LOW);
digitalWrite(PIN2, LOW);
digitalWrite(PIN3, LOW);
digitalWrite(PIN4, LOW);
digitalWrite(PIN5, LOW);
digitalWrite(PIN6, LOW);
digitalWrite(PIN7, LOW);
digitalWrite(PIN8, LOW);

pinMode(ledverde, OUTPUT);
digitalWrite(ledverde, LOW); 
pinMode(ledAzul, OUTPUT);
digitalWrite(ledAzul, LOW); 
pinMode(BUZZER_PIN, OUTPUT); 
tone(BUZZER_PIN, 200, 200); delay(200); 
tone(BUZZER_PIN, 500, 400); delay(500);  
delay(500);


#if defined LONG_RANGE
//Define o limite da taxa do sinal de retorno para o valor fornecido em unidades de MCPS (mega contagens por segundo).
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor1.setSignalRateLimit(0.1);
  sensor2.setSignalRateLimit(0.1);
  sensor3.setSignalRateLimit(0.1);
  sensor4.setSignalRateLimit(0.1);
  sensor5.setSignalRateLimit(0.1);
  sensor6.setSignalRateLimit(0.1);
  sensor7.setSignalRateLimit(0.1);
  sensor8.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  // Define o período de pulso VCSEL (laser de emissão de superfície da cavidade vertical) para o tipo de período fornecido
  // para o valor fornecido (em PCLKs). 
  // Períodos mais longos aumentam a faixa potencial do sensor. Os valores válidos são (apenas números pares):
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default
  //---------
  sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor2.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default
 //------------
 //---------
  sensor3.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor3.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default 
  //---------
  sensor4.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor4.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default 
   //---------
  sensor5.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor5.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default 
  //---------
  sensor6.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor6.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default 
//---------
  sensor7.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor7.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default 


  //---------
  sensor8.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor8.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default
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

pinMode(PIN4, INPUT);
delay(150);
sensor4.init(true);
Serial.println("04");
delay(100);
sensor4.setAddress((uint8_t)50);

pinMode(PIN5, INPUT);
delay(150);
sensor5.init(true);
Serial.println("05");
delay(100);
sensor5.setAddress((uint8_t)60);

pinMode(PIN6, INPUT);
delay(150);
sensor6.init(true);
Serial.println("06");
delay(100);
sensor6.setAddress((uint8_t)70);

pinMode(PIN7, INPUT);
delay(150);
sensor7.init(true);
Serial.println("07");
delay(100);
sensor7.setAddress((uint8_t)80);


pinMode(PIN8, INPUT);
delay(150);
sensor8.init(true);
Serial.println("08");
delay(100);
sensor8.setAddress((uint8_t)90);

Serial.println("------");

Serial.println("addresses set");

// end configuration
sensor1.setTimeout(500);
sensor2.setTimeout(500);
sensor3.setTimeout(500);
sensor4.setTimeout(500);
sensor5.setTimeout(500);
sensor6.setTimeout(500);
sensor7.setTimeout(500);
sensor8.setTimeout(500);
sensor1.startContinuous();
sensor2.startContinuous();
sensor3.startContinuous();
sensor4.startContinuous();
sensor5.startContinuous();
sensor6.startContinuous();
sensor7.startContinuous();
sensor8.startContinuous();

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
  int distance4 =sensor4.readRangeContinuousMillimeters();// get distance for sensor 4
  int distance5 =sensor5.readRangeContinuousMillimeters();// get distance for sensor 5
  int distance6 =sensor6.readRangeContinuousMillimeters();// get distance for sensor 6
  int distance7 =sensor7.readRangeContinuousMillimeters();// get distance for sensor 7
  int distance8 =sensor8.readRangeContinuousMillimeters();// get distance for sensor 8
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

   if(distance4<=400)
  {
    digitalWrite(ledverde, HIGH); 
    tone(BUZZER_PIN, 500, 500); // 
  }
  else
  {
     digitalWrite(ledverde, LOW);
  }

    if(distance5<=400)
  {
    digitalWrite(ledverde, HIGH); 
    tone(BUZZER_PIN, 500, 500); // 
  }
  else
  {
     digitalWrite(ledverde, LOW);
  }

      if(distance6<=400)
  {
    digitalWrite(ledverde, HIGH); 
    tone(BUZZER_PIN, 500, 500); // 
  }
  else
  {
     digitalWrite(ledverde, LOW);
  }

    if(distance7<=400)
  {
    digitalWrite(ledverde, HIGH); 
    tone(BUZZER_PIN, 500, 500); // 
  }
  else
  {
     digitalWrite(ledverde, LOW);
  }

      if(distance8<=400)
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

Serial.print(sensor4.readRangeContinuousMillimeters());
if (sensor4.timeoutOccurred()) { Serial.print(" TIMEOUT S4"); }
Serial.print("\t");

Serial.print(sensor5.readRangeContinuousMillimeters());
if (sensor5.timeoutOccurred()) { Serial.print(" TIMEOUT S5"); }
Serial.print("\t");

Serial.print(sensor6.readRangeContinuousMillimeters());
if (sensor6.timeoutOccurred()) { Serial.print(" TIMEOUT S6"); }
Serial.print("\t");

Serial.print(sensor7.readRangeContinuousMillimeters());
if (sensor7.timeoutOccurred()) { Serial.print(" TIMEOUT S7"); }
Serial.print("\t");

Serial.print(sensor8.readRangeContinuousMillimeters());
if (sensor8.timeoutOccurred()) { Serial.print(" TIMEOUT S8"); }
Serial.print("\t");
Serial.println();
}
