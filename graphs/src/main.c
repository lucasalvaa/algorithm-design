#include <stdio.h>
#include <stdbool.h>
#include "graph.h"

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

    graph_bfs(g, 0);
    graph_dfs(g, 0);
    graph_recursive_dfs(g, 0);

    destroy_graph(&g);
    return 0;
}

