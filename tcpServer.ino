#include <ESP8266WiFi.h>
#define PORT 4000
WiFiClient client; // 클라이언트 대리자를 선언
WiFiServer server(PORT);
String dataClient;
const char* ssid = "cse506cse506";  
const char* pass = "cse506cse506";  
#define LED 2 // GPIO 2

void setup() { 

  Serial.begin(115200); // 통신속도를 설정
  delay(200);
 Serial.println("\ntest TCPIP "); // 제목
  Serial.print("Port : ");
  Serial.println(PORT);
  pinMode(LED, OUTPUT); // 램프 포트를 출력으로 설정

   WiFi.begin(ssid, pass); // TCPIP 를 시작

  while (WiFi.status() != WL_CONNECTED) { // 연결시까지 대기
    Serial.print(".");
    delay(200); // 20밀리초 지연을 진행합니다
  }

  Serial.print("Point : ");
  Serial.println(ssid); // 무선네트워크 ID
  Serial.println("Alarm IP : ");
  Serial.print(WiFi.localIP()); // ex) 192.168.0.28
  delay(200);

  server.begin();
} 

void loop() {   
   while(!client.connected()) {   // TCPIP 가 끈어진 상태면?
      client = server.available();
   }

   while (client.connected()) { // TCPIP 가 연결된 상태면?
      if (client.available()) {
         char data = client.read(); // 수신버퍼에서 데이타 읽기
         dataClient += data; // 수신값을 추가합니다
         if (dataClient.equals("off")) { // 램프 끄기(OFF)면?
           digitalWrite(LED, HIGH); // 램프끄기(OFF)
           Serial.println("off");
           dataClient = ""; // 수신버퍼값을 초기화 
         }
         if (dataClient.equals("on")) { // 램프 켜기(ON)면?
           digitalWrite(LED, LOW); // 램프켜기(ON) LOW가 ON임
           Serial.println("on");
           dataClient = ""; // 수신버퍼값을 초기화 합니다
         }
      }
   }   
}

  
