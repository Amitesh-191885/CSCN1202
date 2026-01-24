#include <bits/stdc++.h>
using namespace std;
/*
1. Write a program to find the shortest path between
    two vertices in a graph using Dijkstra's algorithm.
*/
class Graph
{
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int vertex)
    {
        V = vertex;
        adj.resize(V + 1);
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

    void DijkstrasAlgo(int src, int dest)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(V + 1, INT_MAX);
        dist[src] = 0;
        pq.emplace(0, src);

        while (!pq.empty())
        {
            auto topVal = pq.top();
            pq.pop();

            int currDist = topVal.first;
            int pqTopVertex = topVal.second;

            if (currDist > dist[pqTopVertex] || currDist < 0)
            {
                continue;
            }

            for (auto &neighbour : adj[pqTopVertex])
            {
                int vertex = neighbour.first;
                int weight = neighbour.second;

                if (dist[pqTopVertex] != INT_MAX)
                {
                    if ((dist[pqTopVertex] + weight) < dist[vertex])
                    {
                        dist[vertex] = dist[pqTopVertex] + weight;
                        pq.emplace(dist[vertex], vertex);
                    }
                }
            }

            if (pqTopVertex == dest)
            {
                break;
            }
        }

        if (dist[dest] != INT_MAX)
        {
            cout << "\nFrom src: " << src << " to Dest: " << dest << " shortest distance is: " << dist[dest] << endl;
        }
        else
        {
            cout << "\nFrom src: " << src << " to Dest: " << dest << " no shortest path exist " << endl;
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

    g.DijkstrasAlgo(1, 5);

    return 0;
}