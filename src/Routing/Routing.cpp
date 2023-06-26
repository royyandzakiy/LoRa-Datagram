#include "Routing.h"

Routing::Routing() {
  // creates an empty Routing
  n = 0;
  r = 0;
}

void Routing::set(const int _n, const int _r) {
  n = _n;
  r = _r;
}

void Routing::set(const String _n, const String _r) {
  set(_n.toInt(), _r.toInt());
}

void Routing::set(const String routingString) {
  // parse string using json parser, then save as normal integer for each "n" and "r"
  const size_t ROUTINGDOC_SIZE = JSON_OBJECT_SIZE(2);
  StaticJsonDocument<ROUTINGDOC_SIZE> routingDoc;
  deserializeJson(routingDoc, routingString);
  JsonObject routing = routingDoc.as<JsonObject>();

  set(routing["n"].as<int>(), routing["r"].as<int>());
  routingDoc.clear();
}

void Routing::set(const Routing& _routing) {
  set(_routing.n, _routing.r);
}

Routing::Routing(const int _n, const int _r) {
  n = _n;
  r = _r;
}

Routing::Routing(const String _n, const String _r) {
  Routing(_n.toInt(), _r.toInt());
}

Routing::Routing(const String stringRouting) {
  // parser
  set(stringRouting);
}

Routing::Routing(const Routing& _routing) {
  set(_routing.n, _routing.r);
}

String Routing::toString() {
  String tempRoutingJsonString;
  tempRoutingJsonString = "{\"n\":" + (String) n + ",\"r\":" + (String) r + "}";
  
  return tempRoutingJsonString;
}

void Routing::print() {
  Serial.print(toString());
}