#ifndef BST_H
#define BST_H
#include <iostream>

class BST{
    public:
    class Node {
    public:
        Node(int value ,Node* left,Node* right);
        int value;
        Node* left;
        Node* right;
    };

    private:
    Node *root;
};

#endif //BST_H