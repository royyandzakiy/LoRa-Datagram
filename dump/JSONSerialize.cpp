#include <ArduinoJson.h>

int hopFrom, rssi, alertStatus;

void isi(JsonObject objOut) {
    objOut["hopFrom"] = 12;
    objOut["rssi"] = 12;
    objOut["alertStatus"] = 12;
}

void setup() {
    Serial.begin(115200);

    // Serialize
    // gimana cara isi json object
    DynamicJsonDocument docOut(1024);
    JsonObject obj = docOut.to<JsonObject>(); // obj menjadi reference yg bisa diisi dari luar
    isi(obj);

    String tempDatagram;
    serializeJson(docOut, tempDatagram);

    Serial.println(tempDatagram);
}

void loop() {
    // insert code here
    
}