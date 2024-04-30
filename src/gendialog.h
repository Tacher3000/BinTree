#ifndef GENDIALOG_H
#define GENDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>

class GenDialog : public QDialog
{
    Q_OBJECT
public:
    GenDialog(QWidget *parent);
    QString getStart();
    QString getEnd();
    QString getQuality();
    QString getSelectedOption();
private:
    QLineEdit *m_start;
    QLineEdit *m_end;
    QLineEdit *m_quantity;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
};

#endif // GENDIALOG_H
