#include <Arduino.h>
#include "RoutingTable.h"

RoutingTable::RoutingTable() {
  // membuat empty routingTableJson
  for (int i=0; i<N_NODES; i++) {
    Routing tempRouting;

    // masukkan routing ke array of routings
    routings[i] = tempRouting;
  }
}

void RoutingTable::set_nodeId(int _nodeId) {
  nodeId = _nodeId;

  for (int i=0; i<N_NODES; i++) {
    // jika posisi routing ada pada self, maka value default dari n adalah 255
    boolean self = (i==nodeId-1);
    if (self) {
      routings[i].n = 255;
      routings[i].r = 255;
    }
  }
}

void RoutingTable::set(RoutingTable senderRoutingTable) {
  set_nodeId(senderRoutingTable.nodeId);
  for (int i=0; i<N_NODES; i++) {
    routings[i].set_from_string(senderRoutingTable.routings[i].get_to_string());
  }
}

void RoutingTable::set(String routingTableString) {
  // ROUTINGTABLE SERIALIZATION
  const size_t ROUTINGTABLEDOC_SIZE = JSON_ARRAY_SIZE(N_NODES) + JSON_OBJECT_SIZE(1) + N_NODES*JSON_OBJECT_SIZE(2); // penjelasan: ukuran object RoutingTable adalah 1, lalu di dalamnya ada array of Routing berukuran 4, maka tiap 4 object routing harus ditambahkan sebagai ukuran juga, dimana tiap object routing berukuran 2
  
  // ROUTINGTABLE
  StaticJsonDocument<ROUTINGTABLEDOC_SIZE> routingTableDoc;
  deserializeJson(routingTableDoc, routingTableString);
  JsonObject routingTableJson = routingTableDoc.as<JsonObject>();

  String nodeIdString;
  for (JsonPair keyValue : routingTableJson ) {
    nodeIdString = keyValue.key().c_str();
  }

  set_nodeId(nodeIdString.toInt());

  // ROUTINGARRAY
  JsonArray routingsJson = routingTableJson[nodeIdString];

  // ROUTING
  for (int i=0; i<3; i++) {
    // insert to routings
    routings[i].set(routingsJson["n"], routingsJson["r"]);
  }

  routingTableDoc.clear();
}

RoutingTable::RoutingTable(String routingTableString) {
  set(routingTableString);
}

void RoutingTable::update(RoutingTable senderRoutingTable, int _r) {  
  // get tempRoutingTable.nodeId
  // set new rssi value
  int senderNodeId = senderRoutingTable.nodeId;

  // UPDATE RSSI
  // update routing nodeId pada routingTable sesuai dengan rssi baru
  routings[senderNodeId-1].n = senderNodeId;
  routings[senderNodeId-1].r = _r;

  // UPDATE HOP
  // iterasi table routing, ubah hop (n)
  for (int i=0; i<N_NODES; i++) {
    boolean self = (i==(nodeId-1));
    boolean sender = (i==(senderNodeId-1));
    if (!self && !sender) // memastikan bagian self dan sender tidak diubah. nilai n pada self adalah 255, dan n pada sender adalah 255, yaitu nilai default yg dianggap tidak terjangkau.
      if (senderRoutingTable.routings[i].n != 0) // memastikan hop pada routingTable sender tidak kosong. Jika kosong, artinya sender tidak terkoneksi ke node terkait, maka abaikan saja.
        if (senderRoutingTable.routings[i].n != nodeId) // memastikan hop pada routingTable sender tidak berasal dari self, jika benar maka tidak perlu update karena nanti jadi redundan. Artinya self sudah pernah terhubung dengan node terkait, dan bahkan sudah menjadi hopping bagi sender.
          routings[i].n = senderNodeId;
  }
}

void RoutingTable::update(String senderRoutingTableString, int _r) {
  RoutingTable senderRoutingTable;
  senderRoutingTable.set(senderRoutingTableString);
  update(senderRoutingTable, _r);
}

String RoutingTable::get_to_string() {
  String temp = "{\"" + (String) nodeId + "\":[";

  for (int i=0; i<N_NODES; i++) {
    temp += routings[i].get_to_string();
    if (i < N_NODES-1) temp += ",";
  }

  temp += "]}";

  return temp;
}

void RoutingTable::print() {
  Serial.print(get_to_string());
}