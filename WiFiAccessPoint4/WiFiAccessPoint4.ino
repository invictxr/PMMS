#include <WebServer.h>
#include <DallasTemperature.h>
#include <ArduinoMqttClient.h>
#include <WiFi.h>
#include "time.h"
#include "esp_sntp.h"

const char *ssid = "victorH";
const char *pass = "Senai@123";

const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = -3600;
const int daylightOffset_sec = -7200;

WiFiClient client;
MqttClient mqttClient(client);

const char broker[] = "192.168.137.68";
int port = 1883;

const char topic1[] = "Temperature/Temp_1";
const char topic2[] = "Temperature/Temp_2";
const char topic3[] = "Temperature/Temp_3";
const char topic4[] = "Temperature/Temp_4";
const char topic5[] = "Temperature/Temp_5";
const char topic6[] = "Temperature/Temp_6";
const char topic7[] = "Temperature/Temp_7";
const char topic8[] = "Temperature/Temp_8";
const char topic9[] = "Temperature/Temp_9";
const char topic10[] = "Temperature/Temp_10";
const char topic11[] = "  ";

#define ONE_WIRE_BUS2 22  // DS18B20 on NodeMCU pin D22
#define ONE_WIRE_BUS0 23  // DS18B20 on NodeMCU pin D23
#define ONE_WIRE_BUS5 21  // DS18B20 on NodeMCU pin D1



float temp_1;
float temp_2;
float temp_3;
float temp_4;
float temp_5;
float temp_6;
float temp_7;
float temp_8;
float temp_9;
float temp_10;
int end_1;
int end_2;
int end_3;
int end_4;
int end_5;
int end_6;
int end_7;
int end_8;
int end_9;
int end_10;
int contador;
WebServer server(80);

DeviceAddress EndSensor1, EndSensor2, EndSensor3, EndSensor4, EndSensor5, EndSensor6, EndSensor7, EndSensor8, EndSensor9, EndSensor10;

void printLocalTime() {

  return;
}

void timeavailable(struct timeval *t) {
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}

void setup() {
  delay(1000);
  Serial.begin(115200);

  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    // failed, retry
    Serial.println(".");
    delay(1000);
  }

  sntp_set_time_sync_notification_cb(timeavailable);
  esp_sntp_servermode_dhcp(1);  // (optional)

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);


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

  Serial.println();
  Serial.print(contador);
  ++contador;
  Serial.print("     ");
  kit2();
  kit0();
  kit5();
  delay(15000);

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }

  mqttClient.beginMessage(topic11);
  mqttClient.println(&timeinfo);
  mqttClient.endMessage();

  mqttClient.beginMessage(topic1);
  mqttClient.println(temp_1);
  mqttClient.endMessage();

  mqttClient.beginMessage(topic2);
  mqttClient.println(temp_2);
  mqttClient.endMessage();

  mqttClient.beginMessage(topic3);
  mqttClient.println(temp_3);
  mqttClient.endMessage();

  mqttClient.beginMessage(topic4);
  mqttClient.println(temp_4);
  mqttClient.endMessage();

  mqttClient.beginMessage(topic5);
  mqttClient.println(temp_5);
  mqttClient.endMessage();

  mqttClient.beginMessage(topic6);
  mqttClient.println(temp_6);
  mqttClient.endMessage();

  mqttClient.beginMessage(topic7);
  mqttClient.println(temp_7);
  mqttClient.endMessage();

  mqttClient.beginMessage(topic8);
  mqttClient.println(temp_8);
  mqttClient.endMessage();

  mqttClient.beginMessage(topic9);
  mqttClient.println(temp_9);
  mqttClient.endMessage();

  mqttClient.beginMessage(topic10);
  mqttClient.println(temp_10);
  mqttClient.endMessage();
}


void kit2() {

  OneWire oneWire2(ONE_WIRE_BUS2);
  DallasTemperature DS18B20(&oneWire2);
  DS18B20.begin();
  DS18B20.requestTemperatures();
  temp_1 = DS18B20.getTempCByIndex(0);  // Sensor 0 will capture Temp in Celcius
  temp_2 = DS18B20.getTempCByIndex(1);  // Sensor 0 will capture Temp in Celcius
  temp_3 = DS18B20.getTempCByIndex(2);  // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor1, 0);    // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor2, 1);    // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor3, 2);    // Sensor 0 will capture Temp in Celcius
  if (contador <= 1) {
    Serial.print(EndSensor1[7], HEX);
    Serial.print("       ");
    Serial.print(EndSensor2[7], HEX);
    Serial.print("       ");
    Serial.print(EndSensor3[7], HEX);
    Serial.print("       ");
  } else {
    Serial.print(temp_1);
    Serial.print("    ");
    Serial.print(temp_2);
    Serial.print("    ");
    Serial.print(temp_3);
    Serial.print("    ");
  }
  delay(100);
}

void kit0() {

  OneWire oneWire0(ONE_WIRE_BUS0);
  DallasTemperature DS18B20(&oneWire0);
  DS18B20.begin();
  DS18B20.requestTemperatures();
  temp_4 = DS18B20.getTempCByIndex(0);  // Sensor 0 will capture Temp in Celcius
  temp_5 = DS18B20.getTempCByIndex(1);  // Sensor 0 will capture Temp in Celcius
  temp_6 = DS18B20.getTempCByIndex(2);  // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor1, 0);    // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor2, 1);    // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor3, 2);    // Sensor 0 will capture Temp in Celcius
  if (contador <= 1) {
    Serial.print(EndSensor1[7], HEX);
    Serial.print("       ");
    Serial.print(EndSensor2[7], HEX);
    Serial.print("       ");
    Serial.print(EndSensor3[7], HEX);
    Serial.print("       ");
  } else {
    Serial.print(temp_4);
    Serial.print("    ");
    Serial.print(temp_5);
    Serial.print("    ");
    Serial.print(temp_6);
    Serial.print("    ");
  }
  delay(100);
}

void kit5() {

  OneWire oneWire5(ONE_WIRE_BUS5);
  DallasTemperature DS18B20(&oneWire5);
  DS18B20.begin();
  DS18B20.requestTemperatures();
  temp_7 = DS18B20.getTempCByIndex(0);   // Sensor 0 will capture Temp in Celcius
  temp_8 = DS18B20.getTempCByIndex(1);   // Sensor 0 will capture Temp in Celcius
  temp_9 = DS18B20.getTempCByIndex(2);   // Sensor 0 will capture Temp in Celcius
  temp_10 = DS18B20.getTempCByIndex(3);  // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor1, 0);     // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor2, 1);     // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor3, 2);     // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor4, 3);     // Sensor 0 will capture Temp in Celcius
  if (contador <= 1) {
    Serial.print(EndSensor1[7], HEX);
    Serial.print("       ");
    Serial.print(EndSensor2[7], HEX);
    Serial.print("        ");
    Serial.print(EndSensor3[7], HEX);
    Serial.print("        ");
    Serial.print(EndSensor4[7], HEX);

  } else {
    Serial.print(temp_7);
    Serial.print("    ");
    Serial.print(temp_8);
    Serial.print("    ");
    Serial.print(temp_9);
    Serial.print("    ");
    Serial.print(temp_10);
  }
  delay(100);
}






//  temp_2 = DS18B20.getTempCByIndex(2); // Sensor 0 will capture Temp in Celcius
// temp_3 = DS18B20.getTempCByIndex(3); // Sensor 0 will capture Temp in Celcius
// temp_4 = DS18B20.getTempCByIndex(4); // Sensor 0 will capture Temp in Celcius
// temp_5 = DS18B20.getTempCByIndex(5); // Sensor 0 will capture Temp in Celcius
// temp_6 = DS18B20.getTempCByIndex(6); // Sensor 0 will capture Temp in Celcius
// temp_7 = DS18B20.getTempCByIndex(7); // Sensor 0 will capture Temp in Celcius
//temp_8 = DS18B20.getTempCByIndex(8); // Sensor 0 will capture Temp in Celcius
//temp_9 = DS18B20.getTempCByIndex(9); // Sensor 0 will capture Temp in Celcius
//  server.handleClient();

//  server.on("/sensor1", sensor1);
//  server.on("/sensor2", sensor2);
