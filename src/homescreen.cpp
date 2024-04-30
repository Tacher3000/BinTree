#include "homescreen.h"

HomeScreen::HomeScreen(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    m_buttonGenerator = new QPushButton(this);
    m_buttonGenerator->setText("СГЕНЕРИРОВАТЬ СЛУЧАЙНОЕ ДЕРЕВО");
    m_buttonGenerator->setMinimumSize(400, 50);
    connect(m_buttonGenerator, &QPushButton::clicked, this, &HomeScreen::Generator);

    m_buttonEnter = new QPushButton(this);
    m_buttonEnter->setText("ВВЕСТИ ДЕРЕВО");
    m_buttonEnter->setMinimumSize(400, 50);
    connect(m_buttonEnter, &QPushButton::clicked, this, &HomeScreen::Enter);

    mainLayout->addWidget(m_buttonGenerator);
    mainLayout->addWidget(m_buttonEnter);
}

void HomeScreen::Generator()
{
    emit clickedGenerator();
}

void HomeScreen::Enter()
{
    emit clickedEnter();
}
