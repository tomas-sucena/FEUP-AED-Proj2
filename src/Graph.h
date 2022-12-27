#ifndef AIRPORTAED_GRAPH_H
#define AIRPORTAED_GRAPH_H

#include <list>
#include <vector>

using namespace std;

template <typename T>
class Graph {
    private:
        struct Edge {
            int dest;
            int weight;
        };

        struct Node {
            T val;
            list<Edge> adj;
            bool visited;
        };

        int n;
        bool hasDir;
        vector<Node> nodes;

    public:
        // constructor
        explicit Graph(bool hasDir = false);
        Graph(int n, bool hasDir = false);

        // methods
        bool addEdge(int src, int dest, int weight = 1);
        bool removeEdge(int src, int dest);

        void addNode(T val);

        char areConnected(int n1, int n2);
};


template <typename T>
Graph<T>::Graph(bool hasDir){
    n = 0;
    this->hasDir = hasDir;
}

template <typename T>
Graph<T>::Graph(int n, bool hasDir){
    this->n = n;
    this->hasDir = hasDir;

    // fill the vector with empty nodes
    Node node;
    for (int i = 1; i <= n; i++){
        nodes.push_back(node);
    }
}

template <typename T>
bool Graph<T>::addEdge(int src, int dest, int weight) {
    if (src < 1 || src > n){
        return false;
    }

    Edge e; e.dest = dest; e.weight = weight;
    nodes[src].adj.push_back(e);

    return true;
}

template <typename T>
bool Graph<T>::removeEdge(int src, int dest) {
    if (src < 1 || src > n){
        return false;
    }

    for (auto it = nodes[src].adj.begin(); it != nodes[src].adj.end(); it++){
        if (it->dest == dest){
            nodes[src].adj.erase(it);
            return true;
        }
    }

    return false;
}

template <typename T>
void Graph<T>::addNode(T val){
    n++;

    Node node; node.val = val;
    nodes.push_back(node);
}

template <typename T>
char Graph<T>::areConnected(int n1, int n2){
    if (n1 < 1 || n1 > n || n2 < 1 || n2 > n){
        return 0;
    }

    char res = 0;

    // check if the first node reaches the second
    for (auto it = nodes[n1].adj.begin(); it != nodes[n1].adj.end(); it++){
        if (it->dest == n2){
            res++;
            break;
        }
    }

    // check if the second node reaches the first
    for (auto it = nodes[n2].adj.begin(); it != nodes[n2].adj.end(); it++){
        if (it->dest == n1){
            res = (!res) ? 2 : 3;
            break;
        }
    }

    return res;
}

#endif //AIRPORTAED_GRAPH_H