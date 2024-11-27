#include <Arduino.h>
#include <ESP32Servo.h>

#define lightBathroom 17   // Si funciona
#define lightBedroom 13    // Si funciona
#define lightKitchen 18    // Si funciona
#define lightLivingRoom 19 // Si funciona
#define servoBathroom  14 // Si funciona
#define servoKitchen  27 // Si funciona 
#define servoDoor 33 // Si funciona
#define enableCeilingBedroom 25 //Motor

Servo servo;

const byte motorBedA = 5;
const byte motorBedB = 4;
const int motorChannel = 1;
const int freq = 5000;
const int resolution = 8;

void testLight(int pin)
{
  const int freq = 5000;
  const int ledChannel = 0;
  const int resolution = 8;
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(pin, ledChannel);

  for (int brightness = 255; brightness >= 0; brightness--)
  {
    ledcWrite(ledChannel, brightness);
    delay(10);
  }
  for (int brightness = 0; brightness <= 255; brightness++)
  {
    ledcWrite(ledChannel, brightness);
    delay(10);
  }
}

void testServo()
{
  for (int angle = 0; angle <= 180; angle++)
  {
    servo.write(angle);
    delay(15);
  }
  for (int angle = 180; angle >= 0; angle--)
  {
    servo.write(angle);
    delay(15);
  }
}

void control_izq(bool sentido, byte vel) {
  if (sentido) {
    digitalWrite(motorBedA, HIGH);
    digitalWrite(motorBedB, LOW);
  } else {
    digitalWrite(motorBedA, LOW);
    digitalWrite(motorBedB, HIGH);
  ledcWrite(motorChannel, vel);
  ledcWrite(0, vel);
}

void testMotor(){
  control_izq(true,255);
}

void setup()
{
  pinMode(motorBedA, OUTPUT);
  ledcSetup(motorChannel, freq, resolution);
  ledcAttachPin(enableCeilingBedroom, motorChannel);
  pinMode(lightBathroom, OUTPUT);
  pinMode(lightBathroom, OUTPUT);
  pinMode(lightBedroom, OUTPUT);
  pinMode(lightKitchen, OUTPUT);
  pinMode(lightLivingRoom, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hello World");
  servo.attach(servoDoor); // Conecta el servo al pin de test
}

void loop()
{
  //testServo();
  //testLight(lightBathroom);
  //testLight(lightBedroom);
  //testLight(lightKitchen);
  //testLight(lightLivingRoom);
  testMotor();
}
