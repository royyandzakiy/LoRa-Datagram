#include "Routing.h"

Routing::Routing() {
  // creates an empty Routing
  n = 0;
  r = 0;
}

void Routing::set(int _n, int _r) {
  n = _n;
  r = _r;
}

void Routing::set(String _n, String _r) {
  set(_n.toInt(), _r.toInt());
}

void Routing::set(String routingString) {
  // parse string using json parser, then save as normal integer for each "n" and "r"
  const size_t ROUTINGDOC_SIZE = JSON_OBJECT_SIZE(2);
  StaticJsonDocument<ROUTINGDOC_SIZE> routingDoc;
  deserializeJson(routingDoc, routingString);
  JsonObject routing = routingDoc.as<JsonObject>();

  set(routing["n"].as<int>(), routing["r"].as<int>());
  routingDoc.clear();
}

Routing::Routing(int _n, int _r) {
  n = _n;
  r = _r;
}

Routing::Routing(String _n, String _r) {
  Routing(_n.toInt(), _r.toInt());
}

Routing::Routing(String stringRouting) {
  // parser
  set(stringRouting);
}

String Routing::get_to_string() {
  String tempRoutingJsonString;
  tempRoutingJsonString = "{\"n\":" + (String) n + ",\"r\":" + (String) r + "}";
  
  return tempRoutingJsonString;
}

void Routing::print_to_string() {
  Serial.print(get_to_string());
}