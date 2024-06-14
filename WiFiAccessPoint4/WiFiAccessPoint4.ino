#include <WebServer.h>
#include <DallasTemperature.h>
//#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <WiFiManager.h>
//#include <ESP8266WebServer.h>



#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#define ONE_WIRE_BUS2 22 // DS18B20 on NodeMCU pin D22 
#define ONE_WIRE_BUS0 23 // DS18B20 on NodeMCU pin D23
#define ONE_WIRE_BUS5 21 // DS18B20 on NodeMCU pin D1 

#endif

const char *ssid = APSSID;
const char *password = APPSK;
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

void setup() {
  delay(1000);
  Serial.begin(115200);
}

void loop() {

  Serial.println();
  Serial.print(contador);
  ++contador;
  Serial.print("     ");
  kit2();
  kit0();
  kit5();
  delay(15000);
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
