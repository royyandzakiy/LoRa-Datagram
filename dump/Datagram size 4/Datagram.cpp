#include "Datagram.h"

Datagram::Datagram() {
  // creates an empty Datagram
  nodeId = 0;
  hopFrom = 0;
  rssi = 0;
  alertStatus = 0;
}

void Datagram::set_from_string(String stringDatagram) {
  // parser
  DynamicJsonDocument doc(1024);

  deserializeJson(doc, stringDatagram);
  JsonObject obj = doc.to<JsonObject>();

  nodeId = obj["nodeId"];
  hopFrom = obj["hopFrom"];
  rssi = obj["rssi"];
  alertStatus = obj["alertStatus"];

  obj.clear();
}

Datagram::Datagram(int _nodeId, int _hopFrom, int _rssi, int _alertStatus) {
  nodeId = _nodeId;
  hopFrom = _hopFrom;
  rssi = _rssi;
  alertStatus = _alertStatus;
}

Datagram::Datagram(String _nodeId, String _hopFrom, String _rssi, String _alertStatus) {
  Datagram(_nodeId.toInt(), _hopFrom.toInt(), _rssi.toInt(), _alertStatus.toInt());
}

Datagram::Datagram(String stringDatagram) {
  // parser
  set_from_string(stringDatagram);
}

void Datagram::set(int _nodeId, int _hopFrom, int _rssi, int _alertStatus) {
  nodeId = _nodeId;
  hopFrom = _hopFrom;
  rssi = _rssi;
  alertStatus = _alertStatus;
}

void Datagram::set(String _nodeId, String _hopFrom, String _rssi, String _alertStatus) {
  set(_nodeId.toInt(), _hopFrom.toInt(), _rssi.toInt(), _alertStatus.toInt());
}

void Datagram::set(String stringDatagram) {
  // parser
  set_from_string(stringDatagram);
}

String Datagram::get_to_string() {
  String tempDatagramJsonString;
  tempDatagramJsonString = "{\"nodeId\":" + (String) nodeId + ",\"hopFrom\":" + (String) hopFrom + ",\"rssi\":" + (String) rssi + ",\"alertStatus\":" + (String) alertStatus + "}";
  
  return tempDatagramJsonString;
}

void Datagram::print_to_string() {
  Serial.print(get_to_string());
}