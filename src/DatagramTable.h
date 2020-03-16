#ifndef DatagramTable_h
#define DatagramTable_h

#include "Datagram.h"

// CLASS DATAGRAM TABLE
class DatagramTable {
  public:
    DatagramTable();
    DatagramTable(String);
    
    void nodeId_set(int);
    void set(DatagramTable);
    void set(String);

    void update(DatagramTable, int);
    void print();
    String get_to_string();

    int nodeId;
    Datagram datagrams[N_NODES];
};

#endif