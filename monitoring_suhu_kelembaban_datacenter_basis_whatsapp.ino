#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include <string.h>
#include <Wire.h>

#define DHTTYPE DHT22
#define dht_pin 2

DHT dht(dht_pin, DHTTYPE);
const char* WIFI_SSID = "nama_wifi";
const char* WIFI_PASS = "pass";
const char* NIM = "nim";
const char* PASS = "pass_nim";

float k;
    float s; 
    float bk;
    float bs;
    int pesan;

void setup() {
  dht.begin();
  Serial.begin(115200);
  Serial.println(F("\n\rESP BOOT"));
  Serial.println(F("WiFi begin!"));
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  HTTPClient http;
  http.begin("http://nas.ub.ac.id/ac_portal/login.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String kirim = "opr=pwdLogin&userName=";
  kirim += NIM;
  kirim += "&pwd=";
  kirim += PASS;
  kirim += "&rememberPwd=1";
  int httpCode = http.POST(kirim);
  if(httpCode > 0){
    Serial.println(http.getString());
  }
 http.end();

  Serial.println(F("\n\rWiFi connected!"));
}


void overheatno1() {

  char tekstual[245];
   char suhu[9];
  dtostrf(s, 7, 2, suhu);
  Serial.println(suhu);
  strcpy(tekstual, "Yth Pengelola Suhu Ruangan FILKOM UB, Pemberitahuan bahwa suhu ruang NOC B1.2 telah mencapai batas waspada, yakni");
  strcat(tekstual, suhu);
  strcat(tekstual, " °C");
  puts (tekstual);
  StaticJsonBuffer<300> JSONbuffer; 
  JsonObject& JSONencoder = JSONbuffer.createObject(); 
    
    JSONencoder["text"] = tekstual;
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
  
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  //nomor #1 - Pak Ivan
  https.begin(*client, "https://user.maxchat.id/uhtlfisip2020/api/chats/**no_wa_1**/messages");
  https.addHeader("Authorization", "Bearer C4eGwVpupjeiABg7YyCRj3");
    Serial.println("[HTTPS] GET...");
    int httpCode = https.POST(JSONmessageBuffer);

      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        String payload = https.getString();
        Serial.println(String("[HTTPS] Received payload: ") + payload);

    https.end();
    Serial.println(httpCode);
    Serial.println(payload);
}


void overheatno2() {

  char tekstual[245];
   char suhu[9];
  dtostrf(s, 7, 2, suhu);
  Serial.println(suhu);
  strcpy(tekstual, "Yth Pengelola Suhu Ruangan FILKOM UB, Pemberitahuan bahwa suhu ruang NOC B1.2 telah mencapai batas waspada, yakni");
  strcat(tekstual, suhu);
  strcat(tekstual, " °C");
  puts (tekstual);
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject(); 
    
    JSONencoder["text"] = tekstual;
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  //nomor #2 - Mas Yones
  https.begin(*client, "https://user.maxchat.id/uhtlfisip2020/api/chats/**no_wa_2**/messages");
  https.addHeader("Authorization", "Bearer C4eGwVpupjeiABg7YyCRj3");
    Serial.println("[HTTPS] GET...");
    int httpCode = https.POST(JSONmessageBuffer);

      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        String payload = https.getString();
        Serial.println(String("[HTTPS] Received payload: ") + payload);

    https.end();
    Serial.println(httpCode);
    Serial.println(payload);
}


void overheatno3() {

  char tekstual[245];
   char suhu[9];
  dtostrf(s, 7, 2, suhu);
  Serial.println(suhu);
  strcpy(tekstual, "Yth Pengelola Suhu Ruangan FILKOM UB, Pemberitahuan bahwa suhu ruang NOC B1.2 telah mencapai batas waspada, yakni");
  strcat(tekstual, suhu);
  strcat(tekstual, " °C");
  puts (tekstual);
  StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
  JsonObject& JSONencoder = JSONbuffer.createObject(); 
    
    JSONencoder["text"] = tekstual;
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  //nomor #3
  https.begin(*client, "https://user.maxchat.id/uhtlfisip2020/api/chats/**no_wa_3**/messages");// HTTPS
  https.addHeader("Authorization", "Bearer C4eGwVpupjeiABg7YyCRj3");
    Serial.println("[HTTPS] GET...");
    int httpCode = https.POST(JSONmessageBuffer);

      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        String payload = https.getString();
        Serial.println(String("[HTTPS] Received payload: ") + payload);

    https.end();
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
}


void loop() {
  k = dht.readHumidity();
  s = dht.readTemperature(); 

Serial.println("Kelembaban : ");
Serial.print(k);
Serial.print(" %");
Serial.println(" ");
Serial.println("Suhu : ");
Serial.print(s);
Serial.print(" °C");
Serial.println(" ");
if(isnan(k) || isnan(s)){
    k = 0;
    s = 0;
    k = dht.readHumidity();
    s = dht.readTemperature();
    delay(1000);
}

else{
 if (s>23 && pesan == 0){
    pesan ++;
    overheatno1();
    delay(2000);
    overheatno2();
    delay(2000);
    overheatno3();
    delay(2000);
  }
  else if (s>23 && pesan >= 1 && pesan < 720){
    pesan ++;
  }

  else if (s>23 && pesan == 720){
    pesan = 1;
    overheatno1();
    delay(2000);
    overheatno2();
    delay(2000);
    overheatno3();
    delay(2000);
  }
  else {
    pesan = 0;
  }
  Serial.println("Tunggu selang waktu 30d sebelum pengambilan data selanjutnya...");
  delay(30000);
}
}
