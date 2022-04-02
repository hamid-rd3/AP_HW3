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

BST::Node::Node()
    : value { 0 }
{
    left = nullptr;
    right = nullptr;
}

std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{
    os << "address of node : " << &node << "  -  "
       << " value in node : " << node.value << "  -  "
       << " address of left child : " << node.left << "  -  "
       << " address of right child : " << node.right<<std::endl;
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
// class Node definition end 

BST::BST(std::initializer_list<int> list)
{
    root = new Node { *list.begin(), nullptr, nullptr };
    for (auto v : list) {
        this->add_node(v);
    }
}

BST::BST()
{
    root = nullptr;
}

BST::BST(const BST& bst)
{
    if (bst.root == nullptr) {
        root = nullptr;
    } else {
        root = new Node { (bst.get_root())->value, nullptr, nullptr };
        std::queue<Node*> qu;
        if (bst.root != nullptr) {
            qu.push(bst.root); // copy of root
            while (!qu.empty()) {
                Node* t = qu.front();
                this->add_node(t->value);
                qu.pop(); // go to next height
                if (t->left != nullptr) // first _copy of root->left added
                    qu.push(t->left);
                if (t->right != nullptr) // then _copy of root->right added
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


BST::Node* const& BST::get_root() const
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func) const
{
    std::queue<Node*> qu;
    if (root != nullptr) {
        // copy bt value of root
        qu.push(root);
        while (!qu.empty()) {
            Node* t = qu.front();
            func(t);
            // delete the oldest value of qu(qu-front)
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
    // using a container  to save rvalue node
    std::queue<Node**> qu;
    qu.push(&root);
    // pass by refrence of root
    Node** node = qu.back();
    while (true) {
        if ((*node)->value == value)
            break;
        else if ((*node)->left != nullptr
            && value < (*node)->value) {
            qu.push(&((*node)->left));
            qu.pop();
            node = qu.back();
        } else if ((*node)->right != nullptr
            && value > (*node)->value) {
            qu.push(&((*node)->right));
            qu.pop();
            node = qu.back();
        } else {
            // value wasnt existed in object
            return nullptr;
        }
    }
    return node;
}

BST::Node** BST::find_parrent(int value)
{
    if (root == nullptr || root->value == value) {
        return nullptr;
    }
    std::queue<Node**> qu;
    qu.push(&root);
    Node** node = qu.back();
    while (true) {
        if ((*node)->left != nullptr && (*node)->left->value == value)
            break;
        if ((*node)->right != nullptr && (*node)->right->value == value)
            break;
        else if ((*node)->left != nullptr
            && value < (*node)->value) {
            qu.push(&((*node)->left));
            qu.pop();
            node = qu.back();
        } else if ((*node)->right != nullptr
            && value > (*node)->value) {
            qu.push(&((*node)->right));
            qu.pop();
            node = qu.back();
        }
    }
    return node;
}

BST::Node** BST::find_successor(int value)
{
    if (root == nullptr)
        return nullptr;
    std::queue<Node**> qu;
    qu.push(this->find_node(value));
    Node** node = qu.back();
    if ((*node)->left == nullptr)
        return node;
    qu.push(&((*node)->left));
    qu.pop();
    while (true) {
        node = qu.back();
        if ((*node)->right == nullptr)
            break;
        qu.push(&(*node)->right);
        qu.pop();
    }
    return node;
}
bool BST::delete_node(int value)
{

    if (this->find_node(value) == nullptr)
        return 0;
    else {
        Node** node = this->find_node(value);
        // qu.back() is node of given value in BST
        // leaf
        if ((*node)->left == nullptr && (*node)->right == nullptr) {
            delete (*node);
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
            Node** tmp = this->find_successor(value);
            (*node)->value = (*tmp)->value;
            delete (*tmp);
            (*tmp) = nullptr;
        }
    }

    return 1;
}

const BST BST::operator++() const
{
    // left ++
    this->bfs([](BST::Node*& node) { node->value++; });
    return *this;
}

const BST BST::operator++(int) const
{
    // right ++
    const BST _bst = *this;
    ++*this;
    return _bst;
}

BST BST::operator=(const BST& bst)
{
    if (bst.root == nullptr)
        root = new Node {};
    if (this == &bst) {
        return *this;
    } else {
        delete root;
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
    return *this;
}

BST BST::operator=(BST&& bst)
{
    delete root;
    root = bst.root;
    bst.root = nullptr;
    return *this;
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
    //like bfs 
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
