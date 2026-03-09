#include <bits/stdc++.h>
using namespace std;
/*
    Lab 1: Write a program to implement Prim's Algorithm to compare the two MST approaches.
*/
struct Node
{
    int v;
    int wt;
    Node *next = nullptr;
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
        adj.resize(vertices, nullptr);
    }

    void addEdge(int u, int v, int weight)
    {
        Node *newNode = new Node{v, weight, adj[u]};
        adj[u] = newNode;

        Node *newNode2 = new Node{u, weight, adj[v]};
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
                cout << "{ " << temp->v << ", " << temp->wt << " }, ";
                temp = temp->next;
            }
            cout << "\n";
        }
    }

    void primMST()
    {
        vector<int> key(vertices, INT_MAX);
        vector<bool> inMST(vertices, false);
        vector<int> parent(vertices, -1);

        key[1] = 0;

        for (int count = 1; count < vertices - 1; count++)
        {
            int u = -1;
            int minKey = INT_MAX;

            // Find vertex with minimum key
            for (int v = 1; v < vertices; v++)
            {
                if (!inMST[v] && key[v] < minKey)
                {
                    minKey = key[v];
                    u = v;
                }
            }

            inMST[u] = true;

            Node *temp = adj[u];
            while (temp)
            {
                int v = temp->v;
                int weight = temp->wt;

                if (!inMST[v] && weight < key[v])
                {
                    key[v] = weight;
                    parent[v] = u;
                }

                temp = temp->next;
            }
        }

        cout << "\nEdges in MST (Prim):\n";
        int totalWeight = 0;

        for (int i = 2; i < vertices; i++)
        {
            cout << parent[i] << " - " << i
                 << "  weight: " << key[i] << endl;

            totalWeight += key[i];
        }

        cout << "Total MST weight: " << totalWeight << endl;
    }

    void primMSTPQ()
    {
        vector<bool> inMST(vertices, false);
        vector<int> key(vertices, INT_MAX);
        vector<int> parent(vertices, -1);

        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>>
            pq;

        key[1] = 0;
        pq.push({0, 1});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u])
                continue;

            inMST[u] = true;

            Node *temp = adj[u];

            while (temp)
            {
                int v = temp->v;
                int weight = temp->wt;

                if (!inMST[v] && weight < key[v])
                {
                    key[v] = weight;
                    parent[v] = u;

                    pq.push({key[v], v});
                }

                temp = temp->next;
            }
        }

        cout << "\nEdges in MST (Prim + Priority Queue):\n";

        int totalWeight = 0;

        for (int i = 2; i < vertices; i++)
        {
            cout << parent[i] << " - " << i
                 << " weight: " << key[i] << endl;

            totalWeight += key[i];
        }

        cout << "Total MST Weight: " << totalWeight << endl;
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

    cout << "\n\n";

    g.primMSTPQ();
    return 0;
}