#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <fstream>
#include <string>

class Avltree {

  private:

    struct Node {
        int key;
        Node *left;
        Node *right;
        int height;

        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node *root;

    int height(Node *N);

    int max(int a, int b);

    Node* rightRotate(Node *y);

    Node* leftRotate(Node *x);

    int getBalance(Node *N);

    Node* insert(Node* node, int key);

    Node* minValueNode(Node* node);

    Node* deleteNode(Node* root, int key);

    Node* search(Node* root, int key);

    int size(Node* node);

  public:

    Avltree();

    Avltree(std::string& filename);

    int getSize();

    int findMin();

    std::string search(int key);

    void insert(int key);

    void deleteAvl(int key);
};

#endif //AVLTREE_H