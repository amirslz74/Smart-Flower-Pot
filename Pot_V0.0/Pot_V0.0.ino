/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char* ssid = "gando";
const char* password = "@e6974r*";

// Set LED GPIO
const int Relay_1 = 14;
const int Relay_2 = 4;
// Stores LED state
String Relay_1_State;
String Relay_2_State;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE1"){
    if(digitalRead, Relay_1){
      Relay_1_State = "ON";
    }
    else{
      Relay_1_State = "OFF";
    }
    Serial.print(Relay_1_State);
    return Relay_1_State;
  }
  /*
  if(var == "STATE2"){
    if(digitalRead, Relay_2){
      Relay_2_State = "ON";
    }
    else{
      Relay_2_State = "OFF";
    }
    Serial.print(Relay_2_State);
    return Relay_2_State;
  }
  */
  return String();
}
 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode (Relay_1, OUTPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/on1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite (Relay_1, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/off1", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite (Relay_1, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to HIGH
  server.on("/on2", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite (Relay_2, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/off2", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite (Relay_2, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}