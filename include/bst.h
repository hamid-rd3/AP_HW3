#ifndef BST_H
#define BST_H
#include <compare>
#include <iostream>
#include <string>
#include <functional>
#include <queue>
#include <iomanip>
#include <vector>
#include <stdlib.h>
class BST {
public:
    class Node {
    public:
        Node(int value, Node* left, Node* right);
        Node() = default;
        Node(const Node& node);
        friend std::ostream& operator<<(std::ostream& os,
            const BST::Node& node);
        std::strong_ordering operator<=>(Node*& node) const;
        bool operator==(Node*& node) const;
        std::strong_ordering operator<=>(const int& N) const;
        bool operator==(const int& N) const;
        int value;
        Node* left;
        Node* right;
    };
    Node* const& get_root() const;
    void bfs(std::function<void(Node*& node)> func)const;
    bool add_node(int value);
    size_t length()const;
    friend std::ostream& operator<<(std::ostream& os,const BST& bst);
private:
    Node* root;
};
#endif // BST_H