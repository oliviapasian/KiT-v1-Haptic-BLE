// --------------------------------------------------------

// This code was created by Olivia Pasian for Thinking Through Making with Michelle Gay

// The code uses the ArduinoBLE library to connect to a p5.js site which is used to toggle
// the vibration motor on / off using the sketch as a "remote"

// It also uses the Adafruit DRV2605 haptic motor driver library to output haptic patterns

//references:
// --adafruit haptic motor driver tutorial and example files: https://learn.adafruit.com/adafruit-drv2605-haptic-controller-breakout?view=all
// --C&C BLE files: 

// --------------------------------------------------------

//librariessss
#include <ArduinoBLE.h>
#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

BLEService hapticService("19b10000-e8f2-537e-4f6c-d104768a1214");
BLECharacteristic hapticCharacteristic("19b10001-e8f2-537e-4f6c-d104768a1214", BLEWrite, 10);

void setup() {
  Serial.begin(9600);
  if (Serial) {
    Serial.println("USB connected");
  }
  Serial.println("KiT Haptic Prototype v1");

  if (!drv.begin()) {
    Serial.println("Could not find DRV2605");
    while (1) delay(10);
  }

  drv.selectLibrary(1);
  // I2C trigger by sending 'go' command 
  drv.setMode(DRV2605_MODE_INTTRIG); // default, internal trigger when sending GO command

  if (!BLE.begin()) {
    Serial.println("BLE fail");
    while (1);
  }

  BLE.setLocalName("KeepInTouch");
  BLE.setAdvertisedService(hapticService);
  hapticService.addCharacteristic(hapticCharacteristic);
  BLE.addService(hapticService);
  BLE.advertise();

  Serial.println("BLE ready");
}

void playHapticPattern(int pattern) {
  // clear
  for (int i = 0; i < 8; i++) {
    drv.setWaveform(i, 0);
  }

  switch (pattern) {
    case 1:  // heartbeat/closeness
      // drv.setWaveform(0, 19);
      // drv.setWaveform(1, 18);
      // drv.setWaveform(2, 69);
      // drv.setWaveform(3, 19);
      // drv.setWaveform(4, 18);
      // drv.setWaveform(5, 69);
      // drv.setWaveform(6, 19);
      // drv.setWaveform(7, 18);
      // drv.setWaveform(8, 69);
      // drv.setWaveform(9, 19);
      // drv.setWaveform(10, 55);
      drv.setWaveform(0, 53);
      drv.setWaveform(1, 19);
      drv.setWaveform(2, 53);
      drv.setWaveform(3, 19);
      drv.setWaveform(4, 55);
      drv.setWaveform(5, 19);
      drv.setWaveform(6, 19);
      drv.setWaveform(7, 18);
      drv.setWaveform(8, 69);
      drv.setWaveform(9, 18);
      drv.setWaveform(10, 55);
      drv.setWaveform(11, 0); //end
      Serial.println("P1: heart/close");
      break;


    case 2:  // hug/squeeze
      drv.setWaveform(0, 84);
      drv.setWaveform(1, 13);
      drv.setWaveform(2, 119);
      drv.setWaveform(3, 119);
      drv.setWaveform(4, 119);
      drv.setWaveform(5, 119);
      drv.setWaveform(6, 120);
      drv.setWaveform(7, 120);
      drv.setWaveform(8, 121);
      drv.setWaveform(9, 122);
      drv.setWaveform(10, 0);//end
      Serial.println("P2: hug/squeeze");
      break;

    case 3:  // tap/attention
      drv.setWaveform(0, 1);
      drv.setWaveform(1, 59);
      drv.setWaveform(2, 68);
      drv.setWaveform(3, 0); //end
      Serial.println("P3: tap/attention");
      break;

    default:
      Serial.print("????");
      Serial.println(pattern);
      return;
  }

//start pattern
  drv.go();
  delay(100); 
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected: ");
    Serial.println(central.address());

    while (central.connected()) {
      if (hapticCharacteristic.written()) {
        int len = hapticCharacteristic.valueLength();
        const uint8_t* val = hapticCharacteristic.value();

        if (len > 0) {
          int pattern = val[0];
          Serial.print("received pattern no.: ");
          Serial.println(pattern);

          playHapticPattern(pattern);
        }
      }
    }

    Serial.println("Disconnected");
  }
}




//WORKING single haptic

/*
#include <ArduinoBLE.h>
#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

BLEService hapticService("19b10000-e8f2-537e-4f6c-d104768a1214");
BLECharacteristic hapticCharacteristic("19b10001-e8f2-537e-4f6c-d104768a1214", BLEWrite, 10);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Single vibration BLE test");

  if (!drv.begin()) {
    Serial.println("Could not find DRV2605");
    while (1) delay(10);
  }

  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);

  if (!BLE.begin()) {
    Serial.println("BLE init failed");
    while (1);
  }

  BLE.setLocalName("LivsNano33");
  BLE.setAdvertisedService(hapticService);
  hapticService.addCharacteristic(hapticCharacteristic);
  BLE.addService(hapticService);
  BLE.advertise();

  Serial.println("BLE ready");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to: ");
    Serial.println(central.address());

    while (central.connected()) {
      if (hapticCharacteristic.written()) {
        Serial.println("Trigger received! Playing vibration.");

        // Set a single waveform, e.g. 84 = strong click in library 1
        drv.setWaveform(0, 84);
        drv.setWaveform(1, 0); // end sequence
        drv.go();

        delay(100); // short delay to allow waveform to start
      }
    }

    Serial.println("Disconnected");
  }
}
*/



