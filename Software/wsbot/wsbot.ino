#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

bool ota_flag = true;
uint16_t time_elapsed = 0;


int M1A=16;//left motor A(fwd)
int M1B=14;//left motor B(rev)
int M2A=12;//right motor A(fwd)
int M2B=13;//right motor B(rev)
int rl=1;//red led
int gl=3;//green led
int bl=5;//blue led
int SF= 255;
int SB=255;
int SR=255;
int SL=255;
int SF1=255;
int SF2=255;
int SB1=255;
int SB2=255;
void fw();
void bw();
void rt();
void lt();
void stp();
void otainit();
void setup() {
  pinMode(M1A,OUTPUT);
  pinMode(M1B,OUTPUT);
  pinMode(M2A,OUTPUT);
  pinMode(M2B,OUTPUT);
  pinMode(rl,OUTPUT);
  pinMode(gl,OUTPUT);
  pinMode(bl,OUTPUT);
  digitalWrite(rl,HIGH);
  digitalWrite(gl,HIGH);
  digitalWrite(bl,HIGH);
  Serial.begin(115200);
  Serial.println("Booting");

  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  otainit();
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
   if(ota_flag)
  {
    while(time_elapsed < 20000)
    {
      ArduinoOTA.handle();
      time_elapsed = millis();
      delay(10);
    }
    ota_flag = false;
  }
  
  digitalWrite(rl,LOW);
  delay(1000);
  digitalWrite(rl,HIGH);
  delay(1000);
  digitalWrite(gl,LOW);
  delay(1000);
  digitalWrite(gl,HIGH);
  delay(1000);
  digitalWrite(bl,LOW);
  delay(1000);
  digitalWrite(bl,HIGH);
  delay(1000);
  fw();
  delay(2000);
  stp();
  delay(1000);
  bw();
  delay(2000);
  stp();
  delay(1000);
  rt();
  delay(2000);
  stp();
  delay(1000);
  lt();
  delay(2000);
  stp();
  delay(1000);
  // put your main code here, to run repeatedly:

}


void fw()
{
  analogWrite(M1A,SF);
  analogWrite(M2A,SF);
  analogWrite(M1B,0);
  analogWrite(M2B,0);
  }

  
void bw()
{
  analogWrite(M1A,0);
  analogWrite(M2A,0);
  analogWrite(M1B,SB);
  analogWrite(M2B,SB);  
  }

  
void rt()
{
  analogWrite(M1A,SR);
  analogWrite(M2A,0);
  analogWrite(M1B,0);
  analogWrite(M2B,0);
  }

  
void lt()
{
  analogWrite(M1A,0);
  analogWrite(M2A,SL);
  analogWrite(M1B,0);
  analogWrite(M2B,0);
  }


void fwd()
{
  analogWrite(M1A,SF1);
  analogWrite(M2A,SF2);
  analogWrite(M1B,0);
  analogWrite(M2B,0);
  }

void bwd()
{
  analogWrite(M1A,0);
  analogWrite(M2A,0);
  analogWrite(M1B,SB1);
  analogWrite(M2B,SB2);
  }

void stp()
{
  analogWrite(M1A,0);
  analogWrite(M2A,0);
  analogWrite(M1B,0);
  analogWrite(M2B,0);
  }

void otainit()
{
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  }
