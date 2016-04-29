/*
 * CSCI-2421: Data Structures and Program Design
 * University of Colorado Denver
 * AVL Tree Base Implementation.
 */
#include "AVLNode.h"

AVLNode::AVLNode() : data() {
    this->balance = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

AVLNode::AVLNode(ItemType data, AVLNode* parent) {
    this->data = data;
    this->balance = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = parent;
}

AVLNode::AVLNode(ItemType data, AVLNode* left, AVLNode* right) {
    this->data = data;
    this->balance = 0;
    this->left = left;
    this->right = right;
    this->parent = nullptr;
}

AVLNode::AVLNode(ItemType data, AVLNode* left, AVLNode* right, int balance) {
    this->data = data;
    this->balance = balance;
    this->left = left;
    this->right = right;
    this->parent = nullptr;
}

AVLNode::~AVLNode() {
    if (this->left != nullptr)
        delete this->left;
    if (this->right != nullptr)
        delete this->right;
}

void AVLNode::setData(ItemType data) {
    this->data = data;
}

void AVLNode::setBalance(int bal) {
    this->balance = bal;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

ItemType AVLNode::getData() const {
    return this->data;
}

int AVLNode::getBalance() const {
    return this->balance;
}

const AVLNode* const AVLNode::getLeft() const {
    return this->left;
}

const AVLNode* const AVLNode::getRight() const {
    return this->right;
}

bool AVLNode::operator < (const AVLNode& AVLNode) const {
    return (this->data < AVLNode.data);
    //if ( this->data < AVLNode.data ) return true;
    //return false;
}

std::ostream& operator << (std::ostream& out, const AVLNode& AVLNode) {
    out << AVLNode.data;
    return out;
}
