#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    m_stackedWidget = new QStackedWidget(this);

    m_homeScreen = new HomeScreen(this);
    connect(m_homeScreen, &HomeScreen::clickedGenerator, this, &MainWindow::openGenDialog);
    connect(m_homeScreen, &HomeScreen::clickedEnter, this, &MainWindow::enterTree);
    m_stackedWidget->addWidget(m_homeScreen);

    m_treeWindow = new TreeWindow(this);
    connect(m_treeWindow, &TreeWindow::clickedExit, this, &MainWindow::homeScreen);
    m_stackedWidget->addWidget(m_treeWindow);

    setCentralWidget(m_stackedWidget);
}

void MainWindow::openGenDialog()
{
    GenDialog genDialog(this);
    if (genDialog.exec() == QDialog::Accepted){
        QString selectedOption = genDialog.getSelectedOption();

        if (selectedOption == "ТЕКСТОВЫЙ ВЫВОД") {

        } else if (selectedOption == "ГРАФИЧЕСКИЙ ВЫВОД (НЕ РЕКОМЕНДУЕЦА ИСПОЛЬЗОВАТЬ ЕСЛИ ЕОЛЛИЧЕСТВО ВЕРШИН БОЛЬШЕ 100.000)") {
            m_treeWindow->randomInsertion(genDialog.getStart().toInt(), genDialog.getEnd().toInt(), genDialog.getQuality().toInt());
            m_stackedWidget->setCurrentIndex(1);
        } else if (selectedOption == "БЕЗ ВЫВОДА") {

        }
    }
}

void MainWindow::homeScreen()
{
    m_stackedWidget->setCurrentIndex(0);
}

void MainWindow::enterTree()
{
    m_treeWindow->enterTree();
    m_stackedWidget->setCurrentIndex(1);
}
