#pragma once
#include "Routing.h"

const int N_NODES = 4; // for experiment purposes, the number of nodes is harcoded to only 4, this can be changed if you intend to use this library seperately

class RoutingTable {
  public:
    RoutingTable();
    RoutingTable(String);
    
    void set_nodeId(int);
    void set(RoutingTable);
    void set(String);

    void update(RoutingTable, int);
    void update(String, int);

    String get_to_string();
    void print();

    int nodeId;
    Routing routings[N_NODES];
};