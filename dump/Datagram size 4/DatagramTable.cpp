<<<<<<< HEAD
<<<<<<<< HEAD:dump/Datagram size 4/DatagramTable.cpp
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
  DynamicJsonDocument doc(10000);

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

void DatagramTable::update(String _datagramTableString, int _rssi) {
  // // UNDER MAINTENANCE!
  // // Masih dalam perbaikan
  // DatagramTable _datagramTable(_datagramTableString);
  // int nodeIdSender = _datagramTable.nodeId;

  // // update diagramTable antara self dengan nodeId pengirim
  // datagrams[nodeIdSender-1].nodeId = nodeIdSender;
  // datagrams[nodeIdSender-1].hopFrom = nodeIdSender;
  // datagrams[nodeIdSender-1].rssi = _rssi;

  // // iterasi table datagram, ubah hop  
  // for (int i=0; i<N_NODES; i++) {
  //   boolean self = (i==(nodeId-1));
  //   if (!self) // memastikan bagian self tidak diubah
  //     if (_datagramTable.datagrams[i].hopFrom != 0) // memeriksa jika ada bagian yang hop-nya masih kosong. artinya, jika data yang tersimpan tidak pernah berasal langsung dari node-nya sendiri
  //       if (_datagramTable.datagrams[i].hopFrom != nodeId) // memeriksa jika hop berasal dari diri sendiri, jika benar maka tidak perlu update
  //         datagrams[i].hopFrom = nodeIdSender;
  // }
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
========
=======
>>>>>>> 3d7d75f89c2beee80f9d764a17fff7fa6d6c6910
#include <Arduino.h>
#include "DatagramTable.h"

DatagramTable::DatagramTable() {
<<<<<<< HEAD
  // membuat empty datagramTableJson
=======
  // membuat empty datagramTable
>>>>>>> 3d7d75f89c2beee80f9d764a17fff7fa6d6c6910
  for (int i=0; i<N_NODES; i++) {
    Datagram tempDatagram;

    // masukkan datagram ke array of datagrams
    datagrams[i] = tempDatagram;
  }
}

<<<<<<< HEAD
void DatagramTable::set_nodeId(int _nodeId) {
  nodeId = _nodeId;

  for (int i=0; i<N_NODES; i++) {
    // jika posisi datagram ada pada self, maka value default dari n adalah 255
    boolean self = (i==nodeId-1);
    if (self) {
      datagrams[i].n = 255;
      datagrams[i].r = 255;
=======
void DatagramTable::nodeId_set(int _nodeId) {
  nodeId = _nodeId;

  for (int i=0; i<N_NODES; i++) {
    // jika posisi datagram ada pada self, maka value default dari hopFrom adalah 255
    boolean self = (i==nodeId-1);
    if (self) {
      datagrams[i].nodeId = nodeId;
      datagrams[i].hopFrom = 255;
      datagrams[i].rssi = 255;
>>>>>>> 3d7d75f89c2beee80f9d764a17fff7fa6d6c6910
    }
  }
}

<<<<<<< HEAD
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
=======
DatagramTable::DatagramTable(String stringDatagramTable) {
  // ubah jadi json dengan parser
  DynamicJsonDocument doc(10000);

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

void DatagramTable::update(String _datagramTableString, int _rssi) {
  // // UNDER MAINTENANCE!
  // // Masih dalam perbaikan
  // DatagramTable _datagramTable(_datagramTableString);
  // int nodeIdSender = _datagramTable.nodeId;

  // // update diagramTable antara self dengan nodeId pengirim
  // datagrams[nodeIdSender-1].nodeId = nodeIdSender;
  // datagrams[nodeIdSender-1].hopFrom = nodeIdSender;
  // datagrams[nodeIdSender-1].rssi = _rssi;

  // // iterasi table datagram, ubah hop  
  // for (int i=0; i<N_NODES; i++) {
  //   boolean self = (i==(nodeId-1));
  //   if (!self) // memastikan bagian self tidak diubah
  //     if (_datagramTable.datagrams[i].hopFrom != 0) // memeriksa jika ada bagian yang hop-nya masih kosong. artinya, jika data yang tersimpan tidak pernah berasal langsung dari node-nya sendiri
  //       if (_datagramTable.datagrams[i].hopFrom != nodeId) // memeriksa jika hop berasal dari diri sendiri, jika benar maka tidak perlu update
  //         datagrams[i].hopFrom = nodeIdSender;
  // }
}

String DatagramTable::get_to_string() {
  String temp = "{\"nodeId\":" + (String) nodeId + ",\"datagrams\":[";
>>>>>>> 3d7d75f89c2beee80f9d764a17fff7fa6d6c6910

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
<<<<<<< HEAD
>>>>>>>> 3d7d75f89c2beee80f9d764a17fff7fa6d6c6910:src/DatagramTable.cpp
=======
>>>>>>> 3d7d75f89c2beee80f9d764a17fff7fa6d6c6910
