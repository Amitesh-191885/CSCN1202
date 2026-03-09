#include <bits/stdc++.h>
using namespace std;
/*
    Lab 2: Write a C++ program to find the Maximum Matching in a Bipartite Graph using the Hungarian Algorithm.
*/

struct Node
{
    int v;
    Node* next;
};

class Graph
{
private:
    int U, V;
    vector<Node*> adj;

    // Bipartite Matching Function
    bool bpm(int u, vector<bool>& visited, vector<int>& matchR)
    {
        Node* temp = adj[u];

        while (temp)
        {
            int v = temp->v;

            if (!visited[v])
            {
                visited[v] = true;

                if (matchR[v] == -1 || bpm(matchR[v], visited, matchR))
                {
                    matchR[v] = u;
                    return true;
                }
            }

            temp = temp->next;
        }

        return false;
    }

public:
    Graph(int u, int v)
    {
        U = u;
        V = v;
        adj.resize(U + 1, nullptr);
    }

    void addEdge(int u, int v)
    {
        Node* newNode = new Node{v, adj[u]};
        adj[u] = newNode;
    }

    void display()
    {
        cout << "Bipartite Graph:\n";

        for (int i = 1; i <= U; i++)
        {
            cout << "U" << i << " : ";

            Node* temp = adj[i];
            while (temp)
            {
                cout << "V" << temp->v << " ";
                temp = temp->next;
            }

            cout << endl;
        }
    }

    void maximumMatching()
    {
        vector<int> matchR(V + 1, -1);

        int result = 0;

        for (int u = 1; u <= U; u++)
        {
            vector<bool> visited(V + 1, false);

            if (bpm(u, visited, matchR)){
                result++;
            }
        }

        cout << "\nMaximum Matching = " << result << endl;

        cout << "Matched Pairs:\n";

        for (int v = 1; v <= V; v++)
        {
            if (matchR[v] != -1){
                cout << "U" << matchR[v] << " - V" << v << endl;
            }
        }
    }
};

int main()
{
    Graph g(4, 4);

    g.addEdge(1, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 2);
    g.addEdge(4, 2);
    g.addEdge(4, 4);

    g.display();

    g.maximumMatching();

    return 0;
}