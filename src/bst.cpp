#include "bst.h"
BST::Node::Node(int value, Node* left, Node* right)
{
    this->value = value;
    this->left = left;
    this->right = right;
}

BST::Node::Node(const Node& node)
    : value { node.value }
    , left { node.left }
    , right { node.right }
{
}

std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{
    os << "address of node : " << &node << "  -  "
       << " value in node : " << node.value << "  -  "
       << " address of left child : " << &node.left << "  -  "
       << " address of right child : " << &node.right;

    return os;
}

std::strong_ordering BST::Node::operator<=>(Node*& node) const
{
    return value <=> node->value;
}

bool BST::Node::operator==(Node*& node) const
{
    return value == node->value;
}

std::strong_ordering BST::Node::operator<=>(const int& N) const
{
    return value <=> N;
}

bool BST::Node::operator==(const int& N) const
{
    return value == N;
}

BST::Node* const& BST::get_root() const
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func) const
{
    std::queue<Node*> qu;
    if (root != nullptr) {
        qu.push(root);
        while (!qu.empty()) {
            Node* t = qu.front();
            func(t);
            qu.pop();
            if (t->left != nullptr)
                qu.push(t->left);
            if (t->right != nullptr)
                qu.push(t->right);
        }
    }
}
bool BST::add_node(int value)
{
    Node* node = new BST::Node { value, nullptr, nullptr };
    if (root == nullptr) {
        root = node;
        return 1;
    }
    Node* tmp = root;
    while (tmp != nullptr) {
        if (tmp->value == node->value)
            return 0;
        // no duplicates allowed
        else if (node->value < tmp->value && tmp->left == nullptr) {
            tmp->left = node;
            return 1;
            // value inserted in left child
        } else if (node->value < tmp->value) {
            tmp = tmp->left;
            // go to left child
        } else if (node->value > tmp->value && tmp->right == nullptr) {
            tmp->right = node;
            return 1;
            // value inserted in right child
        } else {
            tmp = tmp->right;
            // fo to right child
        }
    }
    return 1; // not essential return (just to avoid warning !)
}

size_t BST::length() const
{
    std::vector<int> v;
    this->bfs([&v](Node*& node) { v.push_back(node->value); });
    return v.size();
}

std::ostream& operator<<(std::ostream& os, const BST& bst)
{
    std::vector<int> v;
    bst.bfs([&v](BST::Node*& node) { v.push_back(node->value); });
    os << std::string(80, '*') << std::endl;
    for (size_t i{};i<v.size();i++) {
        os <<std::left<<std::setw(17)<< &v[i]  << "=> value:"
                  << std::setw(10)<< v[i] << "left:"
                  << std::setw(16)<< &v[i-1] << "right:"
                  << &v[i+1] << std::endl;
    }
    os<<"binary search tree size: "<<v.size()<<std::endl;
    os << std::string(80, '*') << std::endl;
    return os;
}