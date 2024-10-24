// VAR 1
#include "../include/tree.h"

NodeT::NodeT(int value) {
    data = value;
    left = nullptr;
    right = nullptr;
}

CompleteBinaryTree::CompleteBinaryTree() {
    root = nullptr;
    size = 0;
}

void CompleteBinaryTree::insert(int value) {
    NodeT* newNode = new NodeT(value);
    if(root == nullptr) { //Если главная часть равна нулю
        root = newNode; //то присваиваем новую ноду
    } else {
        _insert(value, root);
    }
    size++;
}

void CompleteBinaryTree::_insert(int value, NodeT* nodeb) {
    if(value < nodeb->data) { //Сравниваем значения
        if(nodeb->left == nullptr) {
            nodeb->left = new NodeT(value);
        } else {
            _insert(value, nodeb->left); //Рекурсивно вставляем новое значение
        }

    } else {
        if(nodeb->right == nullptr) {
            nodeb->right = new NodeT(value);
        } else {
            _insert(value, nodeb->right);
        }
    }
}

NodeT* CompleteBinaryTree::removeNode(NodeT* root, int value) {
    if (root == nullptr) return root;

    if (value < root->data) {
        root->left = removeNode(root->left, value);
    } else if (value > root->data) {
        root->right = removeNode(root->right, value);
    } else {
        if (root->left == nullptr) { // Удаляем узел
            NodeT* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            NodeT* temp = root->left;
            delete root;
            return temp;
        }
    }
    return root;
}

void CompleteBinaryTree::remove() {
    if (root == nullptr) return; // Если дерево пустое, выход

    // Удаляем узел
    if (root->left == nullptr) {
        NodeT* temp = root->right;
        delete root;
        root = temp;
    } else if (root->right == nullptr) {
        NodeT* temp = root->left;
        delete root;
        root = temp;
    } else {
        NodeT* temp = root->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        root->data = temp->data; // Копируем данные
        root->right = removeNode(root->right, temp->data); // Удаляем узел с данными
    }
    size--; // Уменьшаем размер дерева
}

void CompleteBinaryTree::printTree(NodeT* node, int depth) {
    if (node == nullptr) return;
    printTree(node->right, depth + 1);
    cout << setw(4 * depth) << " " << node->data << endl;
    printTree(node->left, depth + 1);
}

void CompleteBinaryTree::clear(NodeT* nodet) {
    if (nodet == nullptr) return;
    clear(nodet->left);
    clear(nodet->right);
    delete nodet;
}

CompleteBinaryTree::~CompleteBinaryTree() {
    clear(root);
}

int main() {
    int N;
    cout << "Введите количество целых чисел: ";
    cin >> N;

    CompleteBinaryTree tree;

    cout << "Введите " << N << " целых чисел:" << endl;
    for (int i = 0; i < N; ++i) {
        int value;
        cin >> value;
        tree.insert(value);
    }

    cout << "Дерево после вставки:" << endl;
    tree.printTree(tree.root, 0); // Вывод дерева

    // Удаляем корень
    tree.remove();

    cout << "Дерево после удаления корня:" << endl;
    tree.printTree(tree.root, 0); // Вывод дерева после удаления

    return 0;
}