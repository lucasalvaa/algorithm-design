#ifndef GRAPH
#define GRAPH

#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct graph* graph_t;

graph_t create_graph (const int num_vertices, const bool is_oriented);

bool graph_add_edge (graph_t graph, const int src, const int dest);

bool graph_edge_exists(graph_t graph, const int src, const int dest);

int* graph_bfs (graph_t graph, const int start, int *size);

int* graph_dfs (graph_t graph, const int start, int *size);

void graph_recursive_dfs (graph_t graph, const int start);

graph_t graph_reverse (graph_t graph);

bool graph_is_strongly_connected (graph_t graph);

void destroy_graph (graph_t* graph_ptr);

#endif