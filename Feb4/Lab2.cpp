#include <bits/stdc++.h>
using namespace std;

/*
    Lab A: Write a program to implement the Kruskal's Algorithm
        for Minimum Spanning Trees using a Linked List approach.
*/
struct DSUNode
{
    int data;
    DSUNode *next = nullptr;
    DSUNode *rep = nullptr; // representative of the set
};

class DSU_LL
{
private:
    unordered_map<int, DSUNode *> nodes;

public:
    DSU_LL(int vertices){
        for(int i=0;i<vertices;i++){
            this->makeSet(i);
        }
    }
    // MakeSet operation
    void makeSet(int x)
    {
        DSUNode *node = new DSUNode{x};
        node->rep = node; // representative is itself
        nodes[x] = node;
    }

    // Find operation (O(1))
    DSUNode *findSet(int x)
    {
        return nodes[x]->rep;
    }

    // Union operation (O(n))
    bool unionSets(int x, int y)
    {
        DSUNode *repX = findSet(x);
        DSUNode *repY = findSet(y);

        // Cycle detected
        if (repX == repY)
            return false;

        // Append Y list to X list
        DSUNode *temp = repX;
        while (temp->next){
            temp = temp->next;
        }

        temp->next = repY;

        // Update representative pointers
        DSUNode *curr = repY;
        while (curr)
        {
            curr->rep = repX;
            curr = curr->next;
        }

        return true;
    }
};

struct Node
{
    int u;
    int wt;
    Node *next = nullptr;
};

struct Edge
{
    int src;
    int dest;
    int weight;
};

class Graph
{
private:
    int vertices;
    vector<Node *> adj;

public:
    Graph(int v)
    {
        vertices = v + 1;
        adj.resize(vertices);
    }

    // for undirected edge
    void addEdge(int u, int v, int wt)
    {
         // Add edge from u to v
        Node *newNode1 = new Node{v, wt, adj[u]};
        adj[u] = newNode1;
        
        // Add edge from v to u (undirected)
        Node *newNode2 = new Node{u, wt, adj[v]};
        adj[v] = newNode2;
    }

    void display()
    {
        cout << "Display Graph: \n";
        for (int i = 1; i < vertices; i++)
        {
            cout << "For vertex: " << i << ": ";
            Node *temp = adj[i];
            while (temp)
            {
                cout << "{ " << temp->u << ", " << temp->wt << " }, ";
                temp = temp->next;
            }
            cout << "\n";
        }
    }

    // Extract all edges from adjacency list
    vector<Edge> getAllEdges()
    {
        vector<Edge> edges;
        set<pair<int, int>> addedEdges; // To avoid duplicate edges

        for (int i = 1; i < vertices; i++)
        {
            Node *temp = adj[i];
            while (temp)
            {
                int u = i;
                int v = temp->u;
                int wt = temp->wt;

                // Add edge only once (for undirected graph)
                if (addedEdges.find({min(u, v), max(u, v)}) == addedEdges.end())
                {
                    edges.push_back(Edge{u, v, wt});
                    addedEdges.insert({min(u, v), max(u, v)});
                }

                temp = temp->next;
            }
        }

        return edges;
    }

    void kruskalMST()
    {
        // Step 1: Get all edges from adjacency list
        vector<Edge> edges = getAllEdges();

        // Step 2: Sort edges by weight (ascending order)
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
             { return a.weight < b.weight; });

        cout << "All edges sorted by weight:\n";
        for (const Edge &e : edges)
        {
            cout << e.src << " -- " << e.dest << " [weight: " << e.weight << "]\n";
        }
        cout << "\n";

        // Step 3: Initialize DSU
        DSU_LL dsu(vertices);

        // Step 4: Process edges in sorted order
        vector<Edge> mstEdges;
        int mstWeight = 0;

        cout << "Building MST:\n";
        for (const Edge &e : edges)
        {
            // Check if adding this edge creates a cycle
            if (dsu.unionSets(e.src, e.dest))
            {
                mstEdges.push_back(e);
                mstWeight += e.weight;
                cout << "Added edge: " << e.src << " -- " << e.dest
                     << " [weight: " << e.weight << "]\n";
            }
            else
            {
                cout << "Skipped edge: " << e.src << " -- " << e.dest
                     << " [weight: " << e.weight << "] (creates cycle)\n";
            }

            // MST will have (V-1) edges
            if (mstEdges.size() == vertices - 2)
            {
                break;
            }
        }

        // Step 5: Display MST
        cout << "\n=== Minimum Spanning Tree ===\n";
        cout << "Edges in MST:\n";
        for (const Edge &e : mstEdges)
        {
            cout << e.src << " -- " << e.dest << " [weight: " << e.weight << "]\n";
        }
        cout << "\nTotal weight of MST: " << mstWeight << "\n";
    }
};

int main()
{
    Graph g(5);

    // Adding edges (undirected graph for MST)
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 8);
    g.addEdge(2, 3, 3);
    g.addEdge(2, 5, 6);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 10);

    g.display();
    cout << "\n\n";

    g.kruskalMST();

    return 0;
}