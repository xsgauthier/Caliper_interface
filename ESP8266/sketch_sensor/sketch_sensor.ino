#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

//const char* ssid = "BELL729";
const char* ssid = "ESP-DRO-01";
const char* password = "3E345AF3213F";

#define D1 5
#define D2 4
#define D5 14
#define D6 12
#define D7 13

#define LED LED_BUILTIN
const int DCLK = D1;
const int DDAT = D2;

volatile unsigned char recv_buffer[6];
volatile unsigned char recv_i = 0;
volatile unsigned char recv_b = 0;
volatile unsigned char start_recv = 0;
volatile unsigned long lastTrigger = 0;

ICACHE_RAM_ATTR void DCLK_ISR() {
  if (start_recv) {
    if (!digitalRead(DDAT)) {
      recv_buffer[recv_i] |= 1 << recv_b;
    } else {
      recv_buffer[recv_i] &= ~(1 << recv_b);
    }
    recv_b++;
    if (recv_b == 4) {
      recv_b = 0;
      recv_i++;
      if (recv_i == 6) {
        recv_i = 0;
        start_recv = 0;
      }
    }
  }
  lastTrigger = millis();
}


AsyncWebServer server(80);
long pos;

String readPos() {
  return String(pos);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Started\n");

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi");

  server.on("/pos", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPos().c_str());
  });
  
  memset((void*)recv_buffer, 0, sizeof(recv_buffer));
  attachInterrupt(digitalPinToInterrupt(DCLK), DCLK_ISR, FALLING);

  server.begin();
}

unsigned long now = millis();

void loop() {
  // put your main code here, to run repeatedly:
  now = millis();
  if (start_recv == 0 && (now - lastTrigger) > (10)) {
    /*
    Serial.print((int)recv_buffer[0]);
    Serial.print(" ");
    Serial.print((int)recv_buffer[1]);
    Serial.print(" ");
    Serial.print((int)recv_buffer[2]);
    Serial.print(" ");
    Serial.print((int)recv_buffer[3]);
    Serial.print(" ");
    Serial.print((int)recv_buffer[4]);
    Serial.print(" ");
    Serial.print((int)recv_buffer[5]);
    Serial.println();
    */
    long value = (int)recv_buffer[0]
      + (16L * (int)recv_buffer[1])
      + (16L * 16L * (int)recv_buffer[2])
      + (16L * 16L * 16L * (int)recv_buffer[3]);
      + (16L * 16L * 16L * 16L * (int)recv_buffer[4]);
    if (recv_buffer[5] & 0x1) {
      value = -value;
    }
    if (recv_buffer[5] & 0x4) {
      Serial.print("[in] ");
      Serial.println(value*5);
    } else {
      Serial.print("[mm] ");
      Serial.println(value);
    }
    pos = value;
    
    start_recv = 1;
  }
}
