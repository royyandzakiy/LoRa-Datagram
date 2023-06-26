#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class Routing {
  public:
    Routing();
    Routing(int, int);
    Routing(String, String);
    Routing(String);
    void stringToJsonParser(String, JsonObject);
    void set(int, int);
    void set(String, String);
    void set(String);
    void set_from_string(String);
    String get_to_string();
    void print_to_string();
    
    int n, r;
};