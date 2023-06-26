#pragma once
#include "Routing.h"

const int N_NODES = 4; // for experiment purposes, the number of nodes is harcoded to only 4, this can be changed if you intend to use this library seperately

class RoutingTable {
  public:
    RoutingTable();
    RoutingTable(const String);
    
    void setNodeId(const int);
    int getNodeId() const;

    void set(const RoutingTable&);
    void set(const String);

    void update(RoutingTable, const int);
    void update(const String, const int);

    String toString();

    Routing routings[N_NODES]; // it is assumed that each NODEID is defined incrementally from 1 to N_NODES, hence it will be stored in routings[NODEID-1].n = NODEID. This redundancy is not anticipated at start, so oh well
  private:
    int nodeId;
};