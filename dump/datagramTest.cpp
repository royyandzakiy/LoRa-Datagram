#include <Arduino.h>
#include "DatagramTable.h"

void setup() {
  Serial.begin(115200);
  while (!Serial);

  DatagramTable tempDatagramTable(0); // ukuran array of Datagram sudah di declare pada class

  /*// masukkan dummy data
  // String tempDatagramString = "nodeId,hopFrom,rssi,alertStatus,counter,counter;";
  Datagram tempDatagram(tempDatagramString);
  for (int i=0; i<N_NODES; i++) tempDatagramTable.datagrams[i] = tempDatagram;//*/

  // masukkan dummy data
  DatagramTable tempDatagramTable1(1);
  
  String tempDatagramString1 = "1,0,0,0,0,0;";
  String tempDatagramString2 = "1,2,-60,0,0,0;";
  String tempDatagramString3 = "1,2,0,0,0,0;";

  Datagram tempDatagram;
  tempDatagram.set_from_string(tempDatagramString1);
  tempDatagramTable1.datagrams[0] = tempDatagram;
  tempDatagram.set_from_string(tempDatagramString2);
  tempDatagramTable1.datagrams[1] = tempDatagram;
  tempDatagram.set_from_string(tempDatagramString3);
  tempDatagramTable1.datagrams[2] = tempDatagram;

  // debug: print datagramTable
  tempDatagramTable.print();

  Serial.println("datagram node 1");
  tempDatagramTable1.print();

  // masuk data baru
  // tempDatagramTable.update(tempDatagramTable1, "-68");
  tempDatagramTable.copy(tempDatagramTable1);
  
  Serial.println("datagram node 2: updated state");
  tempDatagramTable.print();
}

void loop() {
}