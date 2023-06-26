#ifndef Routing_h
#define Routing_h

#include <Arduino.h>
#include <ArduinoJson.h>

const int N_NODES = 4;

class Routing {
  // ROUTING FORMAT (string): "nodeId,hopFrom,rssi,alertStatus,counter,counter;" (nanti ganti counter dengan datetime)
  // ROUTING FORMAT (string): "nodeId,hopFrom,rssi,alertStatus,datetimeSent,datetimeReceived;" (nanti ganti counter dengan datetime)
  // ROUTING TABLE FORMAT (array): [ routing[0], routing[1], ... }
  // ROUTING FORMAT (JSON): {"hopFrom": hopFrom, "rssi": rssi, "alertStatus": alertStatus}
  // ROUTING TABLE FORMAT (json): { "nodeId": nodeId,"routings":[routing_nodeId1, routing_nodeId2, ..., routing_nodeIdN] }  

  /*
   * Note:
   * Routing ini akan disimpan dalam sebuah RoutingTable. RoutingTable adalah sebuah
   * array of Routing yang memiliki posisi tertentu, dan dibentuk sebagai berikut
   * Routing[N_NODES], dimana N_NODES adalah jumlah maksimal NODE dalam suatu jaringan.
   * Routing sangat erat kaitannya dengan nodeId tertentu, dan secara tidak langsung
   * akan tercatat tergantung dari posisinya di Array RoutingTable.
   * 
   * Maka, jika ada RoutingTable.routings[x], x adalah nodeId dari Routing tersebut.
   * 
   * VARIABLES
   * nodeId = nodeId diri sendiri
   * hopFrom = hop/lompatan terdekat kepada suatu nodeId untuk bertemu dengan node ini
   * rssi = rssi value dari pengiriman terakhir
   * alertStatus = kondisi alarm pada node terkait, digunakan pada pendeteksian penebangan liar
   * datatime_sent = datatime routing dikirimkan oleh node ybs
   * datatime_received = datatime routing diterima nodeId ini
   */
   
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

#endif