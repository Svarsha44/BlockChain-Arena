import networkx as nx
import matplotlib.pyplot as plt

def visualize_from_file(filename="adjList.txt"):
    output = "network.png"
    G = nx.Graph()
    with open(filename, 'r') as f:
        for line in f:
            u, v = map(int, line.strip().split())
            G.add_edge(u, v)
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, node_color='blue', edge_color='black')
    plt.title("P2P Network Visualization (from C++)")
    plt.savefig(output)
    plt.close()
    print(f"Graph image saved as {output}")

visualize_from_file()
