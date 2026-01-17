#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
    int v;
    vector<list<int>> adjList;

    void DFSTraverse(int node, vector<int> &vis, vector<int> &ls)
    {
        vis[node] = 1;
        ls.push_back(node);
        if (adjList[node].size())
        {
            for (auto it : adjList[node])
            {
                if (!vis[it])
                {
                    DFSTraverse(it, vis, ls);
                }
            }
        }
        else
        {
            return;
        }
    }

public:
    Graph(int vertices)
    {
        v = vertices;
        adjList.resize(v + 2);
    }

    void addEdge(int src, int dest)
    {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    void display()
    {
        for (int i = 1; i <= v; i++)
        {
            cout << "[" << i << "]: ";
            for (auto node : adjList[i])
                cout << node << "-> ";
            cout << endl;
        }
    }

    void BFS(int src)
    {
        queue<int> q;
        vector<int> vis(v + 2, 0);
        vector<int> traverse;

        q.push(src);
        vis[src] = 1;

        while (!q.empty())
        {
            int node = q.front();
            traverse.push_back(node);
            q.pop();

            for (auto it : adjList[node])
            {
                if (vis[it] != 1)
                {
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }

        cout << "BFS: ";
        for (auto it : traverse)
        {
            cout << it << "-> ";
        }
    }

    void DFS(int src)
    {
        vector<int> traverse;
        vector<int> vis(v + 2, 0);

        DFSTraverse(src, vis, traverse);

        cout << "DFS: ";
        for (auto it : traverse)
        {
            cout << it << "-> ";
        }
    }
};

int main()
{
    int v, e;
    cout << "Enter vertices and edges: ";
    cin >> v >> e;
    Graph g(v);

    cout << "Enter space separated edges: " << endl;
    int src, dest;

    for (int i = 0; i < e; i++)
    {
        cin >> src >> dest;
        g.addEdge(src, dest);
    }

    g.display();
    cout << endl;
    g.BFS(1);
    cout << endl;
    g.DFS(1);
    return 0;
}