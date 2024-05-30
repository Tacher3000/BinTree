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
    Node(int value, int id); // Конструктор узла

    // Метод для сравнения узлов
    bool equals(Node* other);

    // Метод для получения размера поддерева
    size_t size();

    // Метод для получения идентификатора узла
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

    // Деструктор
    ~BinaryTree();

    // Метод для вставки нового значения в дерево (рекурсивный)
    void recursiveInsert(int value);

    // Метод для вставки нового значения в дерево (итеративный)
    void iterativInsert(int value);

    // Метод для случайной вставки значений в дерево
    void randomInsertion(int start, int end, int amount);

    // Метод для поиска поддеревьев с заданной структурой
    QList<Node*> findSubtrees(Node* subtree_structure);

    // Метод для записи узла в файл
    void writeNodeToFile(Node *node, QTextStream &out);

    // Метод для записи дерева в файл
    void writeTreeToFile(const QString &filename);

    // Рекурсивный метод для добавления узла в дерево
    void addNodeToTreeRecursive(Node *currentNode, Node *newNode);

    // Метод для добавления узла в дерево
    void addNodeToTree(Node *node);

    // Метод для чтения дерева из файла
    void readTreeFromFile(const QString &filename);

    // Метод для чтения дерева из текста
    void readTreeFromText(const QString &text);

    // Метод для вывода дерева в текстовый виджет
    void printTree(QTextEdit *textEdit);

    // Метод для получения корня дерева
    Node *getRoot();

    // Метод для получения размера дерева
    size_t size();

    // Метод для очистки дерева
    void clearTree(Node *node);

private:
    // Вспомогательный рекурсивный метод для вставки нового значения в дерево
    Node* m_recursiveInsertNode(int value, Node* node);

    // Вспомогательный итеративный метод для вставки нового значения в дерево
    Node* m_iterativInsertNode(int value, Node* node);

    // Вспомогательный рекурсивный метод для вывода дерева
    void m_printTreeRecursive(Node *node, const QString &prefix, bool isLast, QString &treeOutput);

    // Вспомогательный метод для поиска поддеревьев
    void m_findSubtrees(Node* node, Node* subtree_structure, QList<Node*>& result);

private:
    Node* root;

    int nodes_amount;
};

#endif // BINARYTREE_H
