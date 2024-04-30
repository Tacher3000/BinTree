#include "gendialog.h"

GenDialog::GenDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    m_start = new QLineEdit(this);
    m_start->setPlaceholderText("ОТ");
    m_start->setMinimumSize(400, 50);
    mainLayout->addWidget(m_start);

    m_end = new QLineEdit(this);
    m_end->setPlaceholderText("ДО");
    m_end->setMinimumSize(400, 50);
    mainLayout->addWidget(m_end);

    m_quantity = new QLineEdit(this);
    m_quantity->setPlaceholderText("КОЛЛИЧЕСТВО ВЕРШИН");
    m_quantity->setMinimumSize(400, 50);
    mainLayout->addWidget(m_quantity);

    // Создание радиокнопок
    QRadioButton *radioButton1 = new QRadioButton("ТЕКСТОВЫЙ ВЫВОД", this);
    QRadioButton *radioButton2 = new QRadioButton("ГРАФИЧЕСКИЙ ВЫВОД (НЕ РЕКОМЕНДУЕЦА ИСПОЛЬЗОВАТЬ ЕСЛИ ЕОЛЛИЧЕСТВО ВЕРШИН БОЛЬШЕ 100.000)", this);
    QRadioButton *radioButton3 = new QRadioButton("БЕЗ ВЫВОДА", this);

    // Группировка радиокнопок (чтобы они работали как единое целое)
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(radioButton1);
    buttonGroup->addButton(radioButton2);
    buttonGroup->addButton(radioButton3);

    // Добавление радиокнопок на форму
    mainLayout->addWidget(radioButton1);
    mainLayout->addWidget(radioButton2);
    mainLayout->addWidget(radioButton3);

    // Устанавливаем одну из кнопок по умолчанию выбранной
    radioButton2->setChecked(true);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    m_okButton = new QPushButton("OK", this);
    m_cancelButton = new QPushButton("Отмена", this);
    connect(m_okButton, &QPushButton::clicked, this, &GenDialog::accept);
    connect(m_cancelButton, &QPushButton::clicked, this, &GenDialog::reject);
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);

    mainLayout->addLayout(buttonLayout);
}

QString GenDialog::getStart()
{
    return m_start->text();
}

QString GenDialog::getEnd()
{
    return m_end->text();
}

QString GenDialog::getQuality()
{
    return m_quantity->text();
}

QString GenDialog::getSelectedOption()
{
    foreach (QRadioButton *button, findChildren<QRadioButton *>()) {
        if (button->isChecked()) {
            return button->text();
        }
    }
    return QString(); // Если ни одна кнопка не выбрана (такого не может быть)
}
