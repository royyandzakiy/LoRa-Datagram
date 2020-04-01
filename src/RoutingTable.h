#ifndef RoutingTable_h
#define RoutingTable_h

#include "Routing.h"

// CLASS ROUTING TABLE
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

#endif