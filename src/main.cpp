#include <Arduino.h>
#include "DatagramTable.h"

#include <SPI.h>
#include <LoRa.h>
#include <EEPROM.h>

//define the pins used by the transceiver module
/*// Arduino Uno
const int ss = 10;
const int rst = 9;
const int dio0 = 2; //*/

// ESP32 
const int ss = 5;
const int rst = 14;
const int dio0 = 2; //*/

const int EEPROM_SIZE = 1; // ESP32 max 512, Arduino Uno max 1024
const int EEPROM_ADDRESS_NODEID = 0; // tempat penyimpanan NODEID

int nodeId;
int counter, alert_status = 0;

void lora_setup() {
  Serial.println("=== LoRa Setup ===");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(915E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF0);
  Serial.println("...LoRa Initializing OK!");

  // cari tau nodeId diri sendiri
  nodeId = (int) EEPROM.read(EEPROM_ADDRESS_NODEID);
  Serial.print("nodeId at EEPROM address '" + (String) EEPROM_ADDRESS_NODEID + "' is: ");
  Serial.println((String) nodeId);
}

void send_packet() {
  // ubah paket menjadi datagramtable
  DatagramTable tempDatagramTable(0); // ukuran array of Datagram sudah di declare pada class

  Serial.print("nodeId " + (String) nodeId + " Sending datagram: ");
  String datagramTableString = tempDatagramTable.get_to_string();
  Serial.println(datagramTableString);
  
  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(datagramTableString);
  LoRa.endPacket();
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  EEPROM.begin(EEPROM_SIZE); // gunakan untuk ESP32
  
  lora_setup();
}

void loop() {
  send_packet();  
  counter++;
  delay(200);
}