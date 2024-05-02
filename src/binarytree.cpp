#include "binarytree.h"

// Реализация методов класса Node

Node::Node(int value, int id) : value(value), id(id), left(nullptr), right(nullptr) {}

bool Node::equals(Node* other) {
    if (other == nullptr)
        return false;
    bool left_equal = (left && other->left) ? left->equals(other->left) : (left == other->left);
    bool right_equal = (right && other->right) ? right->equals(other->right) : (right == other->right);
    return left_equal && right_equal;
}

// Реализация методов класса BinaryTree

BinaryTree::BinaryTree() : root(nullptr), nodes_amount(0) {}

void BinaryTree::recursiveInsert(int value) {
    root = m_recursiveInsertNode(value, root);
}

void BinaryTree::iterativInsert(int value)
{
    root = m_iterativInsertNode(value, root);
}

void BinaryTree::random_insertion(int start, int end, int amount) {
    QList<int> values;
    for (int i = 0; i < amount; ++i)
        values.append(QRandomGenerator::global()->bounded(start, end + 1));

    for (int value : values){
        // recursiveInsert(value);
        iterativInsert(value);
    }
}

QList<Node*> BinaryTree::find_subtrees(Node* subtree_structure) {
    QList<Node*> result;
    dfs(root, subtree_structure, result);
    return result;
}



Node* BinaryTree::m_recursiveInsertNode(int value, Node* node) {
    if (node == nullptr) {
        nodes_amount++;
        return new Node(value, nodes_amount);
    }

    if (QRandomGenerator::global()->bounded(2)) {
        node->left = m_recursiveInsertNode(value, node->left);
    } else {
        node->right = m_recursiveInsertNode(value, node->right);
    }
    return node;
}

Node *BinaryTree::m_iterativInsertNode(int value, Node *node)
{
    // Если текущий узел пуст, создаем новый узел и возвращаем его
    if (node == nullptr) {
        nodes_amount++;
        return new Node(value, nodes_amount);
    }

    // Указатель на текущий узел, который будет использоваться для спуска по дереву
    Node* current = node;

    // Просматриваем дерево, пока не найдем место для вставки нового узла
    while (true) {
        // Случайно выбираем, идти влево или вправо
        if (QRandomGenerator::global()->bounded(2)) {
            // Если нет левого потомка, вставляем новый узел и выходим из цикла
            if (current->left == nullptr) {
                nodes_amount++;
                current->left = new Node(value, nodes_amount);
                break;
            } else {
                // Если есть левый потомок, двигаемся влево
                current = current->left;
            }
        } else {
            // Если нет правого потомка, вставляем новый узел и выходим из цикла
            if (current->right == nullptr) {
                nodes_amount++;
                current->right = new Node(value, nodes_amount);
                break;
            } else {
                // Если есть правый потомок, двигаемся вправо
                current = current->right;
            }
        }
    }
    // Возвращаем корневой узел
    return node;
}

void BinaryTree::dfs(Node* node, Node* subtree_structure, QList<Node*>& result) {
    if (node == nullptr)
        return;

    if (node->equals(subtree_structure))
        result.append(node);

    dfs(node->left, subtree_structure, result);
    dfs(node->right, subtree_structure, result);
}

void BinaryTree::write_tree_to_file(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Unable to open file for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    write_node_to_file(root, out);

    file.close();
}

void BinaryTree::write_node_to_file(Node* node, QTextStream& out) {
    if (node != nullptr) {
        // Записываем значение, id и связи текущего узла
        out << node->value << " " << node->id << " ";
        if (node->left != nullptr)
            out << node->left->id << " ";
        else
            out << "-1 "; // Если нет левого потомка, записываем -1
        if (node->right != nullptr)
            out << node->right->id << "\n";
        else
            out << "-1\n"; // Если нет правого потомка, записываем -1

        // Рекурсивно записываем левое и правое поддеревья
        write_node_to_file(node->left, out);
        write_node_to_file(node->right, out);
    }
}

void BinaryTree::read_tree_from_file(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open file for reading:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);
        if (parts.size() >= 3) {
            int value = parts[0].toInt();
            int id = parts[1].toInt();
            int leftId = parts[2].toInt();
            int rightId = parts.size() >= 4 ? parts[3].toInt() : -1;

            Node* node = new Node(value, id);
            // Добавляем узел в дерево
            addNodeToTree(node);

            // Если есть левый потомок, связываем его с текущим узлом
            if (leftId != -1) {
                Node* leftChild = new Node(0, leftId); // Значение временно задаем 0
                node->left = leftChild;
            }

            // Если есть правый потомок, связываем его с текущим узлом
            if (rightId != -1) {
                Node* rightChild = new Node(0, rightId); // Значение временно задаем 0
                node->right = rightChild;
            }
        }
    }

    file.close();
}

void BinaryTree::addNodeToTree(Node* node) {
    if (root == nullptr) {
        root = node;
    } else {
        // Находим узел с таким же id и добавляем к нему потомков
        addNodeToTreeRecursive(root, node);
    }
}

void BinaryTree::addNodeToTreeRecursive(Node* currentNode, Node* newNode) {
    if (currentNode == nullptr)
        return;

    if (currentNode->left != nullptr && currentNode->left->id == newNode->id) {
        currentNode->left = newNode;
    } else if (currentNode->right != nullptr && currentNode->right->id == newNode->id) {
        currentNode->right = newNode;
    } else {
        addNodeToTreeRecursive(currentNode->left, newNode);
        addNodeToTreeRecursive(currentNode->right, newNode);
    }
}

void BinaryTree::read_tree_from_text(const QString& text) {
    QStringList lines = text.split('\n', Qt::SkipEmptyParts);
    foreach (const QString &line, lines) {
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);
        if (parts.size() >= 3) {
            int value = parts[0].toInt();
            int id = parts[1].toInt();
            int leftId = parts[2].toInt();
            int rightId = parts.size() >= 4 ? parts[3].toInt() : -1;

            Node* node = new Node(value, id);
            addNodeToTree(node);

            if (leftId != -1) {
                Node* leftChild = new Node(0, leftId);
                node->left = leftChild;
            }

            if (rightId != -1) {
                Node* rightChild = new Node(0, rightId);
                node->right = rightChild;
            }
        }
    }
}


void BinaryTree::printTree(QTextEdit *textEdit) {
    QString treeOutput;
    printTreeRecursive(root, "", true, treeOutput);
    textEdit->setText(treeOutput);
}

void BinaryTree::printTreeRecursive(Node* node, const QString& prefix, bool isLast, QString& treeOutput) {
    if (node != nullptr) {
        treeOutput += prefix;
        treeOutput += (isLast ? "└── " : "├── ");
        treeOutput += QString::number(node->value) + "\n";

        QString childPrefix = prefix + (isLast ? "       " : "│       ");

        if (node->left != nullptr || node->right != nullptr) {
            printTreeRecursive(node->left, childPrefix, node->right == nullptr, treeOutput);
            printTreeRecursive(node->right, childPrefix, true, treeOutput);
        }
    }
}
