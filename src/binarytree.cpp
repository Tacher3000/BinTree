#include "binarytree.h"

// Реализация методов класса Node

Node::Node(int value, int id) : value(value), id(id), left(nullptr), right(nullptr) {}

bool Node::equals(Node* other) {

    bool left_equal = false;
    bool right_equal = false;

    if (left && other->left) {
        left_equal = left->equals(other->left);
    } else if (left) {
        left_equal = true;
    }else if (!left && !other->left) {
        left_equal = true;
    }

    if (right && other->right) {
        right_equal = right->equals(other->right);
    } else if (right) {
        right_equal = true;
    }else if (!right && !other->right) {
        right_equal = true;
    }

    return left_equal && right_equal;
}

int Node::getId()
{
    return id;
}

size_t Node::size() {

    size_t nodeSize = sizeof(*this);
    if (left != nullptr)
        nodeSize += left->size();
    if (right != nullptr)
        nodeSize += right->size();
    return nodeSize;
}

// Реализация методов класса BinaryTree

BinaryTree::BinaryTree() : root(nullptr), nodes_amount(0) {}

BinaryTree::~BinaryTree() {
    clearTree(root);
}

void BinaryTree::clearTree(Node* node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

void BinaryTree::recursiveInsert(int value) {
    root = m_recursiveInsertNode(value, root);
}

void BinaryTree::iterativInsert(int value)
{
    root = m_iterativInsertNode(value, root);
}

void BinaryTree::randomInsertion(int start, int end, int amount) {
    QElapsedTimer timer;
    timer.start();

    QList<int> values;
    for (int i = 0; i < amount; ++i)
        values.append(QRandomGenerator::global()->bounded(start, end + 1));

    for (int value : values){
        // recursiveInsert(value);
        iterativInsert(value);
    }
    qDebug() << "randomInsertion" << timer.elapsed() << "milliseconds";
}

QList<Node*> BinaryTree::findSubtrees(Node* subtree_structure) {
    QElapsedTimer timer;
    timer.start();

    QList<Node*> result;
    m_findSubtrees(root, subtree_structure, result);
    qDebug() << "findSubtrees" << timer.elapsed() << "milliseconds";
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
    if (node == nullptr) {
        nodes_amount++;
        return new Node(value, nodes_amount);
    }

    Node* current = node;

    while (true) {
        if (QRandomGenerator::global()->bounded(2)) {
            if (current->left == nullptr) {
                nodes_amount++;
                current->left = new Node(value, nodes_amount);
                break;
            } else {
                current = current->left;
            }
        } else {
            if (current->right == nullptr) {
                nodes_amount++;
                current->right = new Node(value, nodes_amount);
                break;
            } else {
                current = current->right;
            }
        }
    }
    return node;
}

void BinaryTree::m_findSubtrees(Node* node, Node* subtree_structure, QList<Node*>& result) {
    if (node == nullptr)
        return;

    if (node->equals(subtree_structure))
        result.append(node);

    m_findSubtrees(node->left, subtree_structure, result);
    m_findSubtrees(node->right, subtree_structure, result);

}

void BinaryTree::writeTreeToFile(const QString& filename) {
    QElapsedTimer timer;
    timer.start();

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "writeTreeToFile: Невозможно прочитать файл" << file.errorString();
        return;
    }

    QTextStream out(&file);
    writeNodeToFile(root, out);

    file.close();

    qDebug() << "writeTreeToFile" << timer.elapsed() << "milliseconds";
}

void BinaryTree::writeNodeToFile(Node* node, QTextStream& out) {
    if (node != nullptr) {
        out << node->value << " " << node->id << " ";
        if (node->left != nullptr)
            out << node->left->id << " ";
        else
            out << "-1 ";
        if (node->right != nullptr)
            out << node->right->id << "\n";
        else
            out << "-1\n";
        writeNodeToFile(node->left, out);
        writeNodeToFile(node->right, out);
    }
}

void BinaryTree::readTreeFromFile(const QString& filename) {
    QElapsedTimer timer;
    timer.start();

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

    file.close();

    qDebug() << "readTreeFromFile" << timer.elapsed() << "milliseconds";
}

void BinaryTree::addNodeToTree(Node* node) {
    if (root == nullptr) {
        root = node;
    } else {
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

void BinaryTree::readTreeFromText(const QString& text) {
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
    m_printTreeRecursive(root, "", true, treeOutput);
    textEdit->setText(treeOutput);
}

void BinaryTree::m_printTreeRecursive(Node* node, const QString& prefix, bool isLast, QString& treeOutput) {
    if (node != nullptr) {
        treeOutput += prefix;
        treeOutput += (isLast ? "└── " : "├── ");
        treeOutput += QString::number(node->value) + "\n";

        QString childPrefix = prefix + (isLast ? "       " : "│       ");

        if (node->left != nullptr || node->right != nullptr) {
            m_printTreeRecursive(node->left, childPrefix, node->right == nullptr, treeOutput);
            m_printTreeRecursive(node->right, childPrefix, true, treeOutput);
        }
    }
}

Node *BinaryTree::getRoot()
{
    return root;
}

size_t BinaryTree::size() {
    if (root == nullptr)
        return 0;
    else
        return root->size();
}
