// === BASIC
#include <Arduino.h>
#include "RoutingTable.h"
#include <SPI.h>
#include <EEPROM.h>

const int EEPROM_SIZE = 1; // ESP32 max 512, Arduino Uno max 1024
const int EEPROM_ADDRESS_NODEID = 0; // tempat penyimpanan NODEID
int nodeId;

// === LoRa
#include <LoRa.h>

//define the pins used by the transceiver module
/*// Arduino Uno
const int ss = 10;
const int rst = 9;
const int dio0 = 2; //*/

// ESP32 
const int ss = 5;
const int rst = 14;
const int dio0 = 2; //*/

// === OTHERS
unsigned long lastSecond;

// RoutingTable harus di declare disini
RoutingTable thisRoutingTable;


// ----------------------

// === LoRa
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
  Serial.println("nodeId at EEPROM address '" + (String) EEPROM_ADDRESS_NODEID + "' is: " + (String) nodeId);
}

void send_packet() {
  Serial.print("nodeId " + (String) nodeId + " Sending routing: ");
  String routingTableString = thisRoutingTable.get_to_string();
  
  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(routingTableString);
  LoRa.endPacket();
  Serial.println(routingTableString);
}

void retrieve_packet() {
  // received a packet
  // read packet
  while (LoRa.available()) {
    // masukkan ke dalam format      
    String routingTableStringPacket = LoRa.readString();

    // print RSSI of packet
    int rssiPacket = LoRa.packetRssi();

    Serial.println("=== Received then Updated RoutingTable state ===");
    Serial.print("nodeId " + (String) nodeId + " Received routing ");
    Serial.print("with RSSI ");
    Serial.println((String) rssiPacket);

    Serial.println("packet : " + routingTableStringPacket);

    // parse string to thisRoutingTable
    RoutingTable tempRoutingTable(routingTableStringPacket);

    // update current thisRoutingTable
    thisRoutingTable.update(tempRoutingTable, rssiPacket);
    Serial.print("updated: ");
    thisRoutingTable.print();
    Serial.println();
  }
}

void listen_packet() {
  int packetSize = LoRa.parsePacket(); // watchdog
  if (packetSize) {
    retrieve_packet();
  }
}

// ----------------------

void setup() {
  Serial.begin(9600);
  while (!Serial);
  EEPROM.begin(EEPROM_SIZE); // gunakan untuk ESP32
  
  // === LoRa Setup
  lora_setup();
  thisRoutingTable.set_nodeId(nodeId);

  Serial.println("=== Initial RoutingTable state ===");
  thisRoutingTable.print();
  Serial.println();

  Serial.println("=== LoRa Node ===");
  lastSecond = millis();
}

void loop() { 
    // listen paket lora tiap saat
    listen_packet();

    unsigned long now = millis();
    // send 3 paket lora tiap 3 detik 
    int intervalPengiriman = 3000;
    int selisihWaktu = now - lastSecond;
    if (selisihWaktu > intervalPengiriman) { // kirim tiap 3 detik
      lastSecond = now;

      Serial.println("=== Sending RoutingTable ===");

      // jumlah paket yang dikirim dan publish dalam satu waktu, ubah jika dirasa ada paket loss
      int iterasiPengiriman = 1;
      for (int i=0; i<iterasiPengiriman; i++) {
        send_packet();
        delay(50);
      }
    }
}