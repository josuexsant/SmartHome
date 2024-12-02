#include <Arduino.h>
#include <ESP32Servo.h>

#ifndef bathroom_h
#define bathroom_h

//Pines
Servo servoBat;
#define lightBathroom 17 //Led
const int servoBathroom = 2; //Servo

//variables
int brightnessBat = 0;  
bool ledStateBat = false;
bool servoStateBat = false; 

void setupBathroom() {
  Serial.begin(115200);
  
  pinMode(lightBathroom, OUTPUT);     
  ledcAttachPin(lightBathroom, 9); // Canal PWM led
  ledcSetup(9, 5000, 8);   
  servoBat.attach(servoBathroom);
  servoBat.write(0);           
}

void ledBrightnessBat(int value) {
  brightnessBat = constrain(value, 0, 255); // Asegurar que el brillo esté entre 0 y 255
  ledcWrite(9, brightnessBat);
}

void ledOnBat() {
  ledStateBat = true;
  ledBrightnessBat(brightnessBat); // Aplicar el brillo actual
}

void ledOffBat() {
  ledStateBat = false;
  ledBrightnessBat(0); // Apagar el LED
}

void servoWaterBatOn() {
  servoStateBat = true;
  servoBat.write(90);
}

void servoWaterBatOff() {
  servoStateBat = false;
  servoBat.write(0);
}


#endif