#include <stdio.h>
#include "RB.h"
int main() {
    struct RB_tree tree;
    init(&tree);
    // test
insert(&tree, 31);

    insert(&tree, 31);

    insert(&tree, 31);

    insert(&tree, 31);
    insert(&tree, 31);
    insert(&tree, 31);
    print(&tree);
    pop_min(&tree);
    insert(&tree, 31);

    print(&tree);
    insert(&tree, 31);
    print(&tree);
    return 0;
}
