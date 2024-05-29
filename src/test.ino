#include <ACS712XX.h>
#include <Arduino.h>

#define A0 35

ACS712XX ACS712(ACS712_05B, A0);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

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
  
  ACS712.reset(); // Redefine o offset e a sensibilidade do sensor para o padrão
}

void loop() {
  int valor_A0 = analogRead(A0);
  delay(3000);
  if (valor_A0 > 200) { //  Necessário definir valor 
    Serial.print(F("Corrente Medida:"));
    
    //  Por padrão, esta função getDC() retorna o valor de medição de corrente pela média de 10 pontos de dados.
    float corrente = ACS712.getDC() * 20; //  Alterar valor de acordo com o TC
    Serial.print(corrente);

    //  Você pode escolher qualquer valor positivo (exceto zero), então, a função getDC(valor)
    //  retorna o valor de medição de corrente pela média dos pontos de dados fornecidos.
    //  Serial.print(ACS712.getDC(20));
    Serial.println(F(" A"));
    delay(5000);
  } else {
    Serial.println("Inativo");
  }
}
