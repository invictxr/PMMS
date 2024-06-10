#include <ArduinoMqttClient.h>
#include <WiFi.h>
#include "time.h"

#define A1 25
#define A2 33
#define A3 35

#define ssid "victorH"
#define pass "Senai@123"

WiFiClient client;
MqttClient mqttClient(client);

const char broker[] = "192.168.137.68";
int port = 1883;

const char topic[] = "Maq_Solda/1/Amps";
const char topic4[] = "Maq_Solda/1/Time_S";
const char topic5[] = "Maq_Solda/1/Time_M";
const char topic6[] = "Maq_Solda/1/Time_H";
const char topic7[] = "Maq_Solda/1/TimeStamp";

const char topic8[] = "Maq_Solda/2/Amps";
const char topic9[] = "Maq_Solda/2/Time_S";
const char topic10[] = "Maq_Solda/2/Time_M";
const char topic11[] = "Maq_Solda/2/Time_H";

const char topic12[] = "Maq_Solda/3/Amps";
const char topic13[] = "Maq_Solda/3/Time_S";
const char topic14[] = "Maq_Solda/3/Time_M";
const char topic15[] = "Maq_Solda/3/Time_H";

unsigned long segundos = 0;
unsigned long minutos = 0;
unsigned long horas = 0;

unsigned long segundos2 = 0;
unsigned long minutos2 = 0;
unsigned long horas2 = 0;

unsigned long segundos3 = 0;
unsigned long minutos3 = 0;
unsigned long horas3 = 0;


const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -3600;
const int daylightOffset_sec = -7200;

const long interval1 = 1000;
unsigned long previousMillis1 = 0;

const long interval2 = 60000;
unsigned long previousMillis2 = 0;

const long interval3 = 60000;
unsigned long previousMillis3 = 0;

const long interval4 = 60000;
unsigned long previousMillis4 = 0;

unsigned long updateTime = 0;

int count = 0;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(1000);
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1)
      ;
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  mqttClient.poll();

  unsigned long currentMillis1 = millis();

  if (currentMillis1 - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis1;

    int Rvalue = analogRead(A1);
    int Rvalue2 = analogRead(A2);
    int Rvalue3 = analogRead(A3);

    if (Rvalue >= 0) {
      struct tm timeinfo;
      if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
      }

      mqttClient.beginMessage(topic7);
      if (updateTime <= 59) {
        updateTime++;
      }
      if (updateTime >= 60) {
        mqttClient.print(&timeinfo);
        updateTime = 0;
        mqttClient.endMessage();
      }

      if (segundos <= 59) {
        segundos++;
      }
      if (segundos >= 60) {
        segundos = 0;
        minutos++;
      }
      if (minutos >= 60) {
        minutos = 0;
        horas++;
      }

      unsigned long currentMillis2 = millis();

      if (currentMillis2 - previousMillis2 >= interval2) {
        previousMillis2 = currentMillis2;

        mqttClient.beginMessage(topic);
        mqttClient.print(Rvalue);
        mqttClient.endMessage();


        mqttClient.beginMessage(topic4);
        mqttClient.println(segundos);
        mqttClient.endMessage();

        mqttClient.beginMessage(topic5);
        mqttClient.println(minutos);
        mqttClient.endMessage();

        mqttClient.beginMessage(topic6);
        mqttClient.println(horas);
        mqttClient.endMessage();
      }
    }

    if (Rvalue2 >= 0) {

      if (segundos2 <= 59) {
        segundos2++;
      }
      if (segundos2 >= 60) {
        segundos2 = 0;
        minutos2++;
      }
      if (minutos2 >= 60) {
        minutos2 = 0;
        horas2++;
      }

      unsigned long currentMillis3 = millis();

      if (currentMillis3 - previousMillis3 >= interval3) {
        previousMillis3 = currentMillis3;

        mqttClient.beginMessage(topic8);
        mqttClient.print(Rvalue2);
        mqttClient.endMessage();


        mqttClient.beginMessage(topic9);
        mqttClient.println(segundos2);
        mqttClient.endMessage();

        mqttClient.beginMessage(topic10);
        mqttClient.println(minutos2);
        mqttClient.endMessage();

        mqttClient.beginMessage(topic11);
        mqttClient.println(horas2);
        mqttClient.endMessage();
      }
    }

    if (Rvalue3 >= 0) {

      if (segundos3 <= 59) {
        segundos3++;
      }
      if (segundos3 >= 60) {
        segundos3 = 0;
        minutos3++;
      }
      if (minutos3 >= 60) {
        minutos3 = 0;
        horas3++;
      }

      unsigned long currentMillis4 = millis();

      if (currentMillis4 - previousMillis4 >= interval4) {
        previousMillis4 = currentMillis4;

        mqttClient.beginMessage(topic12);
        mqttClient.print(Rvalue3);
        mqttClient.endMessage();


        mqttClient.beginMessage(topic13);
        mqttClient.println(segundos3);
        mqttClient.endMessage();

        mqttClient.beginMessage(topic14);
        mqttClient.println(minutos3);
        mqttClient.endMessage();

        mqttClient.beginMessage(topic15);
        mqttClient.println(horas3);
        mqttClient.endMessage();
      }
    }


    Serial.println();
  }
}

String tempo() {
}
