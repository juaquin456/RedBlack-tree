//
// Created by juaquin on 11/2/23.
//

#ifndef RB_TREE_RB_H
#define RB_TREE_RB_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct RB_tree {
    struct RB_node* root;
};

struct RB_node {
    struct RB_node* left;
    struct RB_node* right;
    struct RB_node* parent;
    bool color;
    int value;
};

void init(struct RB_tree* tree) {
    tree->root = NULL;
}

struct RB_node* new_node(int value) {
    struct RB_node* node = (struct RB_node*) malloc(sizeof(struct RB_node));
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->color = true;
    node->value = value;
    return node;
}

void _print(struct RB_node* node, int level) {
    if (node->right) {
        _print(node->right, level + 1);
    }
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%d\n", node->value);
    if (node->left) {
        _print(node->left, level + 1);
    }
}

void print(struct RB_tree* tree) {
    if (tree->root == NULL) {
        printf("Empty tree\n");
    }
    else {
        _print(tree->root, 0);
    }
}

bool is_black(struct RB_node* node) {
    if (node == NULL) {
        return true;
    }
    else {
        return !node->color;
    }
}

void left_rotate(struct RB_tree* tree, struct RB_node* node) {
    printf("left rotate\n");
    struct RB_node* right = node->right;
    node->right = right->left;
    if (right->left)
        right->left->parent = node;
    if (!node->parent)
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
    printf("right rotate\n");
    struct RB_node* left = node->left;
    node->left = left->right;
    if (left->right)
        left->right->parent = node;
    if (!node->parent)
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
    while (!is_black(new_node->parent)) {
        if (new_node->parent == new_node->parent->parent->left) {
            tmp = new_node->parent->parent->right;

            if (!is_black(tmp)) { // CASE 1
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
            if (!is_black(tmp)) {
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

struct RB_node* find_parent(struct RB_node* initial, struct RB_node* finding) {
    struct RB_node* parent = NULL;
    while (initial) {
        parent = initial;
        if (finding->value < initial->value) {
            initial = initial->left;
        }
        else {
            initial = initial->right;
        }
    }
    return parent;
}

void insert(struct RB_tree* tree, int value) {
    struct RB_node* nn = new_node(value);

    if (tree->root == NULL) {
        tree->root = nn;
        nn->color = false;
    }
    else {
        struct RB_node* parent = find_parent(tree->root, nn);

        nn->parent = parent;
        if (nn->value < parent->value)
            parent->left = nn;
        else
            parent->right = nn;

        if (nn->parent->parent)
            insert_fix(tree, nn);
    }
}

void delete_fix(struct RB_tree *pTree, struct RB_node *pNode);

struct RB_node* pop_min(struct RB_tree* tree) {
    struct RB_node* min = tree->root;
    while (min->left) {
        min = min->left;
    }
    if (min->parent) {
        min->parent->left = min->right;
    }
    else {
        tree->root = min->right;
    }
    if (min->right) {
        min->right->parent = min->parent;
    }
    if (is_black(min))
        delete_fix(tree, min);

    return min;
}

/*Delete fix function only for the case for popping minimum*/
void delete_fix(struct RB_tree *pTree, struct RB_node *pNode) {
    // TODO
}


#endif //RB_TREE_RB_H
