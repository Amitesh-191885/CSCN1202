#include <bits/stdc++.h>
using namespace std;
/*
    Lab 2: Implement a solution for the Travelling Salesman Problem (TSP)
    using C++ where the tour is represented using a circular linked list,
    and compute the minimum route cost using a heuristic approach.
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
    vector<bool> visited;

    Node *head = nullptr;
    Node *tail = nullptr;

    void insertCity(int city, int weight)
    {
        Node *newNode = new Node{city, weight};

        if (!head)
        {
            head = tail = newNode;
            tail->next = head;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
    }

public:
    Graph(int v)
    {
        vertices = v + 1;
        adj.resize(vertices, nullptr);
        visited.resize(vertices, false);
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

    void TSP(int start)
    {
        int curr = start;
        visited[curr] = true;
        int totalCost = 0;
        insertCity(curr, totalCost);

        for (int j = 1; j < vertices - 1; j++)
        {
            int nextCity = -1;
            int minDist = INT_MAX;

            Node *temp = adj[curr];

            while (temp)
            {
                int v = temp->v;
                int wt = temp->wt;

                if (!visited[v] && wt < minDist)
                {
                    minDist = wt;
                    nextCity = v;
                }

                temp = temp->next;
            }

            visited[nextCity] = true;
            totalCost += minDist;
            insertCity(nextCity, totalCost);
            curr = nextCity;
        }

        Node *temp = adj[curr];
        while (temp)
        {
            if (temp->v == start)
            {
                totalCost += temp->wt;
                break;
            }
            temp = temp->next;
        }

        cout << "Total Cost of Travel: " << totalCost << "\n";
    }

    void displayTour()
    {
        cout << "TSP Tour : ";

        Node *temp = head;
        if (!temp)
        {
            return;
        }

        do
        {
            cout << temp->v << "(" << temp->wt << ")" << " -> ";
            temp = temp->next;
        } while (temp != head);

        cout << head->v << endl;
    }
};

int main()
{
    Graph g(4);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 15);
    g.addEdge(1, 4, 20);
    g.addEdge(2, 3, 35);
    g.addEdge(2, 4, 25);
    g.addEdge(3, 4, 30);
    g.display();

    cout << "\n\n";

    g.TSP(1);
    cout << "\n";

    g.displayTour();

    return 0;
}