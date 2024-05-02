#include <QApplication>
#include "mainwindow.h"

#include <QRandomGenerator>
#include <QDateTime>
#include <QDebug>
#include <QElapsedTimer>
#include <QtTest/QTest>
#include <chrono>

void timeTest();

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.showMaximized();
    // timeTest();

    return app.exec();
}


void timeTest(){
    // Создаем экземпляр бинарного дерева
    BinaryTree tree;

    // Задаем параметры для тестирования
    const int minNodes = 900000;
    const int maxNodes = 1000000;
    const int step = 10000;
    const int iterations = 5;

    // Измеряем время выполнения для каждого размера дерева
    for (int numNodes = minNodes; numNodes <= maxNodes; numNodes += step) {
        long long recursiveTotalTime = 0;
        long long iterativeTotalTime = 0;

        for (int i = 0; i < iterations; ++i) {
            // Генерируем случайные значения для вставки в дерево
            QVector<int> values;
            for (int j = 0; j < numNodes; ++j) {
                values.append(QRandomGenerator::global()->generate());
            }

            // Тестирование рекурсивной версии
            auto startRecursive = std::chrono::high_resolution_clock::now();
            for (int value : values) {
                tree.recursiveInsert(value);
            }
            auto endRecursive = std::chrono::high_resolution_clock::now();
            recursiveTotalTime += std::chrono::duration_cast<std::chrono::milliseconds>(endRecursive - startRecursive).count();

            // Пересоздаем дерево для следующей итерации
            tree = BinaryTree();

            // Тестирование итеративной версии
            auto startIterative = std::chrono::high_resolution_clock::now();
            for (int value : values) {
                tree.iterativInsert(value);
            }
            auto endIterative = std::chrono::high_resolution_clock::now();
            iterativeTotalTime += std::chrono::duration_cast<std::chrono::milliseconds>(endIterative - startIterative).count();

            // Пересоздаем дерево для следующей итерации
            tree = BinaryTree();
        }

        // Выводим результаты для текущего размера дерева
        qDebug() << "Number of nodes:" << numNodes;
        qDebug() << "Recursive average time (ms):" << recursiveTotalTime / iterations;
        qDebug() << "Iterative average time (ms):" << iterativeTotalTime / iterations;
    }
}
