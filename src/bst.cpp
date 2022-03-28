#include "bst.h"
BST::Node::Node(int value,Node* left=nullptr,Node*right=nullptr){
this->value=value;
this->left=left;
this->right=right;

}
BST::Node::Node(const Node& node ):value{node.value},left{node.left},right{node.right}{
    
}