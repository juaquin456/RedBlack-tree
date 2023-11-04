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

void left_rotate(struct RB_node* node) {
    printf("left rotate\n");
    struct RB_node* parent = node->parent;
    struct RB_node* left = node->left;
    node->parent = parent->parent;
    node->left = parent;
    parent->right = left;
}

void right_rotate(struct RB_node* node) {
    printf("right rotate\n");
    struct RB_node* parent = node->parent;
    struct RB_node* right = node->right;
    node->parent = parent->parent;
    node->right = parent;
    parent->left = right;
}

void flip(struct RB_node* node) {
    node->color = !node->color;
    if (node->left)
        node->left->color = !node->left->color;
    if (node->right)
        node->right->color = !node->right->color;
}

struct RB_node* _insert(struct RB_node* node, int value) {
    if (node->value > value) {
        if (node->left) {
            node->left = _insert(node->left, value);
        }
        else {
            node->left = (struct RB_node *) malloc(sizeof(struct RB_node));
            node->left->left = NULL;
            node->left->right = NULL;
            node->left->color = true;
            node->left->value = value;
            node->left->parent = node;
            if (!is_black(node) & !is_black(node->left)) {
                if (is_black(node->parent->right)) {
                    right_rotate(node);
                    return node;
                }
                else {
                    flip(node);
                }
            }
        }
    }
    else {
        if (node->right) {
            node->right = _insert(node->right, value);
        }
        else {
            node->right = (struct RB_node *) malloc(sizeof(struct RB_node));
            node->right->left = NULL;
            node->right->right = NULL;
            node->right->color = true;
            node->right->value = value;
            node->right->parent = node;
            if (!is_black(node) & !is_black(node->right)) {
                if (is_black(node->parent->left)) {
                    left_rotate(node);
                    return node;
                }
                else {
                    flip(node);
                }
            }
        }
    }
    return node;
}

void insert(struct RB_tree* tree, int value) {
    if (tree->root == NULL) {
        tree->root = (struct RB_node*) malloc(sizeof(struct RB_node));
        tree->root->left = NULL;
        tree->root->right = NULL;
        tree->root->color = false;
        tree->root->value = value;
        tree->root->parent = NULL;
    }
    else {
        tree->root = _insert(tree->root, value);
    }
}




#endif //RB_TREE_RB_H
