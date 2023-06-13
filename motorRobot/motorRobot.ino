#define BLYNK_TEMPLATE_ID "TMPLKvzxz5sN"
#define BLYNK_TEMPLATE_NAME "LED2"
#define BLYNK_AUTH_TOKEN "dLzJwJQ6HLsS3fAAWBd8EHo3tkss9zlC"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "NetForArt";
char pass[] = "netnut00";

//char ssid[] = "pahn";
//char pass[] = "12345679";

#define motorPin1 D5  // Motor pin 5 (IN1) connected to ESP8266 D5 pin
#define motorPin2 D6  // Motor pin 6 (IN2) connected to ESP8266 D6 pin
#define motorPin3 D7  // Motor pin 7 (IN3) connected to ESP8266 D7 pin
#define motorPin4 D8  // Motor pin 8 (IN4) connected to ESP8266 D8 pin

BlynkTimer timer;

void motorControl(int font, int left, int back, int right)
{
  Serial.print("order : ");
  Serial.print(font);
  Serial.print(left);
  Serial.print(back);
  Serial.println(right);
  if (font > 0) {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    Serial.println("font");
  }
  else if (left > 0)
  {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    Serial.println("left");
  }
  else if (back > 0)
  {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    Serial.println("back");
  }
  else if (right > 0)
  {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    Serial.println("right");
  }
  else
  {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    Serial.println("stop");
  }
}

BLYNK_WRITE(V0)
{
  int font = param.asInt();
  int left = 0;
  int back = 0;
  int right = 0;
  motorControl(font, left, back, right);
}

BLYNK_WRITE(V1)
{
  int font = 0;
  int left = param.asInt();
  int back = 0;
  int right = 0;
  motorControl(font, left, back, right);
}

BLYNK_WRITE(V2)
{
  int font = 0;
  int left = 0;
  int back = param.asInt();
  int right = 0;
  motorControl(font, left, back, right);
}

BLYNK_WRITE(V3)
{
  int font = 0;
  int left = 0;
  int back = 0;
  int right = param.asInt();
  motorControl(font, left, back, right);
}

void setup()
{
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
  timer.run();
}
