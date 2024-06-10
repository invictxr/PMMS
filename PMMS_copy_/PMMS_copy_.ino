#include <ArduinoMqttClient.h>
#include <WiFi.h>
#include <ACS712XX.h>
#include <Arduino.h>

#define A0 35
#define led 2

#define ssid "kako"  // SSID da sua rede Wi-Fi
#define pass "senai123"  // Senha da sua rede Wi-Fi

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

ACS712XX ACS712(ACS712_05B, A0);

const char broker[] = "131.0.0.81";  // Endereço IP do seu broker MQTT
int port = 1883;

const char topic[] = "sensor/current";  // Tópico MQTT para publicar a leitura do sensor de corrente

void setup() {
  Serial.begin(115200);

  pinMode(led, OUTPUT);

  Serial.print("Tentando se conectar à rede WPA SSID: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    // falha, tentar novamente
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Você está conectado à rede");
  Serial.println();

  Serial.print("Tentando se conectar ao broker MQTT: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("Conexão MQTT falhou! Código de erro = ");
    Serial.println(mqttClient.connectError());

    while (1)
      ;
  }

  Serial.println("Você está conectado ao broker MQTT!");
  Serial.println();

  while (!Serial) {
    ;
  }

  Serial.println("Teste do Sensor de Corrente ACS712_05B...");
  Serial.println();

  Serial.print("Tipo de Fonte de Corrente:");
  Serial.println(" DC");
  Serial.println();

  Serial.print("Offset Atual:");
  Serial.println(ACS712.getOffset());       // Mostra o offset atual
  Serial.println();

  Serial.println("Calibrando Automaticamente o Sensor de Corrente...");
  Serial.print("Offset Calibrado:");
  float _offset = ACS712.autoCalibrate();   // Deve garantir que não haja corrente passando pelos sensores
  Serial.println(_offset);
  Serial.println();

  Serial.print("Sensibilidade Atual:");
  Serial.print(ACS712.getSensitivity());  // Mostra a sensibilidade atual
  Serial.println(" mV/A");
  Serial.println();

  ACS712.reset(); // Redefine o offset e a sensibilidade do sensor para o padrão
}

void loop() {
  int valor_A0 = analogRead(A0);
  if (valor_A0 > 200) { //  Necessário definir valor
    Serial.print("Corrente Medida:");

    //  Por padrão, esta função getDC() retorna o valor de medição de corrente pela média de 10 pontos de dados.
    float current = ACS712.getDC() * 20; //  Alterar valor de acordo com o TC
    Serial.print(current);
    Serial.println(" A");

    // Publica a leitura de corrente no tópico MQTT
    mqttClient.beginMessage(topic);
    mqttClient.print(current);
    mqttClient.endMessage();

    delay(1000);
  } else {
    Serial.println("Inativo");
    digitalWrite(led, 1);
    delay(1000);
    digitalWrite(led, 0);
  }
}