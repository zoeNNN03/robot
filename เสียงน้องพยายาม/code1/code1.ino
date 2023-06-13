#include <Servo.h>

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

int i = 90;
#define TRIG_PIN D6
#define ECHO_PIN D7
#define speaker D2

unsigned long last;
bool check = true;

Servo servo;

void turn_on(int dist) {
  if (millis() - last >= 5000) {
    digitalWrite(speaker, HIGH);
    delay(400);
    digitalWrite(speaker , LOW);
    delay(200);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(speaker, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  servo.attach(D3);
  servo.write(90);

}

void loop()
{
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(12);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  unsigned long dist = (0.034 * duration) / 2 ;
  Serial.print("Ultrasonic Sensor Distance = ");
  Serial.print(dist);
  Serial.println("cm");
  delay(200);
  
  if (dist <= 25 && check) {
    check = !check;
    turn_on(dist);
  }
  else if (dist <= 25 && !check){
    
    }
  else {
    check = true;
    }
    
  Blynk.run();
}

BLYNK_WRITE(V4)
{
  for (i ; i > 45; i--) {
    servo.write(i);
    delay(15);
  }
  Serial.println("headleft");
}

BLYNK_WRITE(V5)
{
  if (i > 90) {
    for (i ; i > 90; i--) {
      servo.write(i);
      delay(15);
    }
  }
  
  if (i < 90) {
    for (i ; i < 90; i++) {
      servo.write(i);
      delay(15);
    }
  }
  Serial.println("headfont");
}

BLYNK_WRITE(V6)
{

  for (i ; i < 135; i++) {
    servo.write(i);
    delay(15);
  }
  Serial.println("headright");
}
