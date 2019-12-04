//Include required packages
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//initializing I/O pins     
int LED = 13;
//enter your ssid & password
const char* ssid = "ssid";
const char* password = "password";

ESP8266WebServer server(80);
MDNSResponder mdns;
   
String webPage = "";
     

     
void setup(){
     
//assigning modes of port
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //creating HTML webpage  
  
  webPage += "<p>LED state <a href=\"LedON\"><button>ON</button></a>&nbsp;<a href=\"LedOFF\"><button>OFF</button></a></p>";
  
  WiFi.begin(ssid, password);
  Serial.println("");
     
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");  
  Serial.println(ssid);
  Serial.print("IP address: "); 
  Serial.println(WiFi.localIP());

  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
     
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  
  server.on("/LedON", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(LED, HIGH);
    Serial.println("[on]");
    delay(1000);
  });
  
  server.on("/LedOFF", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(LED, LOW);
    Serial.println("[off]");
    delay(1000);
  });

  
  
  server.begin();
  Serial.println("HTTP server started");
  
}
//main code to run repeatedly    
void loop(){
  server.handleClient();
}
