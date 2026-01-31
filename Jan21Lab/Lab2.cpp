#include <bits/stdc++.h>
using namespace std;
/*
2. Write a program to find the shortest paths between every pair of vertices in a graph
    using Floyd-Warshall's algorithm.
*/
struct Node
{
    int v;
    int w;
    Node *next;
};
class Graph
{
private:
    int V;
    vector<Node *> adj;

public:
    Graph(int vertices)
    {
        V = vertices + 1;
        adj.resize(V);
    }

    void addEdge(int src, int dest, int weight)
    {
        Node *tempSrcHead = adj[src];
        Node *newSrcNode = new Node{dest, weight};
        newSrcNode->next = tempSrcHead;
        adj[src] = newSrcNode;

        Node *tempDestHead = adj[dest];
        Node *newDestNode = new Node{src, weight};
        newDestNode->next = tempDestHead;
        adj[dest] = newDestNode;
    }

    void display()
    {
        for (int i = 1; i < V; i++)
        {
            cout << "Vertex " << i << " :";
            Node *tempNode = adj[i];
            while (tempNode)
            {
                cout << "{ " << tempNode->v << "," << tempNode->w << "}, ";
                tempNode = tempNode->next;
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
            Node *temp = adj[i];
            while (temp)
            {
                dist[i][temp->v] = min(dist[i][temp->v], temp->w);
                temp = temp->next;
            }
        }

        cout << "Before Floyed distances: \n";
        cout << "   ";
        for (int i = 1; i < V; i++)
        {
            cout << i << " , ";
        }
        cout << "\n";

        for (int i = 1; i < V; i++)
        {
            cout << i << ": ";
            for (int j = 1; j < V; j++)
            {
                if (dist[i][j] == INT_MAX)
                {
                    cout << "INF , ";
                }
                else
                {

                    cout << dist[i][j] << " , ";
                }
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
        cout << "   ";
        for (int i = 1; i < V; i++)
        {
            cout << i << " , ";
        }
        cout << "\n";

        for (int i = 1; i < V; i++)
        {
            cout << i << ": ";
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