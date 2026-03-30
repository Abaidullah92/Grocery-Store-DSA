#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <queue>
using namespace std;

class Graph {
public:
    Graph(int numVertex);  // constructor initializes adjacency matrix
    void insertEdge(int frmVertex, int toVertex);  // inserts edge from one vertex to another
    void bfsShortestPath(int startVertex, int endVertex);  // BFS to find the shortest path
    void display();  // display adjacency matrix

private:
    int** adj_matrix;
    int numVertices;
};


Graph::Graph(int numVertex) {
    this->numVertices = numVertex;
    adj_matrix = new int* [numVertex];
    for (int i = 0; i < numVertex; i++) {
        adj_matrix[i] = new int[numVertex];
        for (int j = 0; j < numVertex; j++) {
            adj_matrix[i][j] = 0;
        }
    }
}

void Graph::insertEdge(int FromVertex, int ToVertex) {
    if (FromVertex >= numVertices || ToVertex >= numVertices || FromVertex < 0 || ToVertex < 0) {
        cout << "Invalid edge!" << endl;
    }
    else {
        adj_matrix[FromVertex][ToVertex] = 1;
        adj_matrix[ToVertex][FromVertex] = 1;  // for undirected graph
    }
}

void Graph::bfsShortestPath(int startVertex, int endVertex) {
    bool* visited = new bool[numVertices]();
    int* parent = new int[numVertices];
    for (int i = 0; i < numVertices; i++) {
        parent[i] = -1;
    }

    queue<int> q;
    visited[startVertex] = true;
    q.push(startVertex);

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();

        if (vertex == endVertex) {
            // Shortest path found
            int* path = new int[numVertices];
            int pathIndex = 0;
            int current = endVertex;
            while (current != -1) {
                path[pathIndex++] = current;
                current = parent[current];
            }

            
            cout << "Shortest path from store to customer: ";
            for (int i = pathIndex - 1; i >= 0; i--) {
                cout << path[i] << " ";
            }
            cout << endl;
            delete[] path;
            delete[] visited;
            delete[] parent;
            return;
        }

        for (int i = 0; i < numVertices; i++) {
            if (adj_matrix[vertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                parent[i] = vertex;
                q.push(i);
            }
        }
    }

    cout << "No path found from store to customer." << endl;
    delete[] visited;
    delete[] parent;
}

void Graph::display() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cout << adj_matrix[i][j] << " ";
        }
        cout << endl;
    }
}

#endif

