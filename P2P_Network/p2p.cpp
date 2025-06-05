#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <random>
#include <ctime>
#include <algorithm>
#include <queue>

using namespace std;

const int MIN_PEERS = 50;
const int MAX_PEERS = 100;
const int MIN_DEGREE = 3;
const int MAX_DEGREE = 6;

class P2PNetwork {
private:
    int num_nodes;
    vector<set<int>> adj;

    bool checkConnectivity() {
        vector<bool> visited(num_nodes, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;

        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int neighbour : adj[node]) {
                if (!visited[neighbour]) {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }

        for (bool it : visited)
            if (!it) return false;
        return true;
    }

    int get_random_node_exclude(int exclude) {
        int node;
        do {
            node = rand() % num_nodes;
        } while (node == exclude);
        return node;
    }

public:
    void generate() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist_nodes(MIN_PEERS, MAX_PEERS);
        uniform_int_distribution<> dist_degree(MIN_DEGREE, MAX_DEGREE);

        while (true) {
            num_nodes = dist_nodes(gen);
            adj.assign(num_nodes, set<int>());

            // generating random degrees
            vector<int> degrees;
            for(int i=0; i<num_nodes; i++) degrees.push_back(dist_degree(gen));

            
            vector<int> available;
            for (int i = 0; i < num_nodes; ++i)
                for (int j = 0; j < degrees[i]; ++j)
                    available.push_back(i);

            shuffle(available.begin(), available.end(), gen);

            bool failed = false;
            while (available.size() >= 2) {
                int a = available.back(); 
                available.pop_back();
                int b = available.back(); 
                available.pop_back();
                if (a == b || adj[a].find(b)!=adj[a].end()) {
                    // Reinsert and reshuffle
                    available.push_back(a);
                    available.push_back(b);
                    shuffle(available.begin(), available.end(), gen);
                    continue;
                }
                adj[a].insert(b); // undirected
                adj[b].insert(a);
            }

            if (checkConnectivity()) break;
        }
    }

    void adjacentList(const string& filename) {
        ofstream fout(filename);
        for (int u = 0; u < num_nodes; ++u)
            for (int v : adj[u])
                if (u < v) fout << u << " " << v << "\n";
        fout.close();
        cout << "Edge list saved to " << filename << endl;
    }
};

int main() {
    srand(time(0));
    P2PNetwork net;
    net.generate();
    net.adjacentList("adjList.txt");
    return 0;
}