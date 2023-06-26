#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

class Routing {
  public:
    Routing();
    Routing(const Routing&);
    Routing(const int, const int);
    Routing(const String, const String);
    Routing(const String);
    void stringToJsonParser(const String, const JsonObject);
    void set(const int, const int);
    void set(const String, const String);
    void set(const String);
    void set(const Routing&);
    String toString();
    void print();
    
    int n, r;
};