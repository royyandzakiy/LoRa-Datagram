# LoRa Routing Table

This project extends the implementation of [royyandzakiy/LoRa-simple-send-recv](https://github.com/royyandzakiy/LoRa-simple-send-recv), for further details, please refer directly to it

### Routing Table
The Routing table is the main component here, it is based upon Routing which is a simple data structure consisting of `r` and `n`
- `r`: target route. defined as an `int`, leading to the address defined as `NODEID`
- `n`: nearest path. what is the closest node to hop onto, to be able to reach the final target route?