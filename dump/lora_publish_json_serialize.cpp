#include <ArduinoJson.h>
#include "Datagram.h"

int nodeId;

void setup() {
    Serial.begin(115200);
    nodeId = 2;

    // DATAGRAMTABLE SERIALIZATION
    const size_t DATAGRAMTABLE_SIZE = JSON_ARRAY_SIZE(N_NODES) + JSON_OBJECT_SIZE(1) + 4*JSON_OBJECT_SIZE(2);
    // DATAGRAM
    StaticJsonDocument<DATAGRAMTABLE_SIZE> datagramDoc;

    datagramDoc["n"] = 2;
    datagramDoc["r"] = -76;

    // DATAGRAMARRAY
    StaticJsonDocument<DATAGRAMTABLE_SIZE> datagramsDoc;
    JsonArray datagramArray = datagramsDoc.to<JsonArray>();

    for (int i=0; i<N_NODES; i++) {
      datagramArray.add(datagramDoc);
    }

    // DATAGRAMTABLE
    StaticJsonDocument<DATAGRAMTABLE_SIZE> datagramTableDoc;
    datagramTableDoc[String(nodeId)] = datagramsDoc;

    String datagramString, datagramsString, datagramTableString;

    // serializeJson(datagramDoc, datagramString);
    // serializeJson(datagramsDoc, datagramsString);
    serializeJson(datagramTableDoc, datagramTableString);

    // Serial.println(datagramString);
    // Serial.println(datagramsString);
    Serial.println(datagramTableString);

    datagramDoc.clear();
    datagramsDoc.clear();
    datagramTableDoc.clear();
}


void loop() {
    // insert code here    
}