#include "graph.h"
#include "utils.h"
#include "queue.h"
#include "stack.h"

struct node {
    int vertex;
    struct node* next;
};

typedef struct node* node_t;

struct graph {
    // vettore di liste di adiacenza
    node_t adj_list[MAX_VERTICES];
    int num_vertices;
    bool is_oriented;
};

static node_t create_node (const int v);
static bool is_vertex_valid (graph_t graph, const int v);
static void recursive_dfs (graph_t graph, const int vertex, bool explored[]);

graph_t create_graph (const int num_vertices, const bool is_oriented) {
    if (num_vertices <= 0) {
        fprintf(stderr, "Invalid input for number of vertices: %d\n", num_vertices);
        exit(EXIT_FAILURE);
    }
    
    graph_t graph = secure_malloc(sizeof(struct graph));
    graph->num_vertices = num_vertices;
    graph->is_oriented = is_oriented;

    for (int i=0; i<num_vertices; i++) {
        graph->adj_list[i] = NULL;
    }
    
    return graph;
}

bool graph_add_edge (graph_t graph, int src, int dest) {
    if (graph_edge_exists(graph, src, dest) || src == dest) {
        return false;
    } 
    
    node_t new_node = create_node(dest);
    new_node->next = graph->adj_list[src];
    graph->adj_list[src] = new_node;

    if (graph->is_oriented) {
        new_node = create_node(src);
        new_node->next = graph->adj_list[dest];
        graph->adj_list[dest] = new_node;
    }

    return true;
}

// Cerco nella lista di adiacenza del vertice src il vertice dest  
bool graph_edge_exists(graph_t graph, const int src, const int dest) {
    if (graph == NULL) {
        fprintf(stderr, "Operation attempted on an empty or invalid graph\n");
        exit(EXIT_FAILURE);
    }

    if (!is_vertex_valid(graph, src) || !is_vertex_valid(graph, dest)) {
        return false;
    }
    
    node_t curr = graph->adj_list[src];
    while (curr) {
        if (curr->vertex == dest) {
            return true;
        }    
        curr = curr->next;
    }
    return false;
}

int* graph_bfs (graph_t graph, const int start, int* size) {
    int n = graph->num_vertices;
    queue_t queue = create_queue(n);
    
    bool discovered[n];
    discovered[start] = true;
    for (int i=1; i<n; i++) {
        discovered[i] = false;
    }

    queue_enqueue(queue, start);
    int temp_cc[n];
    *size = 0;

    while (!queue_is_empty(queue)) {
        int current;
        if (!queue_dequeue(queue, &current)) {
            break;
        }
        
        temp_cc[*size] = current;
        *size += 1;

        node_t neighbor = graph->adj_list[current];
        while (neighbor != NULL) {
            int v = neighbor->vertex;

            if (!discovered[v]) {
                discovered[v] = true;
                queue_enqueue(queue, v);
            }

            neighbor = neighbor->next;
        }
    }
    destroy_queue(&queue);
   
    int* cc = secure_malloc(*size * sizeof(int));
    memcpy(cc, bfs, *size * sizeof(int));
    return cc;
}

int* graph_dfs (graph_t graph, const int start, int *size) {
    int n = graph->num_vertices;
    stack_t stack = create_stack();

    
    bool explored[n];
    for (int i=0; i<n; i++) {
        explored[i] = false;
    }

    stack_push(stack, start);
    int temp_cc[n];
    *size = 0;

    while(!stack_is_empty(stack)) {
        int current = stack_top(stack);
        stack_pop(stack);

        if (!explored[current]) {
            temp_cc[*size] = current;
            *size += 1;
            explored[current] = true;
            
            node_t neighbor = graph->adj_list[current];
            while (neighbor != NULL) {
                if (!explored[neighbor->vertex]) {
                    stack_push(stack, neighbor->vertex);
                }
                neighbor = neighbor->next;
            }
        }
    }
    destroy_stack(&stack);

    int *cc = secure_malloc(*size * sizeof(int));
    memcpy(cc, dfs, *size * sizeof(int));
    return cc;
}

void graph_recursive_dfs (graph_t graph, const int start) {
    int n = graph->num_vertices;
    bool explored[n];
    for (int i=0; i<n; i++) {
        explored[i] = false;
    }

    printf("Recursive DFS traversal starting from vertex %d: ", start);
    recursive_dfs(graph, start, explored);
    printf("\n");    
}

static void recursive_dfs (graph_t graph, const int vertex, bool explored[]) {
    printf("%d ", vertex);
    explored[vertex] = true;

    node_t neighbor = graph->adj_list[vertex];
    while (neighbor != NULL) {
        if (!explored[neighbor->vertex]) {
            recursive_dfs(graph, neighbor->vertex, explored);
        }
        neighbor = neighbor->next;
    }
}

graph_t graph_reverse (graph_t graph) {
    if (graph == NULL) {
        fprintf(stderr, "Reverse operation attempted on an invalid graph\n");
        exit(EXIT_FAILURE);
    }

    if (!graph->is_oriented) {
        fprintf(stderr, "Cannot reverse an undirected graph\n");
        return NULL;
    }

    int n = graph->num_vertices;
    graph_t reversed = create_graph(n, true);

    for (int i=0; i<n; i++) {
        node_t v = graph->adj_list[i];
        while (v != NULL) {
            graph_add_edge(reversed, v->vertex, i);  
            v = v->next;
        } 
    }

    return reversed;
}

bool graph_is_strongly_connected (graph_t graph) {
    if (graph == NULL || !graph->is_oriented) {
        return false;
    }
    
    int size1 = 0, size2 = 0;
    int *cc1, *cc2;
    int start = 0;

    cc1 = graph_bfs(graph, start, &size1);
    graph_t reversed = graph_reverse(graph);
    cc2 = graph_bfs(reversed, start, &size2);

    bool result = (size1 == size2) && same_elements(cc1, cc2, size1);
    
    free(cc1);
    free(cc2);
    destroy_graph(&reversed);

    return result;
}

void destroy_graph (graph_t* graph_ptr) {
    if (graph_ptr == NULL || *graph_ptr == NULL) {
        return;
    }

    graph_t graph = *graph_ptr;

    for (int i = 0; i < graph->num_vertices; i++) {
        node_t curr = graph->adj_list[i];
        while (curr != NULL) {
            node_t temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    free(graph);
    *graph_ptr = NULL;
}

static node_t create_node (const int v) {
    node_t node = secure_malloc(sizeof(struct node));
    node->vertex = v;
    node->next = NULL;
    return node;
}

static bool is_vertex_valid (graph_t graph, const int v) {
    return 0<= v && v < graph->num_vertices;
}