#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <QList>
#include <QMap>
#include <QVariant>
#include <QDebug>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QtMath>

// Определение класса Node, представляющего узел бинарного дерева
class Node {
public:
    Node(int value, int id);

    // Метод для сравнения узлов

    bool equals(Node* other);
    int value;
    int id;
    Node* left;
    Node* right;
};

// Определение класса BinaryTree, представляющего бинарное дерево
class BinaryTree {
public:
    // Конструктор
    BinaryTree();

    // Метод для вставки нового значения в дерево
    void insert(int value);

    // Метод для печати всего дерева
    void print_full_tree();

    // Метод для случайной вставки значений в дерево
    void random_insertion(int start, int end, int amount);

    // Метод для поиска поддеревьев с заданной структурой
    QList<Node*> find_subtrees(Node* subtree_structure);

    // Метод для чтения дерева из словаря
    void read_tree_from_dict(QVariantMap tree_dict);
    // Вспомогательный метод для рекурсивной вставки узла в дерево
    Node* _insert_node(int value, Node* node);

    // Вспомогательный метод для печати дерева (рекурсивный)
    void print_tree(Node* node, QString indent = "");

    // Вспомогательный метод для поиска поддеревьев с заданной структурой (рекурсивный)
    void dfs(Node* node, Node* subtree_structure, QList<Node*>& result);

// private:
    // Корневой узел дерева
    Node* root;

    // Количество узлов в дереве
    int nodes_amount;
};

#endif // BINARYTREE_H
