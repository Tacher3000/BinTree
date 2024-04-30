#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class HomeScreen : public QWidget
{
    Q_OBJECT
public:
    HomeScreen(QWidget *parent = nullptr);
signals:
    void clickedGenerator();
    void clickedEnter();
private slots:
    void Generator();
    void Enter();
private:
    QPushButton *m_buttonGenerator;
    QPushButton *m_buttonEnter;
};

#endif // HOMESCREEN_H
