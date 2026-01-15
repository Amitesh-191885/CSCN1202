#include <bits/stdc++.h>
using namespace std;
/*
    Problem Statement:
    Design and implement algorithms to compute the union, intersection, and ring sum
    (symmetric difference) of two graphs, Analyze the resulting graphs in terms of
    vertex and edge sets, and discuss their structural properties.
*/

class Vertex {
public:
    int data;
    Vertex* next;

    Vertex(int v) {
        data = v;
        next = NULL;
    }
};

class Edge {
public:
    int u, v;
    Edge* next;

    Edge(int x, int y) {
        u = x;
        v = y;
        next = NULL;
    }
};

class Graph {
private:
    Vertex* vHead;
    Edge* eHead;

    bool vertexExists(int v) {
        Vertex* temp = vHead;
        while (temp) {
            if (temp->data == v)
                return true;
            temp = temp->next;
        }
        return false;
    }

    bool edgeExists(int u, int v) {
        Edge* temp = eHead;
        while (temp) {
            if ((temp->u == u && temp->v == v) ||
                (temp->u == v && temp->v == u))
                return true;
            temp = temp->next;
        }
        return false;
    }

public:
    Graph() {
        vHead = NULL;
        eHead = NULL;
    }

    /* -------- Add Vertex -------- */
    void addVertex(int v) {
        if (vertexExists(v)) return;

        Vertex* temp = new Vertex(v);
        temp->next = vHead;
        vHead = temp;
    }

    /* -------- Add Edge -------- */
    void addEdge(int u, int v) {
        if (u == v || edgeExists(u, v)) return;

        addVertex(u);
        addVertex(v);

        Edge* temp = new Edge(u, v);
        temp->next = eHead;
        eHead = temp;
    }

    /* -------- Display Graph -------- */
    void display() {
        cout << "Vertices: ";
        Vertex* v = vHead;
        while (v) {
            cout << v->data << " ";
            v = v->next;
        }

        cout << "\nEdges: ";
        Edge* e = eHead;
        while (e) {
            cout << "(" << e->u << "," << e->v << ") ";
            e = e->next;
        }
        cout << "\n\n";
    }

    /* -------- Union -------- */
    static Graph Union(Graph& g1, Graph& g2) {
        Graph g;

        for (Vertex* v = g1.vHead; v; v = v->next)
            g.addVertex(v->data);

        for (Vertex* v = g2.vHead; v; v = v->next)
            g.addVertex(v->data);

        for (Edge* e = g1.eHead; e; e = e->next)
            g.addEdge(e->u, e->v);

        for (Edge* e = g2.eHead; e; e = e->next)
            g.addEdge(e->u, e->v);

        return g;
    }

    /* -------- Intersection -------- */
    static Graph Intersection(Graph& g1, Graph& g2) {
        Graph g;

        for (Vertex* v = g1.vHead; v; v = v->next)
            if (g2.vertexExists(v->data))
                g.addVertex(v->data);

        for (Edge* e = g1.eHead; e; e = e->next)
            if (g2.edgeExists(e->u, e->v))
                g.addEdge(e->u, e->v);

        return g;
    }

    /* -------- Ring Sum -------- */
    static Graph RingSum(Graph& g1, Graph& g2) {
        Graph g;

        for (Vertex* v = g1.vHead; v; v = v->next)
            g.addVertex(v->data);

        for (Vertex* v = g2.vHead; v; v = v->next)
            g.addVertex(v->data);

        for (Edge* e = g1.eHead; e; e = e->next)
            if (!g2.edgeExists(e->u, e->v))
                g.addEdge(e->u, e->v);

        for (Edge* e = g2.eHead; e; e = e->next)
            if (!g1.edgeExists(e->u, e->v))
                g.addEdge(e->u, e->v);

        return g;
    }
};




int main() {
    int v1, e1;
    cout<<"For Graph 1: Enter vertex and edge: ";
    cin>> v1 >> e1;
    cout<<"Now Enter each edge space separeted for the graph G1: ";
    int src, dest;
    
    Graph G1, G2;
    for(int i=0;i<e1;i++){
        cin>> src>>dest;
        G1.addEdge(src, dest);
    }

    
    int v2, e2;
    cout<<"For Graph 2: Enter vertex and edge: ";
    cin>> v2 >> e2;
    cout<<"Now Enter each edge space separeted for the graph G2: ";
     for(int i=0;i<e2;i++){
        cin>> src>>dest;
        G2.addEdge(src, dest);
    }


    cout << "Graph G1\n";
    G1.display();

    cout << "Graph G2\n";
    G2.display();

    Graph GU = Graph::Union(G1, G2);
    cout << "Union\n";
    GU.display();

    Graph GI = Graph::Intersection(G1, G2);
    cout << "Intersection\n";
    GI.display();

    Graph GR = Graph::RingSum(G1, G2);
    cout << "Ring Sum\n";
    GR.display();

    return 0;
}
