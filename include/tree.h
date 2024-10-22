#ifndef tree_h
#define tree_h

#include "utility.h"

struct NodeT {
    int data;
    NodeT* left;
    NodeT* right;

    NodeT(int value);
};

struct CompleteBinaryTree {
    NodeT* root; //Главная часть в бинарном дереве
    size_t size;

    CompleteBinaryTree();
    ~CompleteBinaryTree();

    void insert(int value); //Функция добавления элемента
    void _insert(int value, NodeT* nodeb);
    NodeT* removeNode(NodeT* root, int value);
    void remove();
    void printTree(NodeT* node, int depth);
    void clear(NodeT* nodet); // освобождение памяти
};

#endif // TREE_H