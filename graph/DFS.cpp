#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
    int V;
    vector<list<int>> adj;

    void dfsrecursive(int node, vector<int> &ls, vector<int> &vis)
    {
        ls.push_back(node);
        vis[node] = 1;
        for (int neighbor : adj[node])
        {
            if (vis[neighbor] != 1)
            {
                dfsrecursive(neighbor, ls, vis);
            }
        }
    }

public:
    Graph(int vertices)
    {
        V = vertices;
        adj.resize(vertices + 1);
    }

    void addEdge(int src, int dest)
    {
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }

    void display()
    {
        for (int i = 1; i <= V; i++)
        {
            cout << "at vertex: " << i << " [ ";
            for (int neighbour : adj[i])
            {
                cout << neighbour << ", ";
            }
            cout << " ]";
            cout << endl;
        }
    }

    void DFS(int src)
    {
        vector<int> traversed;
        vector<int> vis(V + 1, 0);
        // recursive call for DFS
        dfsrecursive(src, traversed, vis);
        // display
        cout << endl;
        for (int node : traversed)
        {
            cout << node << "->";
        }
    }
};

int main()
{
    Graph g(5);
    g.addEdge(1, 2);
    g.addEdge(1, 5);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.addEdge(2, 5);
    g.display();
    g.DFS(1);
    return 0;
}