#include <ESP8266WiFi.h> 
#include <ThingerESP8266.h>

#define USERNAME "jako" //Username thinger.io
#define DEVICE_ID "ESP8266JAKO" 
#define DEVICE_CREDENTIAL "jakojako"

#define SSID "xyza"
#define SSID_PASSWORD "1sampek19"


ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

const int sensor = A0;
const int sensorMin = 0;
const int sensorMax = 1024;
float nilai;
float vout;

void setup() {
  //Thinger.io
  pinMode(sensor, INPUT);

  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, SSID_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  thing.add_wifi(SSID, SSID_PASSWORD);

  thing["inputan"] >> [](pson& out){
    out["cahaya"] = vout;
  };
}

void loop() {
  // put your main code here, to run repeatedly:
  thing.handle();

  vout = analogRead(sensor);
  int range = map(vout, sensorMin, sensorMax, 0, 3);

  switch(range){
    case 0:
      Serial.println("Banjir");
      break;
     case 1:
      Serial.println("Hujan");
      break;
     case 2:
      Serial.println("g ujan");
      break;
  }
  delay(500);
  Serial.print("\t");
}
