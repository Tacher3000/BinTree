#ifndef TREEWINDOW_H
#define TREEWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVariantMap>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <memory>

#include "binarytree.h"
#include "scalablegraphicsview.h"

constexpr qreal NODE_WIDTH = 50;
constexpr qreal NODE_HEIGHT = 50;

class TreeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TreeWindow(QWidget *parent = nullptr);
    void randomInsertion(int start, int end, int amount);
    void enterTree();
signals:
    void clickedExit();
private slots:
    void exit();
    void reGen();
private:
    // Вычисляет ширину уровня в дереве
    qreal calculateLevelWidth(Node *node);
    // Добавляет узлы дерева на сцену
    void addNodesToScene(QGraphicsScene& scene, Node* node, qreal x, qreal y, qreal offsetY, qreal levelWidth);
private:
    std::unique_ptr<BinaryTree> m_tree;
    std::unique_ptr<QGraphicsScene> m_scene;
    std::unique_ptr<ScalableGraphicsView> m_view;

    QLabel m_quantityLabel;

    QPushButton *m_reGenButton;
    QPushButton *m_searchButton;
    QPushButton *m_exitButton;

    int m_start;
    int m_end;
    int m_quantity;
};

#endif // TREEWINDOW_H
