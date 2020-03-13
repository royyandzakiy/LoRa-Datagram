#include <Arduino.h>
#include "DatagramTable.h"

DatagramTable::DatagramTable(int _nodeId) {
  nodeId = (String) _nodeId;
  
  for (int i=0; i<N_NODES; i++) {
    Datagram tempDatagram;
    tempDatagram.nodeId = nodeId;

    // jika posisi datagram ada pada self, maka value default dari hopFrom adalah 255
    boolean self = (i==nodeId.toInt()-1);
    if (self) tempDatagram.hopFrom = (String) 255;

    // masukkan datagram ke array of datagrams
    datagrams[i] = tempDatagram;
  }
}

void DatagramTable::copy(DatagramTable _datagramTable) {
  for (int i=0; i<N_NODES; i++) {
    datagrams[i].set_from_string(_datagramTable.datagrams[i].get_to_string());
  }
}

void DatagramTable::update(DatagramTable _datagramTable, String _rssi) {
  int nodeIdSender = _datagramTable.nodeId.toInt();

  // update diagramTable antara self dengan nodeId pengirim
  datagrams[nodeIdSender-1].hopFrom = nodeIdSender;
  datagrams[nodeIdSender-1].rssi = _rssi;

  // iterasi table datagram, ubah hop  
  for (int i=0; i<N_NODES; i++) {
    boolean self = (i==(nodeId.toInt()-1));
    if (!self) // memastikan bagian self tidak diubah
      if (_datagramTable.datagrams[i].hopFrom != "0") // memeriksa jika ada bagian yang hop-nya masih kosong
        if (_datagramTable.datagrams[i].hopFrom != (String) nodeId) // memeriksa jika hop berasal dari diri sendiri, jika benar maka tidak perlu update
          datagrams[i].hopFrom = nodeIdSender;
  }
}

void DatagramTable::print() {
  for (int i=0; i<N_NODES; i++) {
    Serial.print((String) (i+1) + ": ");
    Serial.println(datagrams[i].get_to_string());
  }
}

String DatagramTable::get_to_string() {
  String temp = "";

  for (int i=0; i<N_NODES; i++) {
    temp += datagrams[i].get_to_string();
  }

  return temp;
}