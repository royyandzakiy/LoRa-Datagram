#include <Arduino.h>
#include "Datagram.h"

Datagram::Datagram() {
  // creates an empty Datagram
  nodeId = "0";
  hopFrom = "0";
  rssi = "0";
  alertStatus = "0";
  datetimeSent = "0";
  datetimeReceived = "0";
}

// an intermediary function
void Datagram::stringToStringArrayParser(String stringToParse, String outputStringArray[]) {
  // parser
  int tempStart = 0;
  int tempEnd = 0;
  for (int i=0; i<DATAGRAM_SIZE; i++) {
    if (i<DATAGRAM_SIZE-1) tempEnd = stringToParse.indexOf(',', tempStart+1);
    else tempEnd = stringToParse.indexOf(';');

    // adding to string array
    outputStringArray[i] = stringToParse.substring(tempStart, tempEnd);

    tempStart = tempEnd + 1;
  }
}

Datagram::Datagram(String _nodeId, String _hopFrom, String _rssi, String _alertStatus, String _datetimeSent, String _datetimeReceived) {
  nodeId = _nodeId;
  hopFrom = _hopFrom;
  rssi = _rssi;
  alertStatus = _alertStatus;
  datetimeSent = _datetimeSent;
  datetimeReceived = _datetimeReceived;
}

Datagram::Datagram(String stringToParse) {
  // DATAGRAM FORMAT (string): "hopFrom,rssi,alertStatus,datetimeSent,datetimeReceived;"
  // parser
  String tempStringArray[DATAGRAM_SIZE];
  stringToStringArrayParser(stringToParse, tempStringArray);

  nodeId = tempStringArray[0];
  hopFrom = tempStringArray[1];
  rssi = tempStringArray[2];
  alertStatus = tempStringArray[3];
  datetimeSent = tempStringArray[4];
  datetimeReceived = tempStringArray[5];
}

void Datagram::set(String _nodeId, String _hopFrom, String _rssi, String _alertStatus, String _datetimeSent, String _datetimeReceived) {
  nodeId = _nodeId;
  hopFrom = _hopFrom;
  rssi = _rssi;
  alertStatus = _alertStatus;
  datetimeSent = _datetimeSent;
  datetimeReceived = _datetimeReceived;
}

void Datagram::set_from_string(String stringToParse) {
  // DATAGRAM FORMAT (string): "hopFrom,rssi,alertStatus,datetimeSent,datetimeReceived;"
  // parser
  String tempStringArray[DATAGRAM_SIZE];
  stringToStringArrayParser(stringToParse, tempStringArray);

  set(tempStringArray[0], tempStringArray[1], tempStringArray[2], tempStringArray[3], tempStringArray[4], tempStringArray[5]);
}

String Datagram::get_to_string() {
  String tempDatagramString;
  tempDatagramString = nodeId + "," + hopFrom + "," + rssi + "," + alertStatus + "," + datetimeSent + "," + datetimeReceived + ";";
  
  return tempDatagramString;
}

void Datagram::print_to_string() {
  Serial.print(nodeId);
  Serial.print(",");
  Serial.print(hopFrom);
  Serial.print(",");
  Serial.print(rssi);
  Serial.print(",");
  Serial.print(alertStatus);
  Serial.print(",");
  Serial.print(datetimeSent);
  Serial.print(",");
  Serial.print(datetimeReceived);
  Serial.print(";");
}