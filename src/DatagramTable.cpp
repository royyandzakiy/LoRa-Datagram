#include <Arduino.h>
#include "DatagramTable.h"

DatagramTable::DatagramTable() {
  // membuat empty datagramTableJson
  for (int i=0; i<N_NODES; i++) {
    Datagram tempDatagram;

    // masukkan datagram ke array of datagrams
    datagrams[i] = tempDatagram;
  }
}

void DatagramTable::set_nodeId(int _nodeId) {
  nodeId = _nodeId;

  for (int i=0; i<N_NODES; i++) {
    // jika posisi datagram ada pada self, maka value default dari n adalah 255
    boolean self = (i==nodeId-1);
    if (self) {
      datagrams[i].n = 255;
      datagrams[i].r = 255;
    }
  }
}

void DatagramTable::set(DatagramTable senderDatagramTable) {
  set_nodeId(senderDatagramTable.nodeId);
  for (int i=0; i<N_NODES; i++) {
    datagrams[i].set_from_string(senderDatagramTable.datagrams[i].get_to_string());
  }
}

void DatagramTable::set(String datagramTableString) {
  // DATAGRAMTABLE SERIALIZATION
  const size_t DATAGRAMTABLEDOC_SIZE = JSON_ARRAY_SIZE(N_NODES) + JSON_OBJECT_SIZE(1) + N_NODES*JSON_OBJECT_SIZE(2); // penjelasan: ukuran object DatagramTable adalah 1, lalu di dalamnya ada array of Datagram berukuran 4, maka tiap 4 object datagram harus ditambahkan sebagai ukuran juga, dimana tiap object datagram berukuran 2
  
  // DATAGRAMTABLE
  StaticJsonDocument<DATAGRAMTABLEDOC_SIZE> datagramTableDoc;
  deserializeJson(datagramTableDoc, datagramTableString);
  JsonObject datagramTableJson = datagramTableDoc.as<JsonObject>();

  String nodeIdString;
  for (JsonPair keyValue : datagramTableJson ) {
    nodeIdString = keyValue.key().c_str();
  }

  set_nodeId(nodeIdString.toInt());

  // DATAGRAMARRAY
  JsonArray datagramsJson = datagramTableJson[nodeIdString];

  // DATAGRAM
  for (int i=0; i<3; i++) {
    // insert to datagrams
    datagrams[i].set(datagramsJson["n"], datagramsJson["r"]);
  }

  datagramTableDoc.clear();
}

DatagramTable::DatagramTable(String datagramTableString) {
  set(datagramTableString);
}

void DatagramTable::update(DatagramTable senderDatagramTable, int _r) {  
  // get tempDatagramTable.nodeId
  // set new rssi value
  int senderNodeId = senderDatagramTable.nodeId;

  // UPDATE RSSI
  // update datagram nodeId pada datagramTable sesuai dengan rssi baru
  datagrams[senderNodeId-1].n = senderNodeId;
  datagrams[senderNodeId-1].r = _r;

  // UPDATE HOP
  // iterasi table datagram, ubah hop (n)
  for (int i=0; i<N_NODES; i++) {
    boolean self = (i==(nodeId-1));
    boolean sender = (i==(senderNodeId-1));
    if (!self && !sender) // memastikan bagian self dan sender tidak diubah. nilai n pada self adalah 255, dan n pada sender adalah 255, yaitu nilai default yg dianggap tidak terjangkau.
      if (senderDatagramTable.datagrams[i].n != 0) // memastikan hop pada datagramTable sender tidak kosong. Jika kosong, artinya sender tidak terkoneksi ke node terkait, maka abaikan saja.
        if (senderDatagramTable.datagrams[i].n != nodeId) // memastikan hop pada datagramTable sender tidak berasal dari self, jika benar maka tidak perlu update karena nanti jadi redundan. Artinya self sudah pernah terhubung dengan node terkait, dan bahkan sudah menjadi hopping bagi sender.
          datagrams[i].n = senderNodeId;
  }
}

void DatagramTable::update(String senderDatagramTableString, int _r) {
  DatagramTable senderDatagramTable;
  senderDatagramTable.set(senderDatagramTableString);
  update(senderDatagramTable, _r);
}

String DatagramTable::get_to_string() {
  String temp = "{\"" + (String) nodeId + "\":[";

  for (int i=0; i<N_NODES; i++) {
    temp += datagrams[i].get_to_string();
    if (i < N_NODES-1) temp += ",";
  }

  temp += "]}";

  return temp;
}

void DatagramTable::print() {
  Serial.print(get_to_string());
}
