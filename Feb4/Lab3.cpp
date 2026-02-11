#include <bits/stdc++.h>
using namespace std;
/* 
    Lab A: Write a program to implement the Kruskal's Algorithm 
        for Minimum Spanning Trees using a Linked List approach.
*/

struct Node
{
    int u;
    int wt;
    Node *next;
};

// Structure to represent an edge
struct Edge
{
    int src, dest, weight;
    
    // Constructor
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

// Disjoint Set Union (Union-Find) for cycle detection
class DSU
{
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        
        // Initially, each vertex is its own parent
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    
    // Find operation with path compression
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    // Union operation with union by rank
    bool unionSets(int x, int y)
    {
        int xRoot = find(x);
        int yRoot = find(y);
        
        // If both belong to same set, adding edge will create cycle
        if (xRoot == yRoot)
        {
            return false;
        }
        
        // Union by rank
        if (rank[xRoot] < rank[yRoot])
        {
            parent[xRoot] = yRoot;
        }
        else if (rank[xRoot] > rank[yRoot])
        {
            parent[yRoot] = xRoot;
        }
        else
        {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
        
        return true;
    }
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
        
        // Initialize all adjacency lists to NULL
        for (int i = 0; i < vertices; i++)
        {
            adj[i] = nullptr;
        }
    }
    
    // Add undirected edge (for MST, we need undirected graph)
    void addEdge(int u, int v, int wt)
    {
        // Add edge from u to v
        Node *newNode1 = new Node{v, wt, adj[u]};
        adj[u] = newNode1;
        
        // Add edge from v to u (undirected)
        Node *newNode2 = new Node{u, wt, adj[v]};
        adj[v] = newNode2;
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
                    edges.push_back(Edge(u, v, wt));
                    addedEdges.insert({min(u, v), max(u, v)});
                }
                
                temp = temp->next;
            }
        }
        
        return edges;
    }
    
    // Kruskal's Algorithm
    void kruskalMST()
    {
        cout << "=== Kruskal's Algorithm for MST ===\n\n";
        
        // Step 1: Get all edges from adjacency list
        vector<Edge> edges = getAllEdges();
        
        // Step 2: Sort edges by weight (ascending order)
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });
        
        cout << "All edges sorted by weight:\n";
        for (const Edge &e : edges)
        {
            cout << e.src << " -- " << e.dest << " [weight: " << e.weight << "]\n";
        }
        cout << "\n";
        
        // Step 3: Initialize DSU
        DSU dsu(vertices);
        
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
    
    void display()
    {
        cout << "Display Graph (Adjacency List): \n";
        for (int i = 1; i < vertices; i++)
        {
            cout << "Vertex " << i << ": ";
            Node *temp = adj[i];
            while (temp)
            {
                cout << "{ " << temp->u << ", " << temp->wt << " } ";
                temp = temp->next;
            }
            cout << "\n";
        }
    }
    
    // Destructor to free memory
    ~Graph()
    {
        for (int i = 0; i < vertices; i++)
        {
            Node *temp = adj[i];
            while (temp)
            {
                Node *toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
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