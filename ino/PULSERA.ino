/*
0001_bienvenido
0002_living
0003_baño
0004_cocina
0005_balcon
0006_pieza
 */
#include <Adafruit_NeoPixel.h>

#define PIN 32 //Designamos nuestro pin de datos
#define NUMPIXELS      2 //Designamos cuantos pixeles tenemos en nuestra cinta led RGB
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// IMPORTANTE: Para reducir el riesgo de dañar los pixeles de la cinta, añada un condensador de 1000 uF a través de
// los cables de alimentación de la cinta, agregue una resistencia de 300-500 Ohm en la entrada de datos del primer pixel
// Y reduzca la distancia entre Arduino y el primera pixel.

uint32_t rojo = pixels.Color(150,0,0);
uint32_t verde = pixels.Color(0,150,0);
uint32_t azul = pixels.Color(0,0,150);
uint32_t apagado = pixels.Color(0,0,0);
uint32_t amarillo = pixels.Color(150,150,0);
uint32_t morado = pixels.Color(150,0,150);
uint32_t celeste = pixels.Color(0,150,150);
uint32_t blanco = pixels.Color(150,150,150);

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <Arduino.h>
#include "DFRobotDFPlayerMini.h"

HardwareSerial mySoftwareSerial(1); //rxMP3=17esp TXmp3=16esp
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
int scanTime = 1; //In seconds
BLEScan* pBLEScan;
String BeaconUUID;
int RSSID = 0;
String Address;
int RSSID_living = 0;
String Address_living;
int RSSID_room = 0;
String Address_room;
int RSSID_bath = 0;
String Address_bath;

String Beacon1= "7c:9e:bd:f5:09:e2";
String Beacon2="7c:9e:bd:f5:07:92";
String Beacon3="7c:9e:bd:f5:01:fe";

int DIST_LIVING=75; //antes 60 define el RSSI necesario para activar
int DIST_ROOM=75; //antes 60 define el RSSI necesario para activar
int DIST_BATH=75; //antes 60 define el RSSI necesario para activar

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      //Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

void setup()
{
  pixels.begin(); 
  mySoftwareSerial.begin(9600, SERIAL_8N1, 16, 17);  // speed, type, RX, TX
  Serial.begin(115200);  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial))  //Use softwareSerial to communicate with mp3.
   { 
    Serial.println(myDFPlayer.readType(),HEX);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  //----Set volume----
  myDFPlayer.volume(25);  //Set volume value (0~30).
  myDFPlayer.volumeUp(); //Volume Up
  myDFPlayer.volumeDown(); //Volume Down  
  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);  
  //----Set device we use SD as default----
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  myDFPlayer.play(2);   //--------------------------------------Play the first mp3 BIENVENIDO
  delay(1000);
  int delayms=100;  
  Serial.println(F("myDFPlayer.play(1)"));                                         
  Serial.println("Scanning...");
  
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
  LED(celeste);
}
//------------------------------------------------------
void loop()
{ 
  LED(apagado);
  pixels.clear();
  pixels.show();
  
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  int BeaconCount=foundDevices.getCount();
   for (int i=0; i<BeaconCount; i++)
   {   LED(apagado);
       pixels.clear();
       pixels.show();
       BLEAdvertisedDevice d=foundDevices.getDevice(i);
       Serial.print("Address=");
       String BeaconAddress=d.getAddress().toString().c_str();
       Serial.print(BeaconAddress);
       int BeaconRSSI=d.getRSSI();
       Serial.print('\t');
       Serial.print("RSSI=");
       Serial.println(BeaconRSSI);//Show RSSI
       LED(apagado);
       pixels.clear();
       pixels.show();
       if(BeaconAddress == Beacon1)
       {
          LED(apagado);
          pixels.clear();
          pixels.show();
          Address_living = Beacon1;
          RSSID_living = BeaconRSSI;
          if(-RSSID_living<= DIST_LIVING)
          {    
             LED(apagado);
             pixels.clear();
             pixels.show();          
             myDFPlayer.play(1); //0002_living 0003_baño 0004_cocina  2bienvenido
             pixels.clear();
             pixels.show();
             LED(rojo);             
             //AGREGAR VARIABLE DE ESTADO PARA NO REPETIR AUDIO INFINITAS VECES
          } delay(1000);
       }
       else if(BeaconAddress == Beacon2)
       {
          LED(apagado);
          pixels.clear();
          pixels.show();   
          Address_room = Beacon2;
          RSSID_room = BeaconRSSI;           
          if(-RSSID_room<= DIST_ROOM)
          {  
            LED(apagado);
            pixels.clear();
            pixels.show();              
            myDFPlayer.play(3); //0002_living 0003_baño 0004_cocina
            pixels.clear();
            pixels.show();
            LED(amarillo);             
            
          } delay(1000);
            //AGREGAR VARIABLE DE ESTADO PARA NO REPETIR AUDIO INFINITAS VECES
       }
       else if(BeaconAddress == Beacon3)
       {
          LED(apagado);
          pixels.clear();
          pixels.show();   
          Address_bath = Beacon3;
          RSSID_bath = BeaconRSSI;           
          if(-RSSID_bath<= DIST_BATH)
          {   
            LED(apagado);
            pixels.clear();
            pixels.show();             
            myDFPlayer.play(4); //0002_living 0003_baño 0004_cocina
            pixels.clear();
            pixels.show();
            LED(morado);             
            
          } delay(1000);
            //AGREGAR VARIABLE DE ESTADO PARA NO REPETIR AUDIO INFINITAS VECES
       }
      else
       {
          Address =  BeaconAddress;
          RSSID = 65;
          LED(apagado);
          pixels.clear();
          pixels.show();
        // delay(100);
       } 
   }

  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(10);
  LED(apagado);
  pixels.clear();
  pixels.show();
}

//----------------------------------------------------

void printDetail(uint8_t type, int value)
{
  switch (type) 
  {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

void LED(uint32_t COLOR)
{  
   // for(int i=0;i<NUMPIXELS;i++)
   //  {
      //pixels.clear(); // Apagamos todos los LEDs
      
      pixels.setPixelColor(0, COLOR); // Brillo moderado en rojo
      pixels.setPixelColor(1, COLOR); // Brillo moderado en rojo
      pixels.show();   // Mostramos y actualizamos el color del pixel de nuestra cinta led RGB
      delay(100); // Pausa por un periodo de tiempo (en milisegundos).
     // pixels.setPixelColor(i, apagado); // Brillo moderado en azul
     // pixels.show();   // Mostramos y actualizamos el color del pixel de nuestra cinta led RGB
     // delay(100); // Pausa por un periodo de tiempo (en milisegundos).          
  //   }  
}
