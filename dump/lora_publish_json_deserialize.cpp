#include <ArduinoJson.h>
#include "Datagram.h"

int nodeId;

void setup() {
    Serial.begin(115200);
    nodeId = 2;

    String datagramTableString = "{\"2\": [{\"n\":1,\"r\":-44},{\"n\":255,\"r\":0},{\"n\":3,\"r\":-13}]}";

    // DATAGRAMTABLE SERIALIZATION
    const size_t DATAGRAMTABLEDOC_SIZE = JSON_ARRAY_SIZE(N_NODES) + JSON_OBJECT_SIZE(1) + N_NODES*JSON_OBJECT_SIZE(2); // penjelasan: ukuran object DatagramTable adalah 1, lalu di dalamnya ada array of Datagram berukuran 4, maka tiap 4 object datagram harus ditambahkan sebagai ukuran juga, dimana tiap object datagram berukuran 2
    
    // DATAGRAMTABLE
    StaticJsonDocument<DATAGRAMTABLEDOC_SIZE> datagramTableDoc;
    deserializeJson(datagramTableDoc, datagramTableString);
    JsonObject datagramTable = datagramTableDoc.as<JsonObject>();
    // SERIALIZE AND PRINT
    serializeJson(datagramTable, Serial);
    Serial.println();

    String nodeIdString, datagramsString;
    for (JsonPair keyValue : datagramTable ) {
      nodeIdString = keyValue.key().c_str();
    }

    // DATAGRAMARRAY
    JsonArray datagrams = datagramTable[nodeIdString];    
    // SERIALIZE AND PRINT
    serializeJson(datagrams, Serial);
    Serial.println();

    // DATAGRAM
    for (int i=0; i<3; i++) {
      JsonObject datagram = datagrams[i];
      // SERIALIZE AND PRINT
      serializeJson(datagram, Serial);  
      Serial.println();
    }

    datagramTableDoc.clear();
}


void loop() {
    // insert code here    
}