/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include "images.h"
#define DEMO_DURATION 3000
SSD1306  display(0x3c, 5, 4);
typedef void (*Demo)(void);
int demoMode = 0;
int counter = 1;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"



void partido(std::string value) {
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    std::string value2=value.substr(0, 1);
    std::string value3=value.substr(1, 1);
    std::string value4=value.substr(2, 2);
    char equipo1[value2.length()+1];
    char equipo2[value3.length()+1];
    char piedras[value4.length()+1];
    strcpy(msg,value2.c_str()); 
    strcpy(msg2,value3.c_str()); 
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(8, 0, "Piedras:");
    display.setFont(ArialMT_Plain_16);
    display.drawString(100, 0, piedras);
    display.setFont(ArialMT_Plain_16);
    display.drawString(8, 14, "Equipo1");
    display.setFont(ArialMT_Plain_16);
    display.drawString(100, 14, equipo1);
    display.setFont(ArialMT_Plain_16);
    display.drawString(8, 28, "Equipo 2:");
    display.setFont(ArialMT_Plain_16);
    display.drawString(100, 28, equipo2);
    display.setFont(ArialMT_Plain_16);
    display.drawString(8, 42, "Faltas:");
    display.setFont(ArialMT_Plain_16);
    display.drawString(100, 42, "00");
    display.display();
}

 void logo() {//dibuja la imagen introducida
    // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
    // on how to create xbm files
    display.clear();
    display.drawXbm(33, 0, skoll_width, skoll_height, skoll_bits);
    display.display();
}

void pantalla(std::string value) {
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/

    char msg[value.length()+1];
    strcpy(msg,value.c_str()); //copia datos directamente de un string
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
     display.setFont(ArialMT_Plain_24);
    display.drawStringMaxWidth(0, 0,128, msg);//limita el numero de caracteres en la linea y escribe en la siguiente si no entra
    Serial.println(msg);
    display.display();
    
}

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
 
      if (value.length() > 0) {      
 
        Serial.println("*********");
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);


        Serial.println();
        Serial.println("*********");
        partido(value);
        
       
      }
    }
};

void setup() {
  Serial.begin(115200);
// Initialising the UI will init the display too.
  display.init();
  display.clear();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  // write the buffer to the display
  
  display.display();
 
  logo();
  
  
  Serial.println("Starting BLE work!");

  BLEDevice::init("JuggerBand");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristic->setCallbacks(new MyCallbacks());
  
  pCharacteristic->setValue("Hello World says Neil");
  pService->start();
  
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
 
  delay(2000);
}
