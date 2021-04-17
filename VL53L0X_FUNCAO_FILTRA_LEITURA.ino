/*
VL53L0X_FUNCAO_FILTRA_LEITURA
//http://mundoprojetado.com.br/sensor-de-distancia-a-laser-vl53l0x/
Filtrando as medições
Para resolver o problema anterior, podemos aplicar um método simples para filtrar as medições.
O método consiste apenas em ignorar o valor de ~8000mm quando ele for retornado pelo sensor. 
Desta forma, o programa irá considerar o último valor válido lido e irá “descartar” o valor de ~8000mm.

Este procedimento foi feito na função “filtrar_sinal” do código abaixo. 
Além do que comentei acima, adicionei um “timeout” de 1 segundo:
se o sensor retornar apenas ~8000mm durante 1 segundo, então ele para de descartar este valor.
Leia os comentários do código para entender.

*/
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

// Variaveis para armazenar a distancia atual e o ultimo valor lido
int dist = 0, dist_old = 0;
// Variavel para armazenar o tempo na parte do timeout
unsigned long timeout = 0;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

  // Perfil de longo alcance
  sensor.setSignalRateLimit(0.1);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
}

void loop()
{
  dist = sensor.readRangeSingleMillimeters();
  filtrar_sinal(); // Filtra o valor de distancia
 
  Serial.println(dist);
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
