#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

typedef struct huffman_tree* huffman_tree_t;

huffman_tree_t build_huffman_tree (char* str);

void destroy_huffman_tree (huffman_tree_t* tree_ptr);

void huffman_print_codes(huffman_tree_t tree);

#endif // HUFFMAN_TREE_H


