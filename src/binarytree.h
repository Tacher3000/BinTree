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
#include <QFile>
#include <QTextEdit>

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
    void recursiveInsert(int value);

    void iterativInsert(int value);

    // Метод для случайной вставки значений в дерево
    void random_insertion(int start, int end, int amount);

    // Метод для поиска поддеревьев с заданной структурой
    QList<Node*> find_subtrees(Node* subtree_structure);


    // Вспомогательный метод для рекурсивной вставки узла в дерево
    Node* m_recursiveInsertNode(int value, Node* node);

    Node* m_iterativInsertNode(int value, Node* node);


    // Вспомогательный метод для поиска поддеревьев с заданной структурой (рекурсивный)
    void dfs(Node* node, Node* subtree_structure, QList<Node*>& result);

// private:
    // Корневой узел дерева
    Node* root;

    // Количество узлов в дереве
    int nodes_amount;

    void write_node_to_file(Node *node, QTextStream &out);
    void write_tree_to_file(const QString &filename);


    void addNodeToTreeRecursive(Node *currentNode, Node *newNode);
    void addNodeToTree(Node *node);
    void read_tree_from_file(const QString &filename);
    void read_tree_from_text(const QString &text);
    void printTree(QTextEdit *textEdit);
    void printTreeRecursive(Node *node, const QString &prefix, bool isLast, QString &treeOutput);
};

#endif // BINARYTREE_H
