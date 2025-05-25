#include "huffman_tree.h"

int main () {
    char *str = "nel_mezzo_del_cammin_di_nostra_vita";
    huffman_tree_t tree = build_huffman_tree(str);
    huffman_print_codes(tree);
    destroy_huffman_tree(&tree);
}

