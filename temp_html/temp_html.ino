#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <DallasTemperature.h>
#include <WiFiClient.h>
#include <WiFiManager.h>

const char* ssid     = "uPesy";
const char* password = "senai123";

IPAddress local_ip(192,168,0,1);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
#define ONE_WIRE_BUS2 22 // DS18B20 on NodeMCU pin D22 
#define ONE_WIRE_BUS0 23 // DS18B20 on NodeMCU pin D23
#define ONE_WIRE_BUS5 21 // DS18B20 on NodeMCU pin D1 


WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

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

DeviceAddress EndSensor1, EndSensor2, EndSensor3, EndSensor4, EndSensor5, EndSensor6, EndSensor7, EndSensor8, EndSensor9, EndSensor10;

void setup()
{
  Serial.begin(115200);
  Serial.println("\n[*] Creating AP");

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssid, password);

  Serial.print("[+] AP Created with IP Gateway ");
  Serial.println(WiFi.softAPIP());

  server.on("/", []() {
    server.send(200, "text\html", String(getPage()));
  });

  server.begin();
  webSocket.begin();
}

void client() {
  server.send (200, "text/html", getPage());
}

void loop(){

  server.handleClient();
  webSocket.loop();

  Serial.println();
  Serial.print(contador);
  ++contador;
  Serial.print("     ");
  kit2();
  kit0();
  kit5();
  delay(5000);
}  



void kit2() {

 OneWire oneWire2(ONE_WIRE_BUS2);
 DallasTemperature DS18B20(&oneWire2);
 DS18B20.begin();
 DS18B20.requestTemperatures(); 
  temp_1 = DS18B20.getTempCByIndex(0); // Sensor 0 will capture Temp in Celcius
  temp_2 = DS18B20.getTempCByIndex(1); // Sensor 0 will capture Temp in Celcius
  temp_3 = DS18B20.getTempCByIndex(2); // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor1 , 0); // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor2 , 1); // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor3 , 2); // Sensor 0 will capture Temp in Celcius
  if (contador <= 1) {  
  Serial.print(EndSensor1[7], HEX);
  Serial.print("       ");
  Serial.print(EndSensor2[7], HEX);
  Serial.print("       ");
  Serial.print(EndSensor3[7], HEX);
  Serial.print("       ");
  }
  else{
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
  temp_4 = DS18B20.getTempCByIndex(0); // Sensor 0 will capture Temp in Celcius
  temp_5 = DS18B20.getTempCByIndex(1); // Sensor 0 will capture Temp in Celcius
  temp_6 = DS18B20.getTempCByIndex(2); // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor1 , 0); // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor2 , 1); // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor3 , 2); // Sensor 0 will capture Temp in Celcius
  if (contador <= 1) {  
  Serial.print(EndSensor1[7], HEX);
  Serial.print("       ");
  Serial.print(EndSensor2[7], HEX);
  Serial.print("       ");
  Serial.print(EndSensor3[7], HEX);
  Serial.print("       ");
  }
  else{
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
  temp_7 = DS18B20.getTempCByIndex(0); // Sensor 0 will capture Temp in Celcius
  temp_8 = DS18B20.getTempCByIndex(1); // Sensor 0 will capture Temp in Celcius
  temp_9 = DS18B20.getTempCByIndex(2); // Sensor 0 will capture Temp in Celcius
  temp_10 = DS18B20.getTempCByIndex(3); // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor1 , 0); // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor2 , 1); // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor3 , 2); // Sensor 0 will capture Temp in Celcius
  DS18B20.getAddress(EndSensor4 , 3); // Sensor 0 will capture Temp in Celcius
  if (contador <= 1) {  
  Serial.print(EndSensor1[7], HEX);
  Serial.print("       ");
  Serial.print(EndSensor2[7], HEX);
  Serial.print("        ");
  Serial.print(EndSensor3[7], HEX);
  Serial.print("        ");
  Serial.print(EndSensor4[7], HEX);

  }
  else{
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
  page += "<title>PMMS</title>";
  page += "</head>";
  page += "<body>";
  page += "<h1>Sensores</h1>";
  page += "<div class='sensores'>";
  page += "<div class='flex'>";
  
  // Sensor 01 e Sensor 02
  page += "<div class='sensor' id='sensor-01'>";
  page += "<p>Sensor - 01</p>";
  page += "<div class='temp' id='temp-01'>";
  page += temp_1;
  page += "°C</div>";
  page += "<div class='status' id='status-01'>Ativo</div>";
  page += "</div>";
  
  page += "<div class='sensor' id='sensor-02'>";
  page += "<p>Sensor - 02</p>";
  page += "<div class='temp' id='temp-02'>";
  page += temp_2;
  page += "°C</div>";
  page += "<div class='status' id='status-02'>Ativo</div>";
  page += "</div>";
  
  page += "</div>";  // Fecha flex
  
  page += "<div class='flex'>";
  
  // Sensor 03 e Sensor 04
  page += "<div class='sensor' id='sensor-03'>";
  page += "<p>Sensor - 03</p>";
  page += "<div class='temp' id='temp-03'>";
  page += temp_3;
  page += "°C</div>";
  page += "<div class='status' id='status-03'>Ativo</div>";
  page += "</div>";
  
  page += "<div class='sensor' id='sensor-04'>";
  page += "<p>Sensor - 04</p>";
  page += "<div class='temp' id='temp-04'>";
  page += temp_4;
  page += "°C</div>";
  page += "<div class='status' id='status-04'>Ativo</div>";
  page += "</div>";
  
  page += "</div>";  // Fecha flex
  
  page += "<div class='flex'>";
  
  // Sensor 05 e Sensor 06
  page += "<div class='sensor' id='sensor-05'>";
  page += "<p>Sensor - 05</p>";
  page += "<div class='temp' id='temp-05'>";
  page += temp_5;
  page += "°C</div>";
  page += "<div class='status' id='status-05'>Ativo</div>";
  page += "</div>";
  
  page += "<div class='sensor' id='sensor-06'>";
  page += "<p>Sensor - 06</p>";
  page += "<div class='temp' id='temp-06'>";
  page += temp_6;
  page += "°C</div>";
  page += "<div class='status' id='status-06'>Ativo</div>";
  page += "</div>";
  
  page += "</div>";  // Fecha flex
  
  page += "<div class='flex'>";
  
  // Sensor 07 e Sensor 08
  page += "<div class='sensor' id='sensor-07'>";
  page += "<p>Sensor - 07</p>";
  page += "<div class='temp' id='temp-07'>";
  page += temp_7;
  page += "°C</div>";
  page += "<div class='status' id='status-07'>Ativo</div>";
  page += "</div>";
  
  page += "<div class='sensor' id='sensor-08'>";
  page += "<p>Sensor - 08</p>";
  page += "<div class='temp' id='temp-08'>";
  page += temp_8;
  page += "°C</div>";
  page += "<div class='status' id='status-08'>Ativo</div>";
  page += "</div>";
  
  page += "</div>";  // Fecha flex
  
  page += "<div class='flex'>";
  
  // Sensor 09 e Sensor 10
  page += "<div class='sensor' id='sensor-09'>";
  page += "<p>Sensor - 09</p>";
  page += "<div class='temp' id='temp-09'>";
  page += temp_9;
  page += "°C</div>";
  page += "<div class='status' id='status-09'>Ativo</div>";
  page += "</div>";
  
  page += "<div class='sensor' id='sensor-10'>";
  page += "<p>Sensor - 10</p>";
  page += "<div class='temp' id='temp-10'>";
  page += temp_10;
  page += "°C</div>";
  page += "<div class='status' id='status-10'>Ativo</div>";
  page += "</div>";
  
  page += "</div>";  // Fecha flex
  
  page += "</div>";  // Fecha sensores
  page += "</body></html>";
  
  return page;
}