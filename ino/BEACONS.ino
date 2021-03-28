// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Sketch shows how to use SimpleBLE to advertise the name of the device and change it on the press of a button
// Useful if you want to advertise some sort of message
// Button is attached between GPIO 0 and GND, and the device name changes each time the button is pressed

#include "SimpleBLE.h"
SimpleBLE ble;
int estadoLed;  //guarda el estado del led (encendido o apagado)
int periodo = 100;  // tiempo que esta el LED en alto y bajo
unsigned long tiempoAnterior = 0;  //guarda tiempo de referencia para comparar

void setup() 
{
    ble.begin("Bee3"); //nombre del dispositivo
    pinMode(32,OUTPUT);  //configura la salida      
}

void loop() 
{
  if(millis()-tiempoAnterior>=periodo){  //si ha transcurrido el periodo programado
    estadoLed=!estadoLed;  //cambia el estado del led cada 100ms
    digitalWrite(32,estadoLed);  //actualiza el estado del led
    tiempoAnterior=millis();  //guarda el tiempo actual como referencia
    }
}
