#include <Arduino.h>
#include <ESP32Servo.h>

#ifndef bathroom_h
#define bathroom_h

//Pines
Servo servoBat;
#define lightBathroom 17 //Led
const int servoBathroom = 19; //Servo

//variables
int brightnessBat = 0;  
bool ledStateBat = false;
bool servoStateBat = false; 

void setupBathroom() {
  pinMode(lightBathroom, OUTPUT);
  ledcAttachPin(lightBathroom, 0); // Canal para PWM
  ledcSetup(0, 5000, 8);           // Frecuencia, resolución
  servoBat.attach(servoBathroom);
  servoBat.write(0);                  
}

// Funciones para controlar el LED
void ledBrightnessBat(int value) {
  brightnessBat = constrain(value, 0, 255); // Asegurar que el brillo esté entre 0 y 255
  ledcWrite(0, brightnessBat);
}

void ledOnBat() {
  ledStateBat = true;
  ledBrightnessBat(brightnessBat); // Aplicar el brillo actual
}

void ledOffBat() {
  ledStateBat = false;
  ledBrightnessBat(0); // Apagar el LED
}

void servoWaterBat(bool state) {
  servoStateBat = state;
  if (servoStateBat) {
    servoBat.write(90); 
  } else {
    servoBat.write(0);  
  }
}

#endif