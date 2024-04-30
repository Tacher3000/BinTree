#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QScrollBar>
#include "mainwindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.showMaximized();
//     // Создаем бинарное дерево и добавляем в него случайные узлы
//     BinaryTree tree;
//     tree.random_insertion(1, 1000000, 1000);

//     // Вычисляем ширину первого уровня дерева
//     qreal levelWidth = calculateLevelWidth(tree.root);

//     // Создаем графическую сцену и добавляем на неё узлы дерева с динамическим распределением по горизонтали
//     QGraphicsScene scene;
//     addNodesToScene(scene, tree.root, 400, 50, 100, levelWidth);

//     ScalableGraphicsView view;
//     view.setWindowTitle("Графическое представление бинарного дерева");
//     view.setScene(&scene);
// //    view.resize(800, 600);
//     view.showMaximized();

    return app.exec();
}
