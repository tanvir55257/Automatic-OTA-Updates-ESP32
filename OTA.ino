#include <stdio.h>
#include <string.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <ArduinoOTA.h>
#include <EEPROM.h>

long cv = 210519 ;

#define WIFI_CONNECT_SSID "tanvir"        // Wifi
#define WIFI_CONNECT_PSWD "12345678"        // Wifi you can use wifi manager for more simplicity
#define WIFI_CONNECT_WAIT_TIME  500
#define WIFI_CONNECT_WAIT_LIMIT 20
WiFiMulti wm ;

String otaDirURL      = "server address" ; // Server address for firmware
String otaCheckURL    = otaDirURL + "ota.php" ;
String otaBinFilename = "firmware" ;                 // firmware name
String otaBinURL      = otaDirURL + otaBinFilename ;

#define EEPROM_ID_STR      "OTA"
#define EEPROM_ID_STR_SIZE 10
#define EEPROM_SIZE        (EEPROM_ID_STR_SIZE + sizeof(cv))

void ReSet()
{  
  ESP.restart() ;  
}

void Connect2Network()
{
  int cc = 0 ;

  WiFi.persistent(true) ;
  WiFi.setAutoConnect(true) ;
  WiFi.setAutoReconnect(true) ;
  WiFi.mode(WIFI_STA) ;
  Serial.printf("Try connecting to WiFi with SSID '%s'\n", WIFI_CONNECT_SSID) ;

  wm.addAP(WIFI_CONNECT_SSID, WIFI_CONNECT_PSWD) ;
  delay(WIFI_CONNECT_WAIT_TIME) ;
  while (wm.run() != WL_CONNECTED) {
    if (cc++ >= WIFI_CONNECT_WAIT_LIMIT) {
      Serial.println("\nWiFi not conneted") ; 
      delay(WIFI_CONNECT_WAIT_TIME * 5) ;
      ReSet() ;
    } else Serial.print(".") ;
    delay(WIFI_CONNECT_WAIT_TIME) ;
  }

  Serial.println("\nWiFi connected.") ;
  Serial.print("SSID : ") ;
  Serial.println(WiFi.SSID()) ;
  Serial.print("My IP Address  : ") ;
  Serial.println(WiFi.localIP().toString()) ;
}

void EEPROM_WriteData(void)
{
  int i ;
  byte data[EEPROM_SIZE] ;

  memcpy(data, EEPROM_ID_STR, EEPROM_ID_STR_SIZE) ;
  memcpy(data + EEPROM_ID_STR_SIZE, &cv, sizeof(cv)) ;
  for (i = 0; i < EEPROM_SIZE; i++) EEPROM.write(i, data[i]) ;
  EEPROM.commit() ;
}

void EEPROM_ReadData(void)
{
  int i ;
  byte data[EEPROM_SIZE] ;

  for (i = 0; i < EEPROM_SIZE; i++) data[i] = (byte)EEPROM.read(i) ;
  if (memcmp(data, EEPROM_ID_STR, EEPROM_ID_STR_SIZE - 1) == 0) {
    memcpy(&cv, data + EEPROM_ID_STR_SIZE, sizeof(cv)) ;
  }
}

void OTA_Update(void)
{
  int hrc ;
  t_httpUpdate_return hur ;
  long nv ;
  HTTPClient http ;
  WiFiClient otaClient ;

  http.begin(otaCheckURL) ;
  hrc = http.GET() ;
  if (hrc > 0) {
    Serial.println(hrc) ;
    nv = http.getString().toInt() ;
  } else {
    Serial.print("Error code : ") ;
    Serial.println(hrc) ;
  }
  http.end() ;
  if (hrc <= 0) return ;
  if (nv > cv) { // New version
//Start OTA update
    httpUpdate.rebootOnUpdate(false) ;
    hur = httpUpdate.update(otaClient, otaBinURL) ;
    switch (hur) {
      case HTTP_UPDATE_FAILED :
        Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n\n",httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str()) ;
        break ;
      case HTTP_UPDATE_NO_UPDATES :
        break ;
      case HTTP_UPDATE_OK :
        cv = nv ;
        EEPROM_WriteData() ;
        ReSet() ;
        break ;
    }
  }
}

void setup()
{
  Serial.begin(115200) ;
  EEPROM.begin(EEPROM_SIZE) ;
  EEPROM_WriteData() ;

  Connect2Network() ;
  OTA_Update() ;

}

void loop()
{
}
