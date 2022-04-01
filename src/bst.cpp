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

BST::BST(const BST& bst)
{
    if (bst.root == nullptr)
        root = new Node {};
    else {
        root = new Node { (bst.get_root())->value, nullptr, nullptr };
        std::queue<Node*> qu;
        if (bst.root != nullptr) {
            qu.push(bst.root);
            while (!qu.empty()) {
                Node* t = qu.front();
                this->add_node(t->value);
                qu.pop();
                if (t->left != nullptr)
                    qu.push(t->left);
                if (t->right != nullptr)
                    qu.push(t->right);
            }
        }
    }
}

BST::BST(BST&& bst)
    : root { bst.root }
{
    bst.root = nullptr;
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
    Node* node = new Node { value, nullptr, nullptr };
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

BST::Node** BST::find_node(int value)
{
    if (root == nullptr) {
        return nullptr;
    }
    Node** tmp = new Node* { root };
    while ((*tmp) != nullptr) {
        if ((*tmp)->value == value)
            return tmp;
        else if (value < (*tmp)->value) {
            (*tmp) = (*tmp)->left;
        } else {
            (*tmp) = (*tmp)->right;
        }
    }
    return nullptr;
}

BST::Node** BST::find_parrent(int value)
{
    if (root == nullptr) {
        return nullptr;
    }
    Node** tmp = new Node* { root };
    while ((*tmp) != nullptr) {
        if ((*tmp)->left->value == value || (*tmp)->right->value == value)
            return tmp;
        else if ((*tmp)->value > value)
            (*tmp) = (*tmp)->left;
        else {
            (*tmp) = (*tmp)->right;
        }
    }
    return nullptr;
}

BST::Node** BST::find_successor(int value)
{
    if (root == nullptr)
        return nullptr;
    Node** tmp = new Node* { *(this->find_node(value)) };
    if ((*tmp) == nullptr || (*tmp)->left == nullptr)
        return tmp;
    else {
        (*tmp) = (*tmp)->left;
        while (true) {
            if ((*tmp)->right == nullptr)
                return tmp;
            (*tmp) = (*tmp)->right;
        }
    }
    return nullptr;
}

bool BST::delete_node(int value)
{

    //  std::queue<Node**> qu;
    // // // root->left->left->right->right=nullptr;
    // qu.push(&(root->left->left->right->right));
    // Node** node =qu.back();
    //  *(node)=nullptr;
    //  Node* &node = qu.back();
    //  qu.push(node->left);
    //  node=&qu.back();
    //  qu.push((*node)->left);
    //  node=&qu.back();
    //  qu.push((*node)->right);
    //    node=&qu.back();
    // qu.push((*node)->right);
    //    node=&qu.back();
    // std::cout << **node << std::endl;
    // (*node)=nullptr;

    if (this->find_node(value) == nullptr)
        return 0;
    else {
        std::queue<Node**> qu;
        qu.push(&root);
        Node** node =qu.back();
        while (true) {
            if ((*node)->value == value)
                break;
            else if (&(*node)->left != nullptr
                && value < (*node)->value) {
                qu.push(&((*node)->left));
                node = qu.back();
            } else if (&((*node)->right) != nullptr
                && value > (*node)->value){
                qu.push(&((*node)->right));
                node = qu.back();}
            // node must be updated to newst qu.back()
        }
        // qu.back() is node of given value in BST
        // leaf    
        if ((*node)->left == nullptr && (*node)->right == nullptr) {
            (*node) = nullptr;
            return 1;
            // edge
        } else if ((*node)->left == nullptr) {
            (*node) = (*node)->right;
            return 1;
        } else if ((*node)->right == nullptr) {
            (*node) = (*node)->left;
            return 1;
            // two children
        } else {
            Node* tmp=*node;
            qu.push(&((*node)->left));
            while (true) {
                node = qu.back();
                if ((*node)->right == nullptr) {
                    tmp->value=(*node)->value;
                    (*node)=nullptr;
                    break;
                }
                qu.push(&(*node)->right);
            }
            

        }
    }
     
    return 0;
}

BST::~BST()
{
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
    for (auto& node : nodes)
        delete node;
}

std::ostream& operator<<(std::ostream& os, const BST& bst)
{
    std::queue<BST::Node*> qu;
    os << std::string(80, '*') << std::endl;
    if (bst.root != nullptr) {
        qu.push(bst.root);
        while (!qu.empty()) {
            BST::Node* t = qu.front();
            os << std::left << std::setw(17) << qu.front() << "=> value:"
               << std::setw(10) << qu.front()->value << "left:"
               << std::setw(16) << qu.front()->left << "right:"
               << qu.front()->right << std::endl;
            qu.pop();
            if (t->left != nullptr)
                qu.push(t->left);
            if (t->right != nullptr)
                qu.push(t->right);
        }
    }
    os << std::string(80, '*') << std::endl;
    os << "binary search tree size: " << bst.length() << std::endl;
    return os;
}
