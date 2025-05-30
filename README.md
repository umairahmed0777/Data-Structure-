# Distributed Hash Table (DHT) in C++

This project is a simulation of a **Distributed Hash Table (DHT)** in C++, demonstrating how consistent hashing, routing tables, and B-trees can be used to store and manage data in a decentralized manner.

## 🔧 Features

- Circular DHT with machine join/leave functionality
- Consistent hashing for machine and key distribution
- Routing table (finger table) per machine
- B-tree for key-value storage on each machine
- Data insertion, lookup, and deletion
- Console-based menu-driven interface

## 📁 Files

- `main.cpp`: Full implementation of machine ring, routing table, B-tree, and menu
- Uses only Standard Template Library (STL) and basic C++ components

## ▶️ How to Run

### Compile:
```bash
g++ -o dht_simulation 39685a17-ef09-4cf4-a7eb-978c5114bd21.cpp
