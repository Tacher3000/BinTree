#include "treewindow.h"

TreeWindow::TreeWindow(QWidget *parent)
    : QWidget{parent}, m_tree{std::make_unique<BinaryTree>()}, m_scene{std::make_unique<QGraphicsScene>()}, m_view{std::make_unique<ScalableGraphicsView>()}
{
    m_reGenButton = new QPushButton(this);
    m_reGenButton->setText("ПЕРЕГЕНЕРИРОВАТЬ");
    m_reGenButton->setMinimumSize(400, 50);
    connect(m_reGenButton, &QPushButton::clicked, this, &TreeWindow::reGen);

    m_searchButton = new QPushButton(this);
    m_searchButton->setText("НАЙТИ ПОДДЕРЕВО");
    m_searchButton->setMinimumSize(400, 50);

    m_exitButton = new QPushButton(this);
    m_exitButton->setText("ВЕРНУТЬСЯ НА ГЛАВНЫЙ ЭКРАН");
    m_exitButton->setMinimumSize(400, 50);
    connect(m_exitButton, &QPushButton::clicked, this, &TreeWindow::exit);
}


void TreeWindow::randomInsertion(int start, int end, int quantity)
{
    m_quantityLabel.setText("КОЛЛИЧЕСТВО ВЕРШИН: " + QString::number(quantity));

    m_start = start;
    m_end = end;
    m_quantity = quantity;
    // Добавляем в дерево случайные узлы
    m_tree->random_insertion(start, end, quantity);

    // Вычисляем ширину первого уровня дерева
    qreal levelWidth = calculateLevelWidth(m_tree->root);

    // Добавляем узлы дерева на сцену
    addNodesToScene(*m_scene, m_tree->root, 0, 0, 200, levelWidth);

    m_view->setScene(m_scene.get());

    QVBoxLayout * buttonLayout = new QVBoxLayout();
    buttonLayout->setAlignment(Qt::AlignCenter);
    buttonLayout->addWidget(&m_quantityLabel);
    buttonLayout->addWidget(m_reGenButton);
    buttonLayout->addWidget(m_searchButton);
    buttonLayout->addWidget(m_exitButton);

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_view.get());
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void TreeWindow::enterTree()
{
    // m_quantityLabel.setText("КОЛЛИЧЕСТВО ВЕРШИН: " + QString::number(quantity));

    QVariantMap treeData;

    // Example data: Construct a simple binary tree
    treeData["root_value"] = 10;
    treeData[QString::number(2)] = QVariantList() << QVariantList() << 20 << 30; // Node 2 has left child 20 and right child 30
    treeData[QString::number(3)] = QVariantList() << QVariantList() << 40 << 50; // Node 3 has left child 40 and right child 50

    m_tree->read_tree_from_dict(treeData);



    // Вычисляем ширину первого уровня дерева
    qreal levelWidth = calculateLevelWidth(m_tree->root);

    // Добавляем узлы дерева на сцену
    addNodesToScene(*m_scene, m_tree->root, 0, 0, 200, levelWidth);

    m_view->setScene(m_scene.get());

    QVBoxLayout * buttonLayout = new QVBoxLayout();
    buttonLayout->setAlignment(Qt::AlignCenter);
    // buttonLayout->addWidget(&m_quantityLabel);
    buttonLayout->addWidget(m_searchButton);
    buttonLayout->addWidget(m_exitButton);

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_view.get());
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void TreeWindow::exit()
{
    // Очистка сцены
    m_scene->clear();

    // Очистка дерева
    m_tree.reset(new BinaryTree());
    emit clickedExit();
}

void TreeWindow::reGen()
{
    m_scene->clear();

    // Очистка дерева
    m_tree.reset(new BinaryTree());
    randomInsertion(m_start, m_end, m_quantity);
}

void TreeWindow::addNodesToScene(QGraphicsScene &scene, Node *node, qreal x, qreal y, qreal offsetY, qreal levelWidth) {
    if (node == nullptr)
        return;

    QGraphicsEllipseItem* ellipseItem = scene.addEllipse(x, y, NODE_WIDTH, NODE_HEIGHT);
    ellipseItem->setBrush(Qt::lightGray);

    qreal centerX = x + NODE_WIDTH / 2;
    qreal centerY = y + NODE_HEIGHT / 2;

    QGraphicsTextItem* textItem = scene.addText(QString::number(node->value));
    textItem->setPos(centerX - textItem->boundingRect().width() / 2, centerY - textItem->boundingRect().height() / 2);
    textItem->setFont(QFont("Arial", 10, QFont::Bold));



    // Распределяем левого и правого потомка узла с учетом динамического расстояния между узлами
    qreal childSpaceX = levelWidth / 2;
    if (node->left != nullptr) {
        addNodesToScene(scene, node->left, x - levelWidth, y + offsetY, offsetY, childSpaceX);
        scene.addLine(x + 25, y + 50, x - levelWidth + 25, y + offsetY);
    }
    if (node->right != nullptr) {
        addNodesToScene(scene, node->right, x + levelWidth, y + offsetY, offsetY, childSpaceX);
        scene.addLine(x + 25, y + 50, x + levelWidth + 25, y + offsetY);
    }
}

qreal TreeWindow::calculateLevelWidth(Node *node) {
    if (node == nullptr)
        return 0;

    qreal leftWidth = calculateLevelWidth(node->left);
    qreal rightWidth = calculateLevelWidth(node->right);

    return leftWidth + rightWidth + 50;
}
