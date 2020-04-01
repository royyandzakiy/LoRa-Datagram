#ifndef DatagramTable_h
#define DatagramTable_h

#include "Datagram.h"

// CLASS DATAGRAM TABLE
class DatagramTable {
  public:
    DatagramTable();
    DatagramTable(String);
    
    void set_nodeId(int);
    void set(DatagramTable);
    void set(String);

    void update(DatagramTable, int);
    void update(String, int);

    String get_to_string();
    void print();

    int nodeId;
    Datagram datagrams[N_NODES];
};
#endif