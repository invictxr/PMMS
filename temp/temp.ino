#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <ArduinoJson.h>

const char* ssid = "uPesy";
const char* password = "senai123";

IPAddress local_ip(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
#define ONE_WIRE_BUS2 22 // DS18B20 no pino D22 do NodeMCU
#define ONE_WIRE_BUS0 23 // DS18B20 no pino D23 do NodeMCU
#define ONE_WIRE_BUS5 21 // DS18B20 no pino D21 do NodeMCU

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

float temp_1, temp_2, temp_3, temp_4, temp_5, temp_6, temp_7, temp_8, temp_9, temp_10;
int contador = 0;

DeviceAddress EndSensor1, EndSensor2, EndSensor3, EndSensor4, EndSensor5, EndSensor6, EndSensor7, EndSensor8, EndSensor9, EndSensor10;

void setup() {
  Serial.begin(115200);
  Serial.println("\n[*] Criando AP");

  WiFi.mode(WIFI_AP); // Modo ponto de acesso
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);

  Serial.print("[+] AP criado com IP ");
  Serial.println(WiFi.softAPIP());

  server.on("/", []() {
    server.send(200, "text/html", getPage());
  });

  server.begin();
  webSocket.begin();
}

void loop() {
  server.handleClient();
  webSocket.loop();
  Serial.println();

  // Atualiza os dados dos sensores
  contador++;
  kit2();
  kit0();
  kit5();

  // Envia dados via WebSocket a cada ciclo
  sendSensorDataViaWebSocket();

  delay(15000); // Intervalo entre leituras
}

void sendSensorDataViaWebSocket() {
  StaticJsonDocument<200> jsonDoc;

  // Adicione os dados dos sensores ao documento JSON
  jsonDoc["temp_1"] = temp_1;
  jsonDoc["temp_2"] = temp_2;
  jsonDoc["temp_3"] = temp_3;
  jsonDoc["temp_4"] = temp_4;
  jsonDoc["temp_5"] = temp_5;
  jsonDoc["temp_6"] = temp_6;
  jsonDoc["temp_7"] = temp_7;
  jsonDoc["temp_8"] = temp_8;
  jsonDoc["temp_9"] = temp_9;
  jsonDoc["temp_10"] = temp_10;

  // Converta o JSON em uma string JSON
  String jsonStr;
  serializeJson(jsonDoc, jsonStr);

  // Envie a mensagem JSON para todos os clientes conectados ao WebSocket
  webSocket.broadcastTXT(jsonStr);
}

void kit2() {
  OneWire oneWire2(ONE_WIRE_BUS2);
  DallasTemperature DS18B20(&oneWire2);
  DS18B20.begin();
  DS18B20.requestTemperatures();
  temp_1 = DS18B20.getTempCByIndex(0);
  temp_2 = DS18B20.getTempCByIndex(1);
  temp_3 = DS18B20.getTempCByIndex(2);
  DS18B20.getAddress(EndSensor1, 0);
  DS18B20.getAddress(EndSensor2, 1);
  DS18B20.getAddress(EndSensor3, 2);
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
  temp_4 = DS18B20.getTempCByIndex(0);
  temp_5 = DS18B20.getTempCByIndex(1);
  temp_6 = DS18B20.getTempCByIndex(2);
  DS18B20.getAddress(EndSensor4, 0);
  DS18B20.getAddress(EndSensor5, 1);
  DS18B20.getAddress(EndSensor6, 2);
  if (contador <= 1) {
    Serial.print(EndSensor4[7], HEX);
    Serial.print("       ");
    Serial.print(EndSensor5[7], HEX);
    Serial.print("       ");
    Serial.print(EndSensor6[7], HEX);
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
  temp_7 = DS18B20.getTempCByIndex(0);
  temp_8 = DS18B20.getTempCByIndex(1);
  temp_9 = DS18B20.getTempCByIndex(2);
  temp_10 = DS18B20.getTempCByIndex(3);
  DS18B20.getAddress(EndSensor7, 0);
  DS18B20.getAddress(EndSensor8, 1);
  DS18B20.getAddress(EndSensor9, 2);
  DS18B20.getAddress(EndSensor10, 3);
  if (contador <= 1) {
    Serial.print(EndSensor7[7], HEX);
    Serial.print("       ");
    Serial.print(EndSensor8[7], HEX);
    Serial.print("        ");
    Serial.print(EndSensor9[7], HEX);
    Serial.print("        ");
    Serial.print(EndSensor10[7], HEX);
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

String getPage() {
  String page = "<!DOCTYPE html><html lang='pt-BR'>";
  page += "<head>";
  page += "<meta charset='UTF-8'>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<style>";
  page += "* { font-family: Arial, Helvetica, sans-serif; font-size: 15px; color: #fff; }";
  page += "body { background-color: black; text-align: center; }";
  page += "h1 { font-size: 30px; font-weight: 700; }";
  page += ".sensores { flex-wrap: wrap; justify-content: center; align-items: center; }";
  page += ".flex { display: flex; flex-wrap: wrap; justify-content: center; align-items: center; }";
  page += ".sensor { width: 120px; padding: 18px; margin: 5px; flex-direction: column; align-items: center; justify-content: center; background: #252525; border-radius: 40px; box-shadow: 0px 0px 5px -3px #fff; }";
  page += ".sensor p { font-size: 18px; font-weight: 600; }";
  page += ".temp { font-size: 30px; font-weight: 600; color: #fff; margin: 25px 0 25px 0; }";
  page += ".sensor p, .sensor .status { margin: 0; }";
  page += "</style>";
  page += "<title>Temperaturas</title>";
  page += "<script>";
  page += "var socket = new WebSocket('ws://' + window.location.hostname + ':81/');";
  page += "socket.onmessage = function(event) {";
  page += "  var data = JSON.parse(event.data);";
  page += "  document.getElementById('temp-01').textContent = data.temp_1.toFixed(2) + '°C';";
  page += "  document.getElementById('temp-02').textContent = data.temp_2.toFixed(2) + '°C';";
  page += "  document.getElementById('temp-03').textContent = data.temp_3.toFixed(2) + '°C';";
  page += "  document.getElementById('temp-04').textContent = data.temp_4.toFixed(2) + '°C';";
  page += "  document.getElementById('temp-05').textContent = data.temp_5.toFixed(2) + '°C';";
  page += "  document.getElementById('temp-06').textContent = data.temp_6.toFixed(2) + '°C';";
  page += "  document.getElementById('temp-07').textContent = data.temp_7.toFixed(2) + '°C';";
  page += "  document.getElementById('temp-08').textContent = data.temp_8.toFixed(2) + '°C';";
  page += "  document.getElementById('temp-09').textContent = data.temp_9.toFixed(2) + '°C';";
  page += "  document.getElementById('temp-10').textContent = data.temp_10.toFixed(2) + '°C';";
  page += "}";
  page += "</script>";
  page += "</head>";
  page += "<body>";
  page += "<h1>Sensores</h1>";
  page += "<div class='sensores'>";
  page += "<div class='flex'>";
  
  // Sensores 01 a 10
  for (int i = 1; i <= 10; i++) {
    page += "<div class='sensor' id='sensor-" + String(i) + "'>";
    page += "<p>Sensor - " + String(i) + "</p>";
    page += "<div class='temp' id='temp-" + String(i) + "'>--°C</div>";
    page += "<div class='status' id='status-" + String(i) + "'>Ativo</div>";
    page += "</div>";
  }

  page += "</div>";  // Fecha flex
  page += "</div>";  // Fecha sensores
  page += "</body></html>";

  return page;
}