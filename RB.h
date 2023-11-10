//
// Created by juaquin on 11/2/23.
//

#ifndef RB_TREE_RB_H
#define RB_TREE_RB_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct RB_node {
    struct RB_node* left;
    struct RB_node* right;
    struct RB_node* parent;
    bool color;
    struct thread* t;
};

struct RB_tree {
    struct RB_node* root;
    int size;
    struct RB_node NILL;
};

struct thread {
          /* Saved stack pointer. */
    int priority;              /* Priority. */
    int nice;
    int recent_cpu;
    struct RB_node elem_node;
};

void init_node(struct RB_tree* tree,struct RB_node* node, struct thread* t) {
    node->left = &tree->NILL;
    node->right = &tree->NILL;
    node->parent = &tree->NILL;
    node->color = true;
    node->t = t;
}

void init_tree(struct RB_tree* tree) {
    init_node(tree, &tree->NILL, NULL);
    tree->NILL.color = false;
    tree->root = &tree->NILL;
    tree->size = 0;
}

void _print(struct RB_tree* tree, struct RB_node* node, int level) {
    if (node->right != &tree->NILL) {
        _print(tree, node->right, level + 1);
    }
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%d\n", node->t->priority);
    if (node->left != &tree->NILL) {
        _print(tree, node->left, level + 1);
    }
}

void print(struct RB_tree* tree) {
    if (tree->root == &tree->NILL) {
        printf("Empty tree\n");
    }
    else {
        _print(tree, tree->root, 0);
        printf("\n");
    }
}

bool is_black(struct RB_tree* tree, struct RB_node* node) {
    if (node == &tree->NILL) {
        return true;
    }
    else {
        return !node->color;
    }
}

void left_rotate(struct RB_tree* tree, struct RB_node* node) {
    struct RB_node* right = node->right;
    node->right = right->left;
    if (right->left != &tree->NILL)
        right->left->parent = node;
    if (node->parent == &tree->NILL)
        tree->root = right;
    else if (node->parent->left == node)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->parent = node->parent;
    right->left = node;
    node->parent = right;
}

void right_rotate(struct RB_tree* tree, struct RB_node* node) {
    struct RB_node* left = node->left;
    node->left = left->right;
    if (left->right != &tree->NILL)
        left->right->parent = node;
    if (node->parent == &tree->NILL)
        tree->root = left;
    else if (node->parent->left == node)
        node->parent->left = left;
    else
        node->parent->right = left;
    left->parent = node->parent;
    left->right = node;
    node->parent = left;
}

void insert_fix(struct RB_tree* tree, struct RB_node* new_node) {
    struct RB_node* tmp;
    while (!is_black(tree, new_node->parent)) {
        if (new_node->parent == new_node->parent->parent->left) {
            tmp = new_node->parent->parent->right;

            if (!is_black(tree, tmp)) { // CASE 1
                tmp->color = 0;
                new_node->parent->color = 0;
                new_node->parent->parent->color = 1;
                new_node = new_node->parent->parent;
            } else {
                // CASE 2
                if (new_node == new_node->parent->right) {
                    new_node = new_node->parent;
                    left_rotate(tree, new_node);
                }

                // CASE 3
                new_node->parent->color = 0;
                new_node->parent->parent->color = 1;
                right_rotate(tree, new_node->parent->parent);
            }
        } else {
            tmp = new_node->parent->parent->left;
            if (!is_black(tree, tmp)) {
                tmp->color = 0;
                new_node->parent->color = 0;
                new_node->parent->parent->color = 1;
                new_node = new_node->parent->parent;
            } else {
                if (new_node == new_node->parent->left) {
                    new_node = new_node->parent;
                    right_rotate(tree, new_node);
                }
                new_node->parent->color = 0;
                new_node->parent->parent->color = 1;
                left_rotate(tree, new_node->parent->parent);
            }
        }
    }
    tree->root->color = 0;
}

struct RB_node* find_parent(struct RB_tree* tree, struct RB_node* initial, struct RB_node* finding) {
    struct RB_node* parent = &tree->NILL;
    while (initial != &tree->NILL) {
        parent = initial;
        if (finding->t->priority > initial->t->priority) {
            initial = initial->left;
        }
        else {
            initial = initial->right;
        }
    }
    return parent;
}

void insert(struct RB_tree* tree, struct thread* t) {
    init_node(tree, &t->elem_node, t);
    tree->size++;
    if (tree->root == &tree->NILL) {
        tree->root = &t->elem_node;
        (&t->elem_node)->color = false;
    }
    else {
        struct RB_node* parent = find_parent(tree, tree->root, &t->elem_node);

        (&t->elem_node)->parent = parent;
        if ((&t->elem_node)->t->priority > parent->t->priority)
            parent->left = (&t->elem_node);
        else
            parent->right = (&t->elem_node);

        // printf("%d\n", parent == &tree->NILL);
        if ((&t->elem_node)->parent->parent)
            insert_fix(tree, (&t->elem_node));
    }
}

void delete_fix(struct RB_tree *pTree, struct RB_node *pNode) {
    while ((pNode != pTree->root) & is_black(pTree, pNode)) {
        if (pNode == pNode->parent->left) {
            struct RB_node *w = pNode->parent->right;
            if (!is_black(pTree, w)) {
                w->color = 0;
                pNode->parent->color = 1;
                left_rotate(pTree, pNode->parent);
                w = pNode->parent->right;
            }
            if (is_black(pTree, w->left) & is_black(pTree, w->right)) {
                w->color = 1;
                pNode = pNode->parent;
            } else {
                if (is_black(pTree, w->right)) {
                    w->left->color = 0;
                    w->color = 1;
                    right_rotate(pTree, w);
                    w = pNode->parent->right;
                }
                w->color = pNode->parent->color;
                pNode->parent->color = 0;
                w->right->color = 0;
                left_rotate(pTree, pNode->parent);
                pNode = pTree->root;
            }
        } else {
            struct RB_node *w = pNode->parent->left;
            if (!is_black(pTree, w)) {
                w->color = 0;
                pNode->parent->color = 1;
                right_rotate(pTree, pNode->parent);
                w = pNode->parent->left;
            }
            if (is_black(pTree, w->left) & is_black(pTree, w->right)) {
                w->color = 1;
                pNode = pNode->parent;
            } else {
                if (is_black(pTree, w->left)) {
                    w->right->color = 0;
                    w->color = 1;
                    left_rotate(pTree, w);
                    w = pNode->parent->left;
                }
                w->color = pNode->parent->color;
                pNode->parent->color = 0;
                w->left->color = 0;
                right_rotate(pTree, pNode->parent);
                pNode = pTree->root;
            }
        }
    }
    pNode->color = 0;
}

void transplant(struct RB_tree* tree, struct RB_node* u, struct RB_node* v) {
    if (u->parent == &tree->NILL)
        tree->root = v;
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if (v != &tree->NILL)
        v->parent = u->parent;
}

void delete(struct RB_tree* tree, struct RB_node* node) {
    struct RB_node* y = node;
    struct RB_node* x;
    bool y_original_color = y->color;
    if (node->left == &tree->NILL) {
        x = node->right;
        transplant(tree, node, node->right);
    }
    else if (node->right == &tree->NILL) {
        x = node->left;
        transplant(tree, node, node->left);
    }
    else {
        y_original_color = y->color;
        x = y->right;
        if (y != node->right) {
            transplant(tree, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        else
            x->parent = y;

        transplant(tree, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }
    if (y_original_color && (x != &tree->NILL)) {
        delete_fix(tree, x);
    }
}

struct thread* pop_min(struct RB_tree* tree) {
    tree->size--;
    struct RB_node* node = tree->root;
    while (node->left != &tree->NILL) {
        node = node->left;
    }
    struct thread* t = node->t;
    delete(tree, node);
    return t;
}
bool tree_empty(struct RB_tree* tree) {
    return tree->root == &tree->NILL;
}

struct thread* front(struct RB_tree* tree) {
    struct RB_node* node = tree->root;
    while (node->left != &tree->NILL) {
        node = node->left;
    }
    return node->t;
}

#endif //RB_TREE_RB_H
