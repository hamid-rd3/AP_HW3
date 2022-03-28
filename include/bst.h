#ifndef BST_H
#define BST_H
#include <iostream>

class BST{
    public:
    class Node {
    public:
        Node(int value ,Node* left,Node* right);
        Node()=default;
        Node(const Node& node);
        int value;
        Node* left;
        Node* right;
    };

    private:
    Node *root;
};

#endif //BST_H