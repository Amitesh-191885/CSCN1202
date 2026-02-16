#include<bits/stdc++.h>
using namespace std;
/*
   Lab 1: Write a C++ program to determine whether a given undirected graph is Hamiltonian.
*/

struct Node {
    int vertex;
    Node* next;
};

class Graph {
private:
    int V;
    vector<Node*> adj;

    // Check adjacency using linked list
    bool isAdjacent(int u, int v) {
        Node* temp = adj[u];
        while (temp) {
            if (temp->vertex == v)
                return true;
            temp = temp->next;
        }
        return false;
    }

    // Backtracking utility
    bool hamiltonianUtil(vector<int>& path, vector<bool>& visited, int pos) {
        // All vertices included
        if (pos == V) {
            // Check edge from last to first (cycle)
            return isAdjacent(path[pos - 1], path[0]);
        }

        for (int v = 2; v <= V; v++) {
            if (!visited[v] && isAdjacent(path[pos - 1], v)) {
                visited[v] = true;
                path[pos] = v;

                if (hamiltonianUtil(path, visited, pos + 1))
                    return true;

                // Backtrack
                visited[v] = false;
            }
        }
        return false;
    }

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V + 1, nullptr);
    }

    // Undirected edge
    void addEdge(int u, int v) {
        Node* newNode = new Node{v, adj[u]};
        adj[u] = newNode;

        newNode = new Node{u, adj[v]};
        adj[v] = newNode;
    }

    void display() {
        cout << "Graph:\n";
        for (int i = 1; i <= V; i++) {
            cout << i << " : ";
            Node* temp = adj[i];
            while (temp) {
                cout << temp->vertex << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    bool isHamiltonian() {
        vector<int> path(V);
        vector<bool> visited(V + 1, false);

        // Start from vertex 1
        path[0] = 1;
        visited[1] = true;

        return hamiltonianUtil(path, visited, 1);
    }

    ~Graph() {
        for (int i = 1; i <= V; i++) {
            Node* temp = adj[i];
            while (temp) {
                Node* del = temp;
                temp = temp->next;
                delete del;
            }
        }
    }
};

int main() {
    Graph g(5);

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 1);

    g.display();
    cout << endl;

    if (g.isHamiltonian())
        cout << "Graph is Hamiltonian\n";
    else
        cout << "Graph is NOT Hamiltonian\n";

    return 0;
}
