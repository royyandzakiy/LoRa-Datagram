#include <Arduino.h>
#include "RoutingTable.h"

RoutingTable::RoutingTable() {
  // create empty routingTableJson
  for (int i=0; i<N_NODES; i++) {
    Routing tempRouting;

    // insert routing to array of routings
    routings[i] = tempRouting;
  }
}

RoutingTable::RoutingTable(const String _routingTableString) {
  // create empty routingTableJson
  for (int i=0; i<N_NODES; i++) {
    Routing tempRouting;

    // insert routing to array of routings
    routings[i] = tempRouting;
  }

  set(_routingTableString);
}

void RoutingTable::setNodeId(const int _nodeId) {
  nodeId = _nodeId;

  for (int i=0; i<N_NODES; i++) {
    // if position of routing is self, then default value of n is 255. this prevents storing an address to self, because this is unpresentable through the expected json that will be generated using RoutingTable::get_to_string()
    boolean self = (i==nodeId-1);
    if (self) {
      routings[i].n = 255;
      routings[i].r = 255;
    }
  }
}

int RoutingTable::getNodeId() const {
  return nodeId;
}

void RoutingTable::set(const RoutingTable& _routingTable) {
  setNodeId(_routingTable.getNodeId());
  for (int i=0; i<N_NODES; i++) {
    routings[i].set(_routingTable.routings[i]);
  }
}

void RoutingTable::set(const String routingTableString) {
  // ROUTINGTABLE SERIALIZATION
  const size_t ROUTINGTABLEDOC_SIZE = JSON_ARRAY_SIZE(N_NODES) + JSON_OBJECT_SIZE(1) + N_NODES*JSON_OBJECT_SIZE(2); // how to calculate: size of object RoutingTable is 1, then within it is an array of Routing sized 4, and each Routing object of size 2 (n, r) is added
  
  // ROUTINGTABLE
  StaticJsonDocument<ROUTINGTABLEDOC_SIZE> routingTableDoc;
  deserializeJson(routingTableDoc, routingTableString);
  JsonObject routingTableJson = routingTableDoc.as<JsonObject>();

  String nodeIdString;
  for (JsonPair keyValue : routingTableJson ) {
    nodeIdString = keyValue.key().c_str();
  }

  setNodeId(nodeIdString.toInt());

  // ROUTINGARRAY
  JsonArray routingsJson = routingTableJson[nodeIdString];

  // ROUTING
  for (int i=0; i<3; i++) {
    // insert to routings
    routings[i].set(routingsJson["n"], routingsJson["r"]);
  }

  routingTableDoc.clear();
}

void RoutingTable::update(RoutingTable _routingTable, const int _rssi) {  
  // get nodeId from sender of _routingTable, update the _rssi value
  int senderNodeId = _routingTable.nodeId;
  routings[senderNodeId-1].n = senderNodeId;
  routings[senderNodeId-1].r = _rssi;

  // UPDATE ROUTING TABLE
  // update routing table rssi values from the received Routing Table. Update except for self and sender, because rssi to self will always be 255, rssi to sender has been updated before this
  for (int i=0; i<N_NODES; i++) {
    if (_routingTable.routings[i].n != nodeId || _routingTable.routings[i].n != senderNodeId)
      routings[i].n = _routingTable.routings[i].n;
      routings[i].r = _routingTable.routings[i].r;
  }
}

void RoutingTable::update(const String _routingTableString, const int _rssi) {
  RoutingTable _routingTable(_routingTableString);
  update(_routingTable, _rssi);
}

String RoutingTable::toString() {
  String temp = "{\"" + (String) nodeId + "\":[";

  for (int i=0; i<N_NODES; i++) {
    temp += routings[i].toString();
    if (i < N_NODES-1) temp += ",";
  }

  temp += "]}";

  return temp;
}