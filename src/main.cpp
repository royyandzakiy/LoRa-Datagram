#include <ArduinoJson.h>

int hopFrom, rssi, alertStatus;

void isi(JsonObject objOut) {
    objOut["hopFrom"] = 12;
    objOut["rssi"] = 12;
    objOut["alertStatus"] = 12;
}

void setup() {
    Serial.begin(115200);

    // insert code here
    // DynamicJsonDocument doc(1024);

    // // Deserialize
    // String input =
    //     "{\"hopFrom\":1,\"rssi\":-68,\"alertStatus\":0}";
    // deserializeJson(doc, input);
    // JsonObject obj = doc.as<JsonObject>();

    // hopFrom = obj["hopFrom"];
    // rssi = obj["rssi"];
    // alertStatus = obj["alertStatus"];

    // String tempDatagram;
    // serializeJson(doc, tempDatagram);

    // Serial.println(tempDatagram);

    // Serialize
    // gimana cara copy json object
    DynamicJsonDocument docOut(1024);
    JsonObject obj = docOut.to<JsonObject>();
    isi(obj);

    String tempDatagram;
    serializeJson(docOut, tempDatagram);

    Serial.println(tempDatagram);
}

void loop() {
    // insert code here
    
}