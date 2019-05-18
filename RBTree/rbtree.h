#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <algorithm>
#include <QString>

using namespace std;

enum { red = 0, black = 1 };

struct Node
{
    int key;
    bool color;
    Node * parent;
    Node * left;
    Node * right;
    Node(int key = 0)
    {
        this->key = key;
        this->color = red;
        this->parent = this->left = this->right = nullptr;
    }
};

class RBTree
{
private:
    Node * header; //head->l = root
private:
    void rotate_left(Node * x);
    void rotate_right(Node * x);
    void insert_rebalance(Node * x); //insert
    void erase_rebalance(Node * z); //delete

public:
    RBTree();
    ~RBTree();
    Node * insert(int key);
    Node * find(int key);
    Node *& root();
    void destroy(Node * node);
    void erase(int key);
    void print(QString &);
    void doprint(Node *t, int level, QString &);
};

#endif // RBTREE_H
