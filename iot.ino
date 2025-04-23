/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPLSCChTfHl"
#define BLYNK_TEMPLATE_NAME "LED Controller"
#define BLYNK_AUTH_TOKEN "YFtXEtEo-HBjbfDcPpQ6QBTWfgMrxWGE"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define trig 12
#define echo 14
#define DHTPIN 0          // D3 pin
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Connected";
char pass[] = "999999999";
BlynkTimer timer;
DHT dht(DHTPIN, DHTTYPE);
int pinValue;
// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  pinValue = param.asInt();
}
BLYNK_WRITE(V9)
{
  int status = param.asInt();
  if(status == 1)
    digitalWrite(D8, 1);
  else digitalWrite(D8, 0);
}
bool automatic;
BLYNK_WRITE(V8)
{
  automatic = param.asInt();
}
BLYNK_WRITE(V7)
{
  int status = param.asInt();
  if(automatic == 0)
  {
    if(status == 1)
      digitalWrite(D7, 1);
    if(status == 0)
      digitalWrite(D7, 0);
  }
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Serial.println("Goriber Congratulation!");
}

void notifiaction() {
  bool sensor = digitalRead(D3);
  Serial.println(sensor);
  if (pinValue == 1) {
    Serial.println("System is ON");
    if (sensor == 1) {
      // Blynk.notify("WARNING! Please check your security system");
      Blynk.logEvent("thief_notification", String("WARNING! Please check your security system"));
      digitalWrite(D0, HIGH);
      // digitalWrite(D1, HIGH);
      // digitalWrite(D2, LOW);
    } else if (sensor == 0) {
      digitalWrite(D0, LOW);
      // digitalWrite(D1, LOW);
      // digitalWrite(D2, HIGH);
    }
  } else if (pinValue == 0) {
    Serial.println("System is OFF");
  }
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, h);
  Blynk.virtualWrite(V2, t);
}
double val =0;
bool d4status = 0;
void update()
{
  digitalWrite(2, d4status);
  d4status ^= 1;
  val = (val+.1);
  if(abs(val-.5)<.0000001)
    val = 0;
  Blynk.virtualWrite(V5, val);
}
double duration, distance;
void ultra()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration*.034/2;
  int low = 20, high = 10, percentage;
  if(distance >=high && distance <= low)
  {
    percentage = (low-distance)/10*100;
    Blynk.virtualWrite(V6, percentage);
    if(automatic)
    {    
      if(percentage<10)
        digitalWrite(D7, 1);
      if(percentage>90)
        digitalWrite(D7, 0);
    }
  }
  Blynk.virtualWrite(V4, distance);
  return;
}
unsigned long starting_time;
void thief_detection()
{
  // Read the PIR sensor value
  double pirValue = analogRead(A0);
  Serial.println(pirValue);
  Serial.println("okdone");
  // // If the PIR sensor detects motion
  unsigned long cur_time = millis();
  if (pirValue > 100) {
    starting_time = cur_time;
    digitalWrite(D2, 1);
    digitalWrite(D1, 1);
    return;
  }
  if(cur_time-starting_time >=3000)
  {
    digitalWrite(D2, 0);
    digitalWrite(D1, 0);
    return;
  }
  // if(cur_time-starting_time >=1000)
  // {
  //   digitalWrite(D2, 1);
  //   digitalWrite(D1, 0);
  //   return;
  // }
  // if(cur_time-starting_time >=1500)
  // {
  //   digitalWrite(D2, 0);
  //   digitalWrite(D1, 1);
  //   return;
  // }
  // if(cur_time-starting_time >=2000)
  // {
  //   digitalWrite(D2, 1);
  //   digitalWrite(D1, 0);
  //   return;
  // }
  // if(cur_time-starting_time >=2500)
  // {
  //   digitalWrite(D2, 0);
  //   digitalWrite(D1, 1);
  //   return;
  // }
  // digitalWrite(D2, 0);
  // digitalWrite(D1, 0);
  return;
}
void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(2, OUTPUT); // d4
  pinMode(0, OUTPUT); //d3
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(D3, INPUT);
  pinMode(D7, OUTPUT); // motor
  pinMode(D8, OUTPUT); // master light
  pinMode(A0, INPUT);
  pinMode(D2, OUTPUT); // buzzer pin
  pinMode(D1, OUTPUT); // red alert
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
  timer.setInterval(1000L, update);
  timer.setInterval(50L, ultra);
  timer.setInterval(50L, thief_detection);
  timer.setInterval(1000L, sendSensor);
  // timer.setInterval(1000L, notifiaction);

}

void loop()
{
  Blynk.run();
  timer.run();
}
