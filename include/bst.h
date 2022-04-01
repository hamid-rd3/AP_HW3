#ifndef BST_H
#define BST_H
#include <compare>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <string>
#include <vector>
#include <initializer_list>
class BST {
public:
    class Node {
    public:
        Node(int value, Node* left, Node* right);
        Node();
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
    BST(std::initializer_list <int > list);
    BST() = default;
    BST(const BST& bst);
    BST(BST&& bst);
    ~BST();
    Node* const& get_root() const;
    void bfs(std::function<void(Node*& node)> func) const;
    bool add_node(int value);
    size_t length() const;
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    const BST operator++() const;
    const BST operator++(int) const;
    BST operator=(const BST& bst);
    BST operator=(BST&& bst);
    friend std::ostream& operator<<(std::ostream& os, const BST& bst);

private:
    Node* root;
};
#endif // BST_H