#include <stdio.h>
#include "RB.h"
int main() {
    struct RB_tree tree;
    init(&tree);
    // test
    insert(&tree, 10);
    insert(&tree, 5);
    insert(&tree, 1);
    insert(&tree, 11);
    insert(&tree, 12);
    insert(&tree, 13);
    insert(&tree, 14);
    insert(&tree, 7);
    insert(&tree, 15);
    print(&tree);

    return 0;
}
