#include "binarytree.h"

// Реализация методов класса Node

Node::Node(int value, int id) : value(value), id(id), left(nullptr), right(nullptr) {}

bool Node::equals(Node* other) {
    if (other == nullptr)
        return false;
    bool left_equal = (left && other->left) ? left->equals(other->left) : (left == other->left);
    bool right_equal = (right && other->right) ? right->equals(other->right) : (right == other->right);
    return left_equal && right_equal;
}

// Реализация методов класса BinaryTree

BinaryTree::BinaryTree() : root(nullptr), nodes_amount(0) {}

void BinaryTree::insert(int value) {
    root = _insert_node(value, root);
}

void BinaryTree::print_full_tree() {
    print_tree(root);
}

void BinaryTree::random_insertion(int start, int end, int amount) {
    QList<int> values;
    for (int i = 0; i < amount; ++i)
        values.append(QRandomGenerator::global()->bounded(start, end + 1));

    for (int value : values)
        insert(value);
}

QList<Node*> BinaryTree::find_subtrees(Node* subtree_structure) {
    QList<Node*> result;
    dfs(root, subtree_structure, result);
    return result;
}

void BinaryTree::read_tree_from_dict(QVariantMap tree_dict) {

}



Node* BinaryTree::_insert_node(int value, Node* node) {
    if (node == nullptr) {
        nodes_amount++;
        return new Node(value, nodes_amount);
    }

    if (QRandomGenerator::global()->bounded(2)) {
        node->left = _insert_node(value, node->left);
    } else {
        node->right = _insert_node(value, node->right);
    }
    return node;
}

void BinaryTree::print_tree(Node* node, QString indent) {
    if (node != nullptr) {
        qDebug().noquote() << indent + QString::number(node->value);
        print_tree(node->left, indent + "  ");
        print_tree(node->right, indent + "  ");
    }
}

void BinaryTree::dfs(Node* node, Node* subtree_structure, QList<Node*>& result) {
    if (node == nullptr)
        return;

    if (node->equals(subtree_structure))
        result.append(node);

    dfs(node->left, subtree_structure, result);
    dfs(node->right, subtree_structure, result);
}
