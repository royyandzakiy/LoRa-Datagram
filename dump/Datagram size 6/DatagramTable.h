#ifndef DatagramTable_h
#define DatagramTable_h

#include "Datagram.h"

// CLASS DATAGRAM TABLE
class DatagramTable {
  public:
    DatagramTable(int);
    Datagram datagrams[N_NODES];
    
    void copy(DatagramTable);
    void update(DatagramTable, String);
    void print();
    String get_to_string();

    String nodeId;
};

#endif