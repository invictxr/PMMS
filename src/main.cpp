
#include <ACS712XX.h>

/* Descrição : O construtor do sensor de corrente ACS712. Cria um objeto para usar esta biblioteca ACS712.
 * Argumento(s): Tipo de sensor, Pino do sensor, Tensão de referência do ADC, Saída de escala completa do ADC.
 * Padrão  (s): Tensão de referência do ADC -> 5, Saída de escala completa do ADC -> 1023
 */
ACS712XX ACS712(ACS712_05B, A0);
//ACS712XX ACS712(ACS712_20A, A0);
//ACS712XX ACS712(ACS712_30A, A0);

void setup() {
  Serial.println(F("Teste do Sensor de Corrente ACS712_05B..."));
  Serial.println();
  
  Serial.print(F("Tipo de Fonte de Corrente:"));
  Serial.println(F(" DC"));
  Serial.println();
  
  Serial.print(F("Offset Atual:"));
  Serial.println(ACS712.getOffset());       // Mostra o offset atual
  Serial.println();
  
  Serial.println(F("Calibrando Automaticamente o Sensor de Corrente..."));
  Serial.print(F("Offset Calibrado:"));
  float _offset = ACS712.autoCalibrate();   // Deve garantir que não haja corrente passando pelos sensores
  Serial.println(_offset);
  Serial.println();
  
  Serial.print(F("Sensibilidade Atual:"));
  Serial.print(ACS712.getSensitivity());  // Mostra a sensibilidade atual
  Serial.println(F(" mV/A"));
  Serial.println();
  
//  Altere este valor somente quando estiver muito certo de que a sensibilidade do sensor foi alterada.
//  ACS712.setSensitivity(200);             // mV/A

// Esta função reset() irá redefinir o offset e a sensibilidade do sensor para o padrão.
  ACS712.reset();
}

void loop() { 
  Serial.print(F("Corrente Medida:"));
  
//  Por padrão, esta função getDC() retorna o valor de medição de corrente pela média de 10 pontos de dados.
  Serial.print(ACS712.getDC());

//  Você pode escolher qualquer valor positivo (exceto zero), então, a função getDC(valor)
//  retorna o valor de medição de corrente pela média dos pontos de dados fornecidos.
//  Serial.print(ACS712.getDC(20));
  Serial.println(F(" A"));
  delay(100);
}
  