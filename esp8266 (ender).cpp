#include <Arduino.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <stdio.h>

WiFiUDP UDP;

const char* ssid = "";
const char* password = "";
boolean wifiConnected = false;

comst char* ServerIP = ""

unsigned int localPort = 777;
boolean udpConnected = false;

char BufFromPC[128];
char b[5] = {0};
int IncomMesg = 0;   // для хранения полученного байта


boolean connectUDP();
boolean connectWifi();
void GetFromStmSendToPc();


void setup()
{
  Serial.begin(9600);

  wifiConnected = connectWifi();

  if (wifiConnected)
  {
    udpConnected = connectUDP();
  }
}

void loop()
{
  if (Serial.available() > 0){

    IncomMesg = Serial.parseInt();
    snprintf(b, 5, "%d", IncomMesg);
    if (wifiConnected)
    {
      if (udpConnected)
      {
        GetFromStmSendToPc();
      }

    }
  }
  delay(1000);
}

boolean connectUDP() //подключение udp
{
  boolean state = false;
  if (UDP.begin(localPort) == 1)
  {
    state = true;
  }
  return state;
}

boolean connectWifi()
{
  boolean state = true;
  int i = 0;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    if (i > 10)
    {
      state = false;
      break;
      Serial.print("wifi connect false");
    }
    i++;
  }
  Serial.print("wifi connect - ");
  Serial.print(state);
  return state;
}

void GetFromStmSendToPc()
{

    if (!(UDP.beginPacket(ServerIP, localPort)))
    {
      Serial.print("packege not send");
    }
    UDP.write(b);
    UDP.endPacket();
  
}

