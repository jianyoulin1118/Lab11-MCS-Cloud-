#include <LWiFi.h>
#include "MCS.h"

char _lwifi_ssid[] = "AA201-2G";
char _lwifi_pass[] = "iteaa201";
MCSDevice mcs("DAeVb991", "R87fr7RZmZ0IGAth");

MCSControllerOnOff LED_control("led");
MCSDisplayOnOff LED("remote");

void setup()
{
  Serial.begin(9600);

  Serial.println("Connect to Wifi");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    Serial.println("Wifi Reconnecting..");
    delay(1000);
  }
  mcs.addChannel(LED_control);
  mcs.addChannel(LED);
  Serial.println("Connect to MCS...");

  while (!mcs.connected()) {
    Serial.println("MCS Reconnecting..");
    mcs.connect();
  }
  Serial.println("MCS Connected!");
  


  pinMode(7, OUTPUT);

}


void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) {
      Serial.println("MCS Reconnect");
    }
  }
  while(!LED_control.valid())
  {
    Serial.println("read LED value from MCS...");
    LED_control.value();   //取得MCS數值
  }
  Serial.print("done, LED value = ");
  Serial.println(LED_control.value());

  mcs.process(1000);

  if (LED_control.value() == 1) {
    digitalWrite(7, HIGH);

  } else {
    digitalWrite(7, LOW);

  }
  if(!LED.set(LED_control.value()))
    {
      Serial.print("Failed to update remote");
      Serial.println(LED.value());
    }


  delay(200);
}
