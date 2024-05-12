#include "Avltree.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Avltree::Node::Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}

int Avltree::height(Node *N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

int Avltree::max(int a, int b) {
    return (a > b) ? a : b;
}

Avltree::Node* Avltree::rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Εκτέλεση περιστροφής
    x->right = y;
    y->left = T2;

    // Ενημέρωση ύψους
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Avltree::Node* Avltree::leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Εκτέλεση περιστροφής
    y->left = x;
    x->right = T2;

    // Ενημέρωση ύψους
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int Avltree::getBalance(Node *N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

Avltree::Node* Avltree::insert(Node* node, int key) {
    if (node == nullptr)
        return(new Node(key));
    
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else 
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Avltree::Node* Avltree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Avltree::Node* Avltree::deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if ( key < root->key )
        root->left = deleteNode(root->left, key);
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
    else {
        if( (root->left == nullptr) || (root->right == nullptr) ) {
            Node *temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Avltree::Node* Avltree::search(Node* root, int key) {
    if (root == nullptr || root->key == key)
        return root;
    if (root->key < key)
        return search(root->right, key);
    return search(root->left, key);
}

int Avltree::size(Node* node) {
    if (node == nullptr)
        return 0;
    return 1 + size(node->left) + size(node->right);
}

Avltree::Avltree() : root(nullptr) {}

Avltree::Avltree(std::string& filename) : Avltree() {
    std::ifstream file(filename);
    int key;
    while (file >> key) {
        root = insert(root, key);
    }
}

int Avltree::getSize() {
    return size(root);
}

int Avltree::findMin() {
    Node* node = minValueNode(root);
    if (node == nullptr)
        throw std::runtime_error("The tree is empty.");
    return node->key;
}

std::string Avltree::search(int key) {
    Node* result = search(root, key);
    return result ? "SUCCESS" : "FAILURE";
}

void Avltree::insert(int key) {
    root = insert(root, key);
}

void Avltree::deleteAvl(int key) {
    root = deleteNode(root, key);
}