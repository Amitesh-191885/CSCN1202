#include <bits/stdc++.h>
using namespace std;

/*
    Lab A: Write a program to find the
    longest path from a given source in a DAG
    using an Adjacency List. Also, find the
    total number of distinct paths between
    two nodes u and v.
*/

struct Node
{
    int u;
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
        adj.resize(vertices);
    }

    // for directed edge
    void addEdge(int u, int v, int wt)
    {
        Node *srcHead = adj[u];
        Node *newNode = new Node{v, wt};
        newNode->next = srcHead;
        adj[u] = newNode;
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

    int countPathsDFS(int u, int v, unordered_map<int, int> &memo)
    {
        if (u == v)
        {
            return 1;
        }
        if (memo.find(u) != memo.end())
        {
            return memo[u];
        }

        int totalPaths = 0;
        Node *temp = adj[u];
        while (temp)
        {
            totalPaths += countPathsDFS(temp->u, v, memo);
            temp = temp->next;
        }
        memo[u] = totalPaths;
        return totalPaths;
    }

    int countDistinctPaths(int src, int dest)
    {
        unordered_map<int, int> ump;
        return countPathsDFS(src, dest, ump);
    }

    void topologicalSortUtil(int v, vector<bool> &visited, stack<int> &stack)
    {
        visited[v] = true;
        Node *temp = adj[v];
        while (temp)
        {
            if (!visited[temp->u])
            {
                topologicalSortUtil(temp->u, visited, stack);
            }
            temp = temp->next;
        }
        stack.push(v);
    }

    void findLongestPath(int src, int dest)
    {
        stack<int> st;
        vector<bool> visited(vertices, false);
        vector<int> dist(vertices, -1e9);

        for (int i = 0; i < vertices; i++)
        {
            if (!visited[i])
            {
                topologicalSortUtil(i, visited, st);
            }
        }

        dist[src] = 0;

        while (!st.empty())
        {
            int u = st.top();
            st.pop();

            if (dist[u] != -1e9)
            {
                Node *temp = adj[u];
                while (temp)
                {
                    int v = temp->u;
                    int wt = temp->wt;
                    if (dist[v] < dist[u] + wt)
                    {
                        dist[v] = dist[u] + wt;
                    }
                    temp = temp->next;
                }
            }
        }

        cout << "Longest distances from source " << src << " & Dest " << dest << " is " << dist[dest] << endl;
        // for (int i = 0; i < vertices; i++)
        // {
        //     (dist[i] == -1e9) ? cout << "INF " : cout << dist[i] << " ";
        // }
        cout << endl;
    }
};

int main()
{
    Graph g(5);

    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);
   
    g.display();
    cout << "\n\n";
    g.findLongestPath(1, 5);
    cout << "\n\n";
    cout << "Distict path from 1 to 5: " << g.countDistinctPaths(1, 5);

    return 0;
}