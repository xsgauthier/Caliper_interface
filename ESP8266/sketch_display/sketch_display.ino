#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
// include plain C library
extern "C" {
#include "user_interface.h"
}
#include <ESP8266HTTPClient.h>

const char* ssid = "ESP-DRO-01";
const char* password = "3E345AF3213F";

String serverName = "";
unsigned long lastTime = 0;
unsigned long timerDelay = 200;

#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13

const int rs = D0, en = D2, d4 = D3, d5 = D4, d6 = D5, d7 = D6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

boolean waitingDHCP=false;
char last_mac[18];

boolean deviceIP(char* mac_device, String &cb) {

  struct station_info *station_list = wifi_softap_get_station_info();
  int station_id = 0;
  while (station_list != NULL) {
    char station_mac[18] = {0}; sprintf(station_mac, "%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(station_list->bssid));
    String station_ip = IPAddress((&station_list->ip)->addr).toString();

    if (strcmp(mac_device,station_mac)==0) {
      waitingDHCP=false;
      cb = station_ip;

      if (station_id == 0) {
        serverName = String("http://") + station_ip + String("/pos");
      }
      
      return true;
    } 

    station_id++;
    station_list = STAILQ_NEXT(station_list, next);
  }

  wifi_softap_free_station_info();
  cb = "DHCP not ready or bad MAC address";
  return false;
}

// Manage incoming device connection on ESP access point
void onNewStation(WiFiEventSoftAPModeStationConnected sta_info) {
  Serial.println("New Station :");
  sprintf(last_mac,"%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(sta_info.mac));
  Serial.printf("MAC address : %s\n",last_mac);
  Serial.printf("Id : %d\n", sta_info.aid);
  waitingDHCP=true;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
    
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(ssid);
  lcd.setCursor(0, 1);
  lcd.print("Connect...");
  lcd.setCursor(0, 1);  

  static WiFiEventHandler e1;

  e1 = WiFi.onSoftAPModeStationConnected(onNewStation);
  
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  /*
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());  
  */
}

void loop() {
  if (waitingDHCP) {
    String cb;
    if (deviceIP(last_mac,cb)) {
      Serial.println("Ip address :");
      Serial.println(cb); //do something
      lcd.clear();
    } else {
      //Serial.println("Problem during ip address request :");
      //Serial.println(cb); //do something else
    }
  }

  
  // put your main code here, to run repeatedly:
  if (serverName.length() > 0 && (millis() - lastTime) > timerDelay) {
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName;

      Serial.println(serverPath.c_str());
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
  
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        lcd.setCursor(0, 0);
        if (payload.length() > 2) {
          const char *pcstr = payload.c_str();
          int dplace = payload.length() - 3;
          if (pcstr[0] == '-') {
            lcd.print("-");
            pcstr++;
            dplace--;
          } else {
            lcd.print("+");
          }
          for (int i = (dplace+3); i < 5; i++) {
            lcd.print("0");
          }
          for (int i = 0;i < (dplace+3);i++)
          {
            lcd.print(pcstr[i]);
            if (i == dplace)
              lcd.print(".");
          }
        } else {
          const char *pcstr = payload.c_str();
          int dlen = payload.length();
          if (pcstr[0] == '-') {
            lcd.print("-");
            dlen--;
            pcstr++;
          } else {
            lcd.print("+");
          }
          if (dlen == 1)
          {
            lcd.print("000.0");
          }
          else
          {
            lcd.print("000.");
          }
          lcd.print(pcstr);
        }
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    lastTime = millis();
  }
}
