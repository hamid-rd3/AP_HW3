#include "bst.h"
BST::Node::Node(int value, Node* left , Node* right )
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

void BST::bfs (std::function <void(Node* & node)> func){


}

bool BST::add_node(int value){
     BST::Node* node = new BST::Node{value,nullptr,nullptr} ;
     if(root==nullptr){
        root=node;
        return 1;
    }
    BST::Node* tmp=root;
    while(tmp!= nullptr){
    if(tmp->value==node->value)
        return 0;
        //no duplicates allowed 
    else if(node->value<tmp->value && tmp->left==nullptr){
        tmp->left=node;
        return 1;
        //value inserted in left child
    }
    else if(node->value <tmp->value){
        tmp=tmp->left;
        // go to left child 
    }
    else if (node->value >tmp->value && tmp->right==nullptr){
        tmp->right=node;
        return  1;
        //value inserted in right child
    }
    else {
        tmp=tmp->right;
        //fo to right child
    }
    }
    return 1;//not essential return (just to avoid warning !) 
}