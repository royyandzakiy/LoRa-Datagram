// === BASIC
#include <Arduino.h>
#include "DatagramTable.h"
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

// === WiFi
// #include <ESP8266WiFi.h> // use for ESP8266
#include <WiFi.h> // use for anything else
#include <PubSubClient.h>

const char* ssid = "Ciheulang 3";
const char* password = "CBnotiga";
const char* mqtt_server = "192.168.1.7";

WiFiClient thisClient;
PubSubClient client(thisClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (100)
int value = 0;

// === OTHERS
unsigned long lastSecond;

// DatagramTable harus di declare disini
DatagramTable thisDatagramTable;


// ----------------------

// === WiFi
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void publish_packet(DatagramTable _datagramTable) {
  String datagramTableString = _datagramTable.get_to_string();
  String tempMsgString = "hello from nodeId " + (String) nodeId + "::" + datagramTableString;
  char msg[tempMsgString.length() + 1];
  strcpy(msg, tempMsgString.c_str());
  // snprintf (msg, MSG_BUFFER_SIZE, tempMsgString, 0);
  client.publish("outTopic/nodeId", msg);
  Serial.println("published::" + (String) msg);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "NodeClient-";
    clientId += (String) nodeId;
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      publish_packet(thisDatagramTable);
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

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

// DatagramTable harus di declare disini
// DatagramTable thisDatagramTable;

void send_packet() {
  Serial.print("nodeId " + (String) nodeId + " Sending datagram: ");
  String datagramTableString = thisDatagramTable.get_to_string();
  Serial.println(datagramTableString);
  
  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(datagramTableString);
  LoRa.endPacket();
}

void retrieve_packet() {
  // received a packet
  // read packet
  while (LoRa.available()) {
    // masukkan ke dalam format      
    String datagramTableStringPacket = LoRa.readString();

    // print RSSI of packet
    int rssiPacket = LoRa.packetRssi();

    Serial.println("=== Received then Updated DatagramTable state ===");
    Serial.print("nodeId " + (String) nodeId + " Received datagram ");
    Serial.print("with RSSI ");
    Serial.println((String) rssiPacket);

    Serial.println("packet : " + datagramTableStringPacket);

    // parse string to thisDatagramTable
    DatagramTable tempDatagramTable(datagramTableStringPacket);

    // update current thisDatagramTable
    thisDatagramTable.update(tempDatagramTable, rssiPacket);
    Serial.print("updated: ");
    thisDatagramTable.print();
    Serial.println();

    // publish thisDatagramTable to mqtt
    publish_packet(tempDatagramTable);
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
  Serial.begin(115200);
  while (!Serial);
  EEPROM.begin(EEPROM_SIZE); // gunakan untuk ESP32
  
  // === LoRa Setup
  lora_setup();
  thisDatagramTable.nodeId_set(nodeId);

  Serial.println("=== Initial DatagramTable state ===");
  thisDatagramTable.print();
  Serial.println();

  Serial.println("=== LoRa Node ===");
  lastSecond = millis();

  // === WiFi Setup
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() { 
    // pastikan wifi terhubung
    if (!client.connected()) {
      reconnect();
    }
    client.loop();

    // listen paket lora tiap saat
    listen_packet();

    unsigned long now = millis();
    // send 3 paket lora tiap 3 detik 
    if (now - lastSecond > 3000) { // kirim tiap 3 detik
      lastSecond = now;

      Serial.println("=== Sending DatagramTable ===");

      int iterasiPengiriman = 1;
      for (int i=0; i<iterasiPengiriman; i++) {
        send_packet();       
        publish_packet(thisDatagramTable);
        delay(50);
      }
    }
}