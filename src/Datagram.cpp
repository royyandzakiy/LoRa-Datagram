#include "Datagram.h"

Datagram::Datagram() {
  // creates an empty Datagram
  hopFrom = 0;
  rssi = 0;
  alertStatus = 0;
}

void Datagram::stringToJsonParser(String stringToParse, JsonObject outputJson) {
  // parser
  DynamicJsonDocument doc(1024);

  deserializeJson(doc, stringToParse);
  JsonObject obj = doc.to<JsonObject>();

  outputJson["hopFrom"] = obj["hopFrom"];
  outputJson["rssi"] = obj["rssi"];
  outputJson["alertStatus"] = obj["alertStatus"];
}

Datagram::Datagram(int _hopFrom, int _rssi, int _alertStatus) {
  hopFrom = _hopFrom;
  rssi = _rssi;
  alertStatus = _alertStatus;
}

Datagram::Datagram(String _hopFrom, String _rssi, String _alertStatus) {
  Datagram(_hopFrom.toInt(), _rssi.toInt(), _alertStatus.toInt());
}

Datagram::Datagram(String stringToParse) {
  // parser
  DynamicJsonDocument doc(1024);
  JsonObject obj = doc.to<JsonObject>();

  stringToJsonParser(stringToParse, obj);

  Datagram(obj["hopFrom"], obj["rssi"], obj["alertStatus"]);
}

void Datagram::set(int _hopFrom, int _rssi, int _alertStatus) {
  hopFrom = _hopFrom;
  rssi = _rssi;
  alertStatus = _alertStatus;
}

void Datagram::set(String _hopFrom, String _rssi, String _alertStatus) {
  set(_hopFrom.toInt(), _rssi.toInt(), _alertStatus.toInt());
}

void Datagram::set_from_string(String stringToParse) {
  // parser
  DynamicJsonDocument doc(1024);
  JsonObject obj = doc.to<JsonObject>();

  stringToJsonParser(stringToParse, obj);

  Datagram(obj["hopFrom"], obj["rssi"], obj["alertStatus"]);
}

String Datagram::get_to_string() {
  String tempDatagramString;
  tempDatagramString = "{\"hopFrom\":" + (String) hopFrom + ",\"rssi\":" + (String) rssi + ",\"alertStatus\":" + (String) alertStatus + "}";
  
  return tempDatagramString;
}

void Datagram::print_to_string() {
  Serial.print(get_to_string());
}