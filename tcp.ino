#include <ESP8266WiFi.h>
#include <Esp8266WiFiMulti.h> //다수의 wifi존에 접속 가능할 때

#ifndef STASSID
#define STASSID "cse506cse506"
#define STAPSK "cse506cse506"
#endif

const char* ssid  =STASSID;
const char* password =STAPSK;

const char* host = "192.168.0.46"; //사설 ip주소를 알아서 
const uint16_t port = 3000;

ESP8266WiFiMulti WiFiMulti;

void setup(){
  Serial.begin(115200);

  //We start by connection to wifi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password); //wifi하나를 포함

  Serial.println();
  Serial.println();
  Serial.print("Wait for WIFI... ");
  while(WiFiMulti.run() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}

void loop(){
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  /* Use WiFiClient class to create TCP connections */
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }
  // This will send the request to the server
  client.println("hello from ESP8266");

  //read back one line from server
  Serial.println("receiving from remote server");
  String line = client.readStringUntil('\r');
  Serial.println(line);

  Serial.println("closing connection");
  client.stop();

  Serial.println("wait 5 sec...");
  delay(5000);
}
