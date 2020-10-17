#include <DHT.h> //  DHT.h library
#include <ESP8266WiFi.h> // ESP8266WiFi.h library
#define DHTPIN D3
#define DHTTYPE  DHT11
const char* ssid     = "Hehe";
const char* password = "haha1999";
const char* host = "api.thingspeak.com";
const char* writeAPIKey = "WPMLRCX7987EZ265";
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // Initialize sensor
  Serial.begin(115200);
 // pinMode(A0,INPUT); 
  dht.begin();
  delay(1000);
//  Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");   
  }
}
void loop() {
  //int a=analogRead(A0);
 float humidity = dht.readHumidity();
 float temperature = dht.readTemperature();
 Serial.println(temperature);
 // Serial.println(temperature);
  if (isnan(humidity) || isnan(temperature)) {
    return;
  }
// make TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }
  String url = "/update?key=";
  url+=writeAPIKey;
  url+="&field1=";
  url+=String(temperature);
  url+="&field2=";
  url+=String(humidity);
  url+="\r\n";
  //Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" degrees Celcius, Humidity: ");
  Serial.print(humidity);
  Serial.println("%. Send to Thingspeak.");
  
  // Request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    delay(60000);
}
