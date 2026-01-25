#include <bits/stdc++.h>
using namespace std;
/*
2. Write a program to find the shortest paths between every pair of vertices in a graph
    using Floyd-Warshall's algorithm.
*/
class Graph
{
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int vertices)
    {
        V = vertices + 1;
        adj.resize(V);
    }

    void addEdge(int src, int dest, int weight)
    {
        adj[src].push_back({dest, weight});
        adj[dest].push_back({src, weight});
    }

    void display()
    {
        for (int i = 1; i < V; i++)
        {
            cout << "Vertex " << i << " :";
            for (auto it : adj[i])
            {
                cout << "{ " << it.first << "," << it.second << "}, ";
            }
            cout << endl;
        }
    }

    void Floyd_Warshall()
    {
        vector<vector<int>> dist(V, vector<int>(V, INT_MAX));
        for (int i = 1; i < V; i++)
        {
            dist[i][i] = 0;
        }
        for (int i = 1; i < V; i++)
        {
            for (auto it : adj[i])
            {
                dist[i][it.first] = it.second;
            }
        }

        cout << "Before Floyed distances: \n";
        for (int i = 1; i < V; i++)
        {
            for (int j = 1; j < V; j++)
            {
                cout << dist[i][j] << " , ";
            }
            cout << endl;
        }

        // floyd warshall algorithms
        for (int k = 1; k < V; k++)
        {
            for (int i = 1; i < V; i++)
            {
                for (int j = 1; j < V; j++)
                {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    {
                        dist[i][j] = min(dist[i][j], (dist[i][k] + dist[k][j]));
                    }
                }
            }
        }

        cout << "\n\n After Floyed distances: \n";

        for (int i = 1; i < V; i++)
        {
            for (int j = 1; j < V; j++)
            {
                cout << dist[i][j] << " , ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph g(5);
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 8);
    g.addEdge(2, 3, 3);
    g.addEdge(2, 5, 6);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 10);
    g.display();
    cout << "\n";
    g.Floyd_Warshall();

    return 0;
}