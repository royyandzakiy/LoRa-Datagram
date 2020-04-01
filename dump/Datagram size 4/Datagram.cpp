#include "Datagram.h"

Datagram::Datagram() {
  // creates an empty Datagram
  n = 0;
  r = 0;
}

void Datagram::set(int _n, int _r) {
  n = _n;
  r = _r;
}

void Datagram::set(String _n, String _r) {
  set(_n.toInt(), _r.toInt());
}

void Datagram::set(String datagramString) {
  // parser
  const size_t DATAGRAMDOC_SIZE = JSON_OBJECT_SIZE(2);
  StaticJsonDocument<DATAGRAMDOC_SIZE> datagramDoc;
  deserializeJson(datagramDoc, datagramString);
  JsonObject datagram = datagramDoc.as<JsonObject>();

  set(datagram["n"].as<int>(), datagram["r"].as<int>());
  datagramDoc.clear();
}

Datagram::Datagram(int _n, int _r) {
  n = _n;
  r = _r;
}

Datagram::Datagram(String _n, String _r) {
  Datagram(_n.toInt(), _r.toInt());
}

Datagram::Datagram(String stringDatagram) {
  // parser
  set(stringDatagram);
}

String Datagram::get_to_string() {
  String tempDatagramJsonString;
  tempDatagramJsonString = "{\"n\":" + (String) n + ",\"r\":" + (String) r + "}";
  
  return tempDatagramJsonString;
}

void Datagram::print_to_string() {
  Serial.print(get_to_string());
}