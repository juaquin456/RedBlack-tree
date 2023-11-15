#include <stdio.h>
#include "RB.h"
int main() {
    struct RB_tree tree;
    init_tree(&tree);
    struct thread t1;
    t1.recent_cpu = 30;

    struct thread t2;
    t2.recent_cpu = 31;

    struct thread t3;
    t3.recent_cpu = 0;

    struct thread t4;
    t4.recent_cpu = 31;

    struct thread t5;
    t5.recent_cpu = 27;


    struct thread t6;
    t6.recent_cpu = 31;


    struct thread t7;
    t7.recent_cpu = 31;

    insert(&tree, &t1);
    insert(&tree, &t2);
    insert(&tree, &t3);
    insert(&tree, &t4);
    insert(&tree, &t5);
    insert(&tree, &t6);
    insert(&tree, &t7);
    //    printf("pop %d\n", pop_min(&tree)->priority);
//    insert(&tree, &t3);
    print(&tree);
    return 0;
}
