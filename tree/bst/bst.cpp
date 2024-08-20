#include <bits/stdc++.h>

using namespace std;

struct Node {
    int element;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int element) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->element = element;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insertNode(struct Node** tree, struct Node* node) {
    if (!(*tree)) {
        *tree = node;
    } else if ((*tree)->element > node->element) {
        insertNode(&(*tree)->left, node);
    } else {
        insertNode(&(*tree)->right, node);
    }
}

void insert(struct Node** tree, int element) {
    struct Node* node = createNode(element);
    insertNode(tree, node);
}

int level(struct Node* tree, struct Node* node) {
    int level = 0;
    struct Node* curr = tree;
    while (curr != node) {
        if (curr->element < node->element) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }
        level++;
    }
    return level;
}

void height_r(struct Node* tree, int *max_height, int height) {
    if (!tree->left && !tree->right) {
        if (*max_height < height) {
            *max_height = height;
            return;
        }
    }
    if (tree->left) {
        height_r(tree->left, max_height, height+1);
    }
    if (tree->right) {
        height_r(tree->right, max_height, height+1);
    }
}

int height(struct Node* tree) {
    int h = -1;
    height_r(tree, &h, 0);
    return h;
}

void getNodesInLevel(struct Node* tree, int L, int l, queue<struct Node*>* nodes)
{
    if (L == l) {
        nodes->push(tree);
    } else {
        if (tree->left) {
            getNodesInLevel(tree->left, L, l+1, nodes);
        } else {
            nodes->push(NULL);
        }
        if (tree->right) {
            getNodesInLevel(tree->right, L, l+1, nodes);
        } else {
            nodes->push(NULL);
        }
    }
}

void printTreeWithLevel(struct Node* tree, int height, int level) {
    if (!tree) {
        return;
    }
    for (int i = 0; i < height-level; i++) {
        cout << "    ";
    }
    queue<struct Node*> nodes;
    getNodesInLevel(tree, level, 0, &nodes);
    while (nodes.size() > 1) {
        if (nodes.front()) {
            cout << nodes.front()->element;
        }
        cout << "        ";
        nodes.pop();
    }
    cout << nodes.front()->element << endl;
    nodes.pop();
}

void printTree(struct Node* tree) {
    int h = height(tree);
    for (int i = 0; i <= h; i++) {
        printTreeWithLevel(tree, h, i);
    }
}

int main() {
    struct Node* tree = NULL;
    insert(&tree, 8);
    insert(&tree, 5);
    insert(&tree, 12);
    insert(&tree, 2);
    insert(&tree, 7);
    insert(&tree, 16);
    insert(&tree, 6);
    insert(&tree, 13);
    insert(&tree, 20);
    cout << "height: " << height(tree) << endl;
    printTree(tree);
    return 0;
}
