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
#include <QElapsedTimer>

// Определение класса Node, представляющего узел бинарного дерева
class Node {
public:
    Node(int value, int id);

    // Метод для сравнения узлов
    bool equals(Node* other);

    // метод для
    size_t size();

    int getId();

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

    ~BinaryTree();

    // Метод для вставки нового значения в дерево
    void recursiveInsert(int value);

    // Метод для вставки нового значения в дерево
    void iterativInsert(int value);

    // Метод для случайной вставки значений в дерево
    void randomInsertion(int start, int end, int amount);

    // Метод для поиска поддеревьев с заданной структурой
    QList<Node*> findSubtrees(Node* subtree_structure);

    void writeNodeToFile(Node *node, QTextStream &out);

    void writeTreeToFile(const QString &filename);

    void addNodeToTreeRecursive(Node *currentNode, Node *newNode);

    void addNodeToTree(Node *node);

    void readTreeFromFile(const QString &filename);

    void readTreeFromText(const QString &text);

    void printTree(QTextEdit *textEdit);

    Node *getRoot();

    size_t size();

    void clearTree(Node *node);
private:
    Node* m_recursiveInsertNode(int value, Node* node);

    Node* m_iterativInsertNode(int value, Node* node);

    void m_printTreeRecursive(Node *node, const QString &prefix, bool isLast, QString &treeOutput);

    void m_findSubtrees(Node* node, Node* subtree_structure, QList<Node*>& result);

private:
    Node* root;

    int nodes_amount;
};

#endif // BINARYTREE_H
