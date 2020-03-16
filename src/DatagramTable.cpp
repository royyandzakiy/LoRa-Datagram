#include <Arduino.h>
#include "DatagramTable.h"

DatagramTable::DatagramTable() {
  // membuat empty datagramTable
  for (int i=0; i<N_NODES; i++) {
    Datagram tempDatagram;

    // masukkan datagram ke array of datagrams
    datagrams[i] = tempDatagram;
  }
}

void DatagramTable::nodeId_set(int _nodeId) {
  nodeId = _nodeId;

  for (int i=0; i<N_NODES; i++) {
    // jika posisi datagram ada pada self, maka value default dari hopFrom adalah 255
    boolean self = (i==nodeId-1);
    if (self) {
      datagrams[i].nodeId = nodeId;
      datagrams[i].hopFrom = 255;
      datagrams[i].rssi = 255;
    }
  }
}

DatagramTable::DatagramTable(String stringDatagramTable) {
  // ubah jadi json dengan parser
  DynamicJsonDocument doc(1024);

  deserializeJson(doc, stringDatagramTable);
  JsonObject obj = doc.as<JsonObject>();

  nodeId = obj["nodeId"];

  // array of jsonDocuments berupa datagram di iterasi untuk di build  
  for (int i=0; i<N_NODES; i++) {
    String tempStringDatagram = obj["datagrams"][i];
    datagrams[i].set(tempStringDatagram);
  }

  obj.clear();
}

void DatagramTable::set(DatagramTable _datagramTable) {
  for (int i=0; i<N_NODES; i++) {
    datagrams[i].set_from_string(_datagramTable.datagrams[i].get_to_string());
  }
}

void DatagramTable::set(String stringDatagramTable) {
  // ubah jadi json dengan parser
  DynamicJsonDocument doc(1024);

  deserializeJson(doc, stringDatagramTable);
  JsonObject obj = doc.as<JsonObject>();

  nodeId = obj["nodeId"];
  
  // array of jsonDocuments berupa datagram di iterasi untuk di build  
  for (int i=0; i<N_NODES; i++) {
    String tempStringDatagram = obj["datagrams"][i];
    datagrams[i].set(tempStringDatagram);
  }

  obj.clear();
}

void DatagramTable::update(DatagramTable _datagramTable, int _rssi) {
  // UNDER MAINTENANCE!
  // Masih dalam perbaikan
  int nodeIdSender = _datagramTable.nodeId;

  // update diagramTable antara self dengan nodeId pengirim
  datagrams[nodeIdSender-1].nodeId = nodeIdSender;
  datagrams[nodeIdSender-1].hopFrom = nodeIdSender;
  datagrams[nodeIdSender-1].rssi = _rssi;

  // iterasi table datagram, ubah hop  
  for (int i=0; i<N_NODES; i++) {
    boolean self = (i==(nodeId-1));
    if (!self) // memastikan bagian self tidak diubah
      if (_datagramTable.datagrams[i].hopFrom != 0) // memeriksa jika ada bagian yang hop-nya masih kosong. artinya, jika data yang tersimpan tidak pernah berasal langsung dari node-nya sendiri
        if (_datagramTable.datagrams[i].hopFrom != nodeId) // memeriksa jika hop berasal dari diri sendiri, jika benar maka tidak perlu update
          datagrams[i].hopFrom = nodeIdSender;
  }
}

String DatagramTable::get_to_string() {
  String temp = "{\"nodeId\":" + (String) nodeId + ",\"datagrams\":[";

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
