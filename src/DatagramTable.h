#ifndef DatagramTable_h
#define DatagramTable_h

#include "Datagram.h"

// CLASS DATAGRAM TABLE
class DatagramTable {
  public:
    DatagramTable(int);
    Datagram datagrams[N_NODES];
    
    void copy(DatagramTable);
    void update(DatagramTable, int);
    void print();
    String get_to_string();

    int nodeId;
};

#endif