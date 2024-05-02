#ifndef GENDIALOG_H
#define GENDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QCheckBox>
#include <QFileDialog>

class GenDialog : public QDialog
{
    Q_OBJECT
public:
    GenDialog(QWidget *parent);
    QString getStart();
    QString getEnd();
    QString getQuality();
    QString getSelectedOption();
    void toggleDirectorySelection(int state);
    void selectDirectory();
    bool getCheckbox();
    QString getPathDic();
private:
    QLineEdit *m_start;
    QLineEdit *m_end;
    QLineEdit *m_quantity;
    QCheckBox *m_saveToFileCheckbox;
    QLineEdit *m_directoryLine;
    QPushButton *m_directoryButton;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
};

#endif // GENDIALOG_H
