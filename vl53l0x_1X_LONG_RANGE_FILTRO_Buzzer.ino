/*
 * vl53l0x_multiple_test_v1
 * http://dami.azw.pt/usar-varios-vl53l0x-com-enderecos-i2c-diferentes/
 * 
 * 
 */



#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor1;
#define LONG_RANGE
// Variaveis para armazenar a distancia atual e o ultimo valor lido
int dist = 0, dist_old = 0;
// Variavel para armazenar o tempo na parte do timeout
unsigned long timeout = 0;



#define PIN1 22


#define ledverde 47//LED D45
#define ledAzul 46//LED D47
#define BUZZER_PIN  48  // AX-1205-2 5V

void setup() {
Wire.begin();
Serial.begin (115200);

pinMode(PIN1, OUTPUT);

digitalWrite(PIN1, LOW);

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
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor1.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default
  //sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 28);//default
  //sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 20);//default
#endif



pinMode(PIN1, INPUT);
delay(150);
Serial.println("00");
sensor1.init(true);

Serial.println("01");
delay(100);
sensor1.setAddress((uint8_t)45);
Serial.println("02");



Serial.println("addresses set");

// end configuration
sensor1.setTimeout(500);

sensor1.startContinuous();


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
 
  dist = sensor1.readRangeSingleMillimeters();
  Serial.print(" mm");
    Serial.print("\t");
   Serial.println();
  Serial.println(dist);
 //  Serial.println();
  
  filtrar_sinal(); // Filtra o valor de distancia
 // Serial.println();

 
  
 
  
  
  //------------------------------------------------------
  if(dist <=200 )
  {
    digitalWrite(ledAzul, HIGH); 
    tone(BUZZER_PIN, 300, 300); // 
  }
  else
  {
     digitalWrite(ledAzul, LOW);
  }
  
//-------------------------------------------------------------

}

// Função para filtrar o valor medido
void filtrar_sinal()
{
  // Se a distância medida for maior que 8000 e ainda não tiver passado 1 segundo de timeout
  if (dist > 8000 && ((millis() - timeout) < 1000))
  {
    // Descarta a medição feita e iguala ela à anterior
    dist = dist_old;
  }
  else // Caso contrário (medição < 8000 ou passou do timeout)
  {
    // Não descarta a medição atual e atualiza a medição antiga para a atual
    dist_old = dist;
    timeout = millis(); // Reseta o valor da variável do timeout
  }
}
