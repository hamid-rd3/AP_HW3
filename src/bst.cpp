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
    if(bst.root==nullptr)
        root=new Node{};
    else{
    root = new Node{(bst.get_root())->value,nullptr,nullptr};
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
    }}
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

BST::Node** BST::find_node(int value)
{
    if (root == nullptr) {
        return nullptr;
    }
    if (root->value == value)
        return &root;
    else if (value < root->value) {
        this->root = root->left;
        return this->find_node(value);
    } else {
        // value>root->value;
        this->root = root->right;
        return this->find_node(value);
    }
}

BST::Node** BST::find_parrent(int value)
{
    if (root == nullptr) {
        return nullptr;
    }
    if (root->left->value == value || root->right->value == value)
        return &root;
    else if (value < root->value) {
        root = root->left;
        return this->find_parrent(value);
    } else {
        root = root->right;
        return this->find_parrent(value);
    }
}

BST::Node** BST::find_successor(int value)
{
    if (root == nullptr)
        return nullptr;
    if (root->left == nullptr)
        return &root;
    else {
        root = *this->find_node(value);
        root = root->left;
        while (root->right != nullptr) {
            root = root->right;
        }
        return &root;
    }
}

bool BST::delete_node(int value)
{
    if (this->find_node(value) == nullptr) {
        return 0;
    } else {

        Node* tmp = *this->find_node(value);
        if (tmp->left == nullptr && tmp->right == nullptr) {
            delete[] tmp;
        }

        // else if(root->left==nullptr){
        //     Node* tmp=root;

        //     delete[] root;
        //     root=tmp->right;
        //     tmp=nullptr;
        // }
        // else if(root->right==nullptr){
        //     Node* tmp=root;
        //     delete[] root;
        //     root=tmp->left;
        // }
        // else {
        //     auto successor=*this->find_successor(value);
        //     root->value=(successor)->value;
        //     delete[] successor;
        // }
    }

    return 1;
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
