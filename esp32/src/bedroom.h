#include <Arduino.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PubSubClient.h> 

#ifndef bedroom_h
#define bedroom_h

//Pines
#define lightBedroom 13 // Led
#define ONE_WIRE_BUS 18 //Dallas
#define airBedroom 5 //Ventilador
const byte motorBedA = 12;
const byte motorBedB = 14;
const byte enableCeilingBedroom = 15; //Motor

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//variables
int brightnessBed = 0;  // Brillo inicial del LED (0-255)
bool ledStateBed = false;
int ventiladorSpeedBed = 0;      // Velocidad inicial del ventilador
int motorSpeedBed = 0;    // Velocidad inicial del motor
bool ventiladorStateBed = false;
bool motorStateBed = false;


void setupBedroom() {
  Serial.begin(115200);

  pinMode(lightBedroom, OUTPUT);
  pinMode(airBedroom, OUTPUT);
  pinMode(motorBedA, OUTPUT);
  pinMode(motorBedB, OUTPUT);
  pinMode(enableCeilingBedroom, OUTPUT);
  
  ledcAttachPin(lightBedroom, 2);   // Canal PWM led
  ledcSetup(2, 5000, 8);        
  ledcAttachPin(airBedroom, 5);   // Canal PWM ventilador
  ledcSetup(5, 5000, 8);   
  ledcAttachPin(enableCeilingBedroom, 6); // Canal PWM motor
  ledcSetup(6, 5000, 8);                 
}

void ledBrightnessBed(int value) {
  brightnessBed = constrain(value, 0, 255); // Asegurar que el brillo esté entre 0 y 255
  ledcWrite(2, brightnessBed);
}

void ledOnBed() {
  ledStateBed = true;
  ledBrightnessBed(brightnessBed); // Aplicar el brillo actual
}

void ledOffBed() {
  ledStateBed = false;
  ledBrightnessBed(0); // Apagar el LED
}

// Funciones para controlar el ventilador
void ventiladorBed(int value) {
  ventiladorSpeedBed = constrain(value, 0, 255); // Asegurar que la velocidad esté entre 0 y 255
  ledcWrite(5, ventiladorSpeedBed);             // Canal PWM para el ventilador
}

void ventiladorOnBed() {
  ventiladorStateBed = true;
  ventiladorBed(ventiladorSpeedBed); // Aplicar la velocidad actual
}

void ventiladorOffBed() {
  ventiladorStateBed = false;
  ventiladorBed(0); // Apagar el ventilador
}

// Funciones para controlar el motor
void motorBed(byte value) {
  motorSpeedBed = constrain(value, 0, 255); // Asegurar que la velocidad esté entre 0 y 255
  ledcWrite(6, motorSpeedBed);              // Canal PWM para el motor
}

void motorOnBed() {
  motorStateBed = true;
  motorBed(motorSpeedBed); // Aplicar la velocidad actual
}

void motorOffBed() {
  motorStateBed = false;
  motorBed(0); // Apagar el motor
}

float getTemperatureBed() {
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);
}


#endif


