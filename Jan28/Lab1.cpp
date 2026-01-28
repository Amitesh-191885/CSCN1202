#include <bits/stdc++.h>
using namespace std;
/*
Lab 3. Formulate and implement Dijkstra's algorithm to compute the
    shortest path between two vertices in a 
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int vertex;
    int weight;
    Node* next;
};

class Graph {
private:
    int V;
    vector<Node*> adj;   // adjacency list using linked lists

public:
    Graph(int v) {
        V = v;
        adj.resize(V + 1, nullptr);   // 1-based indexing
    }

    // Undirected weighted edge
    void addEdge(int src, int dest, int weight) {
        Node* newNode = new Node{dest, weight, adj[src]};
        adj[src] = newNode;

        newNode = new Node{src, weight, adj[dest]};
        adj[dest] = newNode;
    }

        void dijkstra(int src) {
        vector<int> dist(V + 1, INT_MAX);
        priority_queue<pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto topVal = pq.top();
            pq.pop();

            int currDist = topVal.first;
            int u = topVal.second;

            if (currDist > dist[u])
                continue;

            Node* temp = adj[u];
            while (temp) {
                int v = temp->vertex;
                int wt = temp->weight;

                if (dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                    pq.push({dist[v], v});
                }
                temp = temp->next;
            }
        }

        // Print distances
        cout << "Shortest distances from source " << src << ":\n";
        for (int i = 1; i <= V; i++) {
            if (dist[i] == INT_MAX)
                cout << i << " : INF\n";
            else
                cout << i << " : " << dist[i] << "\n";
        }
    }
};


int main() {
    Graph g(5);

    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 8);
    g.addEdge(2, 3, 3);
    g.addEdge(2, 5, 6);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 10);

    g.dijkstra(1);

    return 0;
}

