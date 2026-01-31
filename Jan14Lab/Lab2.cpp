#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
        Develop an efficient implementation of the Bellman-ford algorithm to determine the shortest
        path between two specified vertices in a weighted graph. Additionally, explain how the
        algorithm detects negative weight cycles.
*/

class Edge
{
public:
    int u, v, w;
};

class Graph
{
private:
    int V, E;
    Edge *edges;
    int *dist;

public:
    Graph(int vertices, int edgecount)
    {
        V = vertices;
        E = edgecount;
        edges = new Edge[E];
        dist = new int[V];
    }

    void addEdge(int index, int src, int dest, int weight)
    {
        edges[index].u = src;
        edges[index].v = dest;
        edges[index].w = weight;
    }

    void displayGraph()
    {
        for (int i = 0; i < E; i++)
        {
            cout << edges[i].u << " -- " << edges[i].v << " == " << edges[i].w << endl;
        }
    }

    void BellmanFord(int src)
    {
        for (int i = 0; i < V; i++)
        {
            dist[i] = INT_MAX;
        }
        dist[src] = 0;

        for (int i = 1; i < V; i++)
        {
            for (int j = 0; j < E; j++)
            {
                int u = edges[j].u;
                int v = edges[j].v;
                int w = edges[j].w;
                if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                {
                    cout << "The graph contains negative cycles \n";
                }
            }
        }

        for (int j = 0; j < E; j++)
        {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
            }
        }

        cout << "Vertex Distance from Source" << endl;
        for (int i = 0; i < V; i++)
        {

            cout << i << "\t\t" << dist[i] << endl;
        }
    }

    ~Graph()
    {
        delete[] edges;
        delete[] dist;
    }
};

int main()
{
    // int v, e;
    // cout << "Enter total vertices and edges: ";
    // cin >> v >> e;

    // Graph g(v, e);
    // int src, dest, weight;
    // cout << "Now, Enter space separated src, dest, weight of each edges: " << endl;
    // for (int i = 0; i < e; i++)
    // {
    //     cin >> src >> dest >> weight;
    //     g.addEdge(i, src, dest, weight);
    // }

    // g.displayGraph();

    // int t;
    // cout << "Enter total no of test case: ";
    // cin >> t;

    // while (t--)
    // {
    //     cout << "Enter src: ";
    //     cin >> src;
    //     g.BellmanFord(src);
    // }

    Graph g(5, 9);

    g.addEdge(0, 3, 0, 4);
    g.addEdge(1, 3, 2, 7);
    g.addEdge(2, 3, 4, 3);
    g.addEdge(3, 0, 2, 4);
    g.addEdge(4, 2, 0, -3);
    g.addEdge(5, 0, 4, 5);
    g.addEdge(6, 4, 2, 3);
    g.addEdge(7, 1, 2, -4);
    g.addEdge(8, 4, 1, 2);

    g.displayGraph();

    g.BellmanFord(0);

    return 0;
}