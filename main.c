#include <stdio.h>
#include "RB.h"
int main() {
    struct RB_tree tree;
    init(&tree);
    insert(&tree, 10);
    insert(&tree, 5);
    insert(&tree, 1);
//    insert(&tree, 3);
    print(&tree);

    return 0;
}
