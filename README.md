# LoRa Network Topology - Routing Table

This project extends the implementation of [royyandzakiy/LoRa-simple-send-recv](https://github.com/royyandzakiy/LoRa-simple-send-recv), for further details, please refer directly to it

This Routing Table is a simple array of Routing, which will then be able to be printed or sent as a json object. This project DOES NOT aim to be able to forward messages, nor create new routes. It simply helps update the link strength (RSSI), to help present the whole topology of the network

### Routing Table
The Routing table is the main component here, it is based upon Routing which is a simple data structure consisting of `r` and `n`
- `n`: target node. defined as an `int`, leading to the address defined as `NODEID`
- `r`: rssi. what is the link strength from this node to the target node? [what is rssi?](https://www.sonicwall.com/support/knowledge-base/wireless-snr-rssi-and-noise-basics-of-wireless-troubleshooting/180314090744170/#:~:text=RSSI%20(Received%20Signal%20Strength%20Indicator,they%20just%20call%20it%20Signal.)