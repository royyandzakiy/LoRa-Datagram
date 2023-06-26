#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <EEPROM.h>

// ROLE

// BOARD & LORA SETTINGS --------------------------

// Board Definition
// #define BRD_ARDUINO_UNO
#define BRD_ESP32

// Define pinout of the board used
#ifdef BRD_ARDUINO_UNO
// Arduino Uno
#define PIN_SS 10
#define PIN_RST 9
#define PIN_DIO0 2
#else defined(BRD_ESP32)
// ESP32
#define PIN_SS 5
#define PIN_RST 14
#define PIN_DIO0 2
#endif

#define EEPROM_SIZE 1 // ESP32 max 512, Arduino Uno max 1024. do not add more than this
#define EEPROM_ADDRESS_NODEID 0 // address to store NODEID
// #define NODEID 1

// Change sync word to (0xF3), make sure is same with Receiver
// Sync word ensures that it will not capture or send LoRa messages to other LoRa transceivers
// within range 0-0xFF
#define LORA_SIMPLE_SYNC_WORD 0xF0

//Change LoRa frequency using LoRa.begin(---E-)
//433E6 Asia
//866E6 Europe
//915E6 North America
#define LORA_SIMPLE_FREQUENCY 915E6