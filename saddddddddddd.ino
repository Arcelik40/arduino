//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "aae9cdafdd364559a993787f2c0a826e";
char auth[] = "93f07bac6ee040e483d4453d11424359";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "turgut";
char pass[] = "turgut33";

/* TIMER */
#include <SimpleTimer.h>
SimpleTimer timer;

long distance = 0;

#define TRIGGER 14
#define ECHO    12

void setup()
{

  Serial.begin(115200);
  delay(10);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendUptime);
  timer.setInterval(100L, getSoilMoisterData);
}

void loop()
{

  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}

void sendUptime()
{
  if (distance < 400)
  {
    Blynk.virtualWrite(10, distance); //virtual pin V10
  }
  else
  {
    Blynk.virtualWrite(10, "yeniden hizzala"); //virtual pin V10
  }
}

void getSoilMoisterData(void)
{
  long duration;
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) / 29.1;


}

