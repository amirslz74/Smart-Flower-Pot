
// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include <DHT.h>

// Replace with your network credentials
const char* ssid = "gando";
const char* password = "@e6974r*";

//DHT sensor configuration 
#define DHTPIN 32     // Digital pin connected to the DHT sensor
// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

// Set Relay GPIO
const int Relay_1 = 14;
const int Relay_2 = 4;
// Stores Relay state
String Relay_1_State;
String Relay_2_State;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readDHTTemperature() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float t = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}


// Replaces placeholder with Relay state value
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE1"){
    if(digitalRead(Relay_1)){
      Relay_1_State = "ON";
    }
    else{
      Relay_1_State = "OFF";
      }
    Serial.print(Relay_1_State);
    return Relay_1_State;
  }
  if(var == "STATE2"){
    //Serial.print("fuck");
    if(digitalRead(Relay_2)){
      Relay_2_State = "ON";
    }
    else{
      Relay_2_State = "OFF";
    }
    Serial.print(Relay_2_State);
    return Relay_2_State;
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  dht.begin();

  pinMode (Relay_1, OUTPUT);
  pinMode (Relay_2, OUTPUT);


  // Static IP Configuration
  IPAddress staticIP(192, 168, 1, 110);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress dns(192, 168, 1, 1);
  WiFi.config(staticIP, gateway, subnet, dns);


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
