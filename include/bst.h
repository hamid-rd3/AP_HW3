#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <compare>
class BST {
public:
    class Node {
    public:
        Node(int value, Node* left, Node* right);
        Node() = default;
        Node(const Node& node);
        friend std::ostream& operator<<(std::ostream& os,const BST::Node & node );
        std::strong_ordering operator<=> (Node* &node )const;
        bool operator==(Node* &node )const;
        std::strong_ordering operator<=>(const int& N)const;
        bool operator==(const int & N)const;
        int value;
        Node* left;
        Node* right;
    };

private:
    Node* root;
};
#endif // BST_H