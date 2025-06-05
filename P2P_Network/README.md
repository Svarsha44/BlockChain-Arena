Block-chain Arena SoC project

Task 1 :  P2P Network Simulation

Name : Varsha Seemala  
Roll Number : 23B0964

## Description

Here we have an implementation of a basic P2P network generator in C++. NetworkX, and Matplotlib are used for visualization.
Details about the network :
- has between 50 to 100 nodes
- Each node has degree between 3 and 6
- The network is fully connected

Instruction to run :

To get the adjacency list of the network: (adjList.txt)
 g++ -o out p2p.cpp
 ./out

To visualize the network : (network.png)
 python3 pycode.py
