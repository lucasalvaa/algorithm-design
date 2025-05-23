#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"

void print_bfs (graph_t graph, const int start);
void print_dfs (graph_t graph, const int start);

int main() {
    const int num_vertices = 6;
    const bool is_oriented = false;
    graph_t g = create_graph(num_vertices, is_oriented);

    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 0, 4);
    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 1, 3);
    graph_add_edge(g, 1, 4);
    graph_add_edge(g, 2, 3);
    graph_add_edge(g, 3, 4);

    print_bfs(g, 0);
    print_dfs(g, 2);
    graph_recursive_dfs(g, 0);

    destroy_graph(&g);
    return 0;
}

void print_bfs (graph_t graph, const int start) {
    int size = 0;
    int *bfs = graph_bfs(graph, start, &size);

    printf("BFS traversal starting from vertex %d: ", start);
    for (int i=0; i<size; i++) {
        printf("%d ", bfs[i]);
    }
    printf("\n");
    free(bfs);
}

void print_dfs (graph_t graph, const int start) {
    int size = 0;
    int *dfs = graph_dfs(graph, start, &size);

    printf("DFS traversal starting from vertex %d: ", start);
    for (int i=0; i<size; i++) {
        printf("%d ", dfs[i]);
    }
    printf("\n");
    free(dfs);
}



