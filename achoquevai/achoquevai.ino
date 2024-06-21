#ifdef __cplusplus
extern "C" {
  #endif
  uint8_t temprature_sens_read();
  #ifdef __cplusplus
}
#endif

#include <ESPmDNS.h>
#include <WebServer.h>
#define WEB_SERVER WebServer

#define LOGGER_LOG_LEVEL 5            // Define log level for this module
#include <ControlAssist.h>            // Control assist class

const char st_ssid[]="kako";             // Put connection SSID here. On empty an AP will be started
const char st_pass[]="senai123";             // Put your wifi passowrd.
unsigned long pingMillis = millis(); // Ping millis

char chBuff[128];
static bool buttonState = false;
#define DELAY_MS 1000               // Measurements delay

WEB_SERVER server(80);              // Web server on port 80
ControlAssist ctrl;                 // Control assist class

#include "gaugePMem.h"              // Program html code definitions

// Change handler to handle web sockets changes
void changeHandler(uint8_t ndx){
  String key = ctrl[ndx].key;
  if(key == "check_ctrl" )
    buttonState = ctrl["check_ctrl"].toInt();
  LOG_D("changeHandler: ndx: %02i, key: %s = %s\n",ndx, key.c_str(), ctrl[key].c_str());
}
int getMemPerc(){
  uint32_t freeHeapBytes = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
  uint32_t totalHeapBytes = heap_caps_get_total_size(MALLOC_CAP_DEFAULT);
  float percentageHeapUsed = 100 - freeHeapBytes * 100.0f / (float)totalHeapBytes;
  return round(percentageHeapUsed);
}

void setup() {
  Serial.begin(115200);
  Serial.print("\n\n\n\n");
  Serial.flush();
  LOG_I("Starting..\n");

   // Connect WIFI ?
  if(strlen(st_ssid)>0){
    LOG_E("Connect Wifi to %s.\n", st_ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(st_ssid, st_pass);
    uint32_t startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 20000)  {
      Serial.print(".");
      delay(500);
      Serial.flush();
    }
    Serial.println();
  }

  // Check connection
  if(WiFi.status() == WL_CONNECTED ){
    LOG_I("Wifi AP SSID: %s connected, use 'http://%s' to connect\n", st_ssid, WiFi.localIP().toString().c_str());
  }else{
    LOG_E("Connect failed.\n");
    LOG_I("Starting AP.\n");
    String mac = WiFi.macAddress();
    mac.replace(":","");
    String hostName = "ControlAssist_" + mac.substring(6);
    WiFi.mode(WIFI_AP_STA);
    if(WiFi.softAP(hostName.c_str(),"",8))
      LOG_I("Wifi AP SSID: %s started, use 'http://%s' to connect\n", WiFi.softAPSSID().c_str(), WiFi.softAPIP().toString().c_str());
    else
      LOG_E("Wifi AP SSID: %s FAILED!\n", WiFi.softAPSSID().c_str());
    if (MDNS.begin(hostName.c_str()))  LOG_V("AP MDNS responder Started\n");
  }


  // Control assist setup
  ctrl.setHtmlHeaders(HTML_HEADERS);
  ctrl.setHtmlBody(HTML_BODY);
  ctrl.bind("rssi");
  ctrl.bind("mem");
  ctrl.bind("temp");
  
  // Every time a variable changed changeHandler will be called
  ctrl.setGlobalCallback(changeHandler);
  // Add a web server handler on url "/"

  ctrl.begin();
  LOG_V("ControlAssist started.\n");
  // Setup webserver
  server.on("/", []() {
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    String res = "";
    while( ctrl.getHtmlChunk(res)){
      server.sendContent(res);
    }
  });

  // Dump binded controls handler
  server.on("/d", []() {
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.sendContent("Serial dump\n");
    String res = "";
    while( ctrl.dump(res) ){
      server.sendContent(res);
    }
  });
  // Start web server
  server.begin();
  LOG_V("HTTP server started\n");
}

void loop() {
  // Update html control values
  if (millis() - pingMillis >= DELAY_MS){
    ctrl.put("rssi", String( WiFi.RSSI() ) );
    ctrl.put("mem", String( getMemPerc() ) );
    ctrl.put("temp", String( ((temprature_sens_read() - 32) / 1.8), 1 ));
    buttonState = !buttonState;
    pingMillis = millis();
  }

  // Handler webserver clients
  server.handleClient();
  // Handle websockets
  ctrl.loop();
  #if not defined(ESP32)
    if(MDNS.isRunning()) MDNS.update(); // Handle MDNS
  #endif
 }

 