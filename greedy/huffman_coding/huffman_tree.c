#include <stdio.h>
#include "huffman_tree.h"
#include "minheap.h"
#include "utils.h"

typedef struct node {
    char c;
    int freq;
    struct node *left, *right;
} node_t;

struct huffman_tree {
    node_t* root;
};

static node_t* node_create (char c, int freq, node_t* left, node_t* right);
static void free_node (node_t* root);
static void print_codes (const node_t* root, char code[], int depth);
static int *frequences (char *str);

huffman_tree_t build_huffman_tree (char* str) {
    const int n = 256;
    min_heap_t heap = create_heap(n);
    int *freqs = frequences(str);

    for (int c=1; c<n; c++) {
        if (freqs[c] <= 0) {
            continue;
        }
        node_t* leaf = node_create(c, freqs[c], NULL, NULL);
        heap_push(heap, (void*) leaf, leaf->freq);
    }

    while (heap_get_size(heap) > 1) {
        node_t* left = (node_t*) heap_pop(heap);
        node_t* right = (node_t*) heap_pop(heap);
        node_t* parent = node_create('\0', left->freq + right->freq, left, right);
        heap_push(heap, (void*) parent, parent->freq);
    }

    node_t* root = (node_t*) heap_pop(heap);
    destroy_heap(&heap);

    huffman_tree_t tree = secure_malloc(sizeof(struct huffman_tree));
    tree->root = root;
    free(freqs);
    return tree;
}

void huffman_print_codes (huffman_tree_t tree) {
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Operation attempted on an invalid Huffman tree\n");
        exit(EXIT_FAILURE);
    }

    char code[256];
    print_codes(tree->root, code, 0);
}

void destroy_huffman_tree (huffman_tree_t* tree_ptr) {
    if (tree_ptr == NULL || *tree_ptr == NULL) {
        return;
    }

    huffman_tree_t tree = *tree_ptr;
    free_node(tree->root);
    free(tree);
    *tree_ptr = NULL;
}


static void print_codes (const node_t* root, char code[], int depth) {
    if (root == NULL) {
        return;
    } 

    if (root->left == NULL && root->right == NULL) {
        code[depth] = '\0';
        printf("%c: %s\n", root->c, code);
        return;
    }

    code[depth] = '0';
    print_codes(root->left, code, depth + 1);
    code[depth] = '1';
    print_codes(root->right, code, depth + 1);
}

static int *frequences (char *str) {
    int *freqs = secure_calloc(256, sizeof(int));
    
    while (*str) {
        freqs[*str]++;
        str++;
    }

    return freqs;
}

static node_t* node_create (char c, int freq, node_t* left, node_t* right) {
    node_t* n = secure_malloc(sizeof(struct node));
    n->c = c;
    n->freq = freq;
    n->left = left;
    n->right = right;
    return n;
}

static void free_node (node_t* root) {
    if (root == NULL) {
        return;
    } 

    free_node(root->left);
    free_node(root->right);
    free(root);
}