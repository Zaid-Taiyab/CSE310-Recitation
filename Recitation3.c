#include <stdio.h>  // include standard input/output functions
#include <stdlib.h> // include standard library functions
#include <string.h> // include string header file

// Struct for Edge of the graph
typedef struct Edge {
    int destination;
    double weight;
    struct Edge* next;
} Edge;

// Struct for Graph
typedef struct Graph {
    int numberOfVertices;
    Edge** adjacencyLists;
    char** vertexNames;
} Graph;

// Initializing all the functions
Edge* createEdge(int destination, double weight);
Graph* createGraph(int numberOfVertices);
void addEdge(Graph* graph, int start, int destination, double weight);
void printGraph(Graph* graph);
Graph* readGraphFromFile(const char* filename);
void freeGraphMemory(Graph* graph);

// Function to create an edge
Edge* createEdge(int destination, double weight) {
    Edge* newEdge = (Edge*) malloc (sizeof(Edge));
    newEdge->destination = destination;
    newEdge->weight = weight;
    newEdge->next = NULL;
    return newEdge;
}

// Function to create a graph
Graph* createGraph(int numberOfVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numberOfVertices = numberOfVertices;
    graph->adjacencyLists = (Edge**)malloc(numberOfVertices * sizeof(Edge*));
    graph->vertexNames = (char**)malloc(numberOfVertices * sizeof(char*));
    for (int i = 0; i < numberOfVertices; i++) {
        graph->adjacencyLists[i] = NULL;
        graph->vertexNames[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int start, int destination, double weight) {
    Edge* newEdge = createEdge(destination, weight);
    newEdge->next = graph->adjacencyLists[start];
    graph->adjacencyLists[start] = newEdge;
}

// Function to print the adjacency list of the graph
void printGraph(Graph* graph) {
    int i=0;
    while(i<graph->numberOfVertices){
        printf("%s : ", graph->vertexNames[i]);
        Edge* temp = graph->adjacencyLists[i];
        while (temp) {
            printf("%s/%.0f --> ", graph->vertexNames[temp->destination], temp->weight);
            temp = temp->next;
        }
        printf("Null\n");
        i+=1;
    }
}

// Function to read the graph from a file
Graph* readGraphFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    int numVertices, numEdges;
    fscanf(file, "%d %d", &numVertices, &numEdges);
    Graph* graph = createGraph(numVertices);
    if (graph == NULL) {
        fprintf(stderr, "Failed to create graph\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numVertices; i++) {
        graph->vertexNames[i] = (char*)malloc(20 * sizeof(char)); // assuming names are less than 20 chars
        if (graph->vertexNames[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for vertex name\n");
            exit(EXIT_FAILURE);
        }
        fscanf(file, "%s", graph->vertexNames[i]);
    }
    for (int i = 0; i < numEdges; i++) {
        char x[20], y[20];
        double weight;
        fscanf(file, "%s %s %lf", x, y, &weight);
        int start = -1, dest = -1;
        for (int j = 0; j < numVertices; j++) {
            if (strcmp(graph->vertexNames[j], x) == 0) {
                start = j;
            }
            if (strcmp(graph->vertexNames[j], y) == 0) {
                dest = j;
            }
        }
        if (start != -1 && dest != -1) {
            addEdge(graph, start, dest, weight);
        } else {
            fprintf(stderr, "Invalid vertex names in input file\n");
        }
    }
    fclose(file);
    return graph;
}

// Freeing the memory for the graph
void freeGraphMemory(Graph* graph) {
    int i=0;
    while(i<graph->numberOfVertices) {
        Edge* current = graph->adjacencyLists[i];
        while (current) {
            Edge* next = current->next;
            free(current);
            current = next;
        }
        free(graph->vertexNames[i]);
        i+=1;
    }
    free(graph->adjacencyLists);
    free(graph->vertexNames);
    free(graph);
}

// main function
int main() {
    Graph* output = readGraphFromFile("graph.txt");  // reading the graph from a file
    printGraph(output); // printing the graph
    freeGraphMemory(output);  // freeing the memory
    return 0;
}

