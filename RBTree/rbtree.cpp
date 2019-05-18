#include "rbtree.h"

void RBTree::rotate_left(Node * x)
{
    Node * y = x->right;

    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;

    if (x == root())
        root() = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RBTree::rotate_right(Node * x)
{
    Node * y = x->left;

    x->left = y->right;
    if (y->right)
        y->right->parent = x;
    y->parent = x->parent;

    if (x == root())
        root() = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void RBTree::destroy(Node * node)
{
    if (node == nullptr)
        return;

    destroy(node->left);
    destroy(node->right);
    delete node;
}

Node *& RBTree::root()
{
    return header->left;
}

void RBTree::insert_rebalance(Node * x)
{
    x->color = red;

    while (x != root() && x->parent->color == red)
    {
        if (x->parent == x->parent->parent->left)
        {
            Node * y = x->parent->parent->right;

            if (y && y->color == red)           // Case 1 uncle red
            {
                x->parent->color = black;
                y->color = black;
                x->parent->parent->color = red;
                x = x->parent->parent;
            }
            else    //uncle black
            {
                if (x == x->parent->right)      // Case 2   zhi zi xing
                {
                    x = x->parent;
                    rotate_left(x);
                }

                x->parent->color = black;       // Case 3   yi zi xing
                x->parent->parent->color = red;
                rotate_right(x->parent->parent);
            }
        }
        else  // same as above, just left <-> right
        {
            Node * y = x->parent->parent->left;

            if (y && y->color == red)
            {
                x->parent->color = black;
                y->color = black;
                x->parent->parent->color = red;
                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->left)
                {
                    x = x->parent;
                    rotate_right(x);
                }

                x->parent->color = black;
                x->parent->parent->color = red;
                rotate_left(x->parent->parent);
            }
        }
    }

    root()->color = black;  // Do not forget! root to black
}

void RBTree::erase_rebalance(Node * z)
{
    Node * y = z;
    Node * x = nullptr;
    Node * x_parent = nullptr;

    //
    if (y->left == nullptr)
        x = y->right;
    else if (y->right == nullptr)
        x = y->left;
    else
    {
        y = y->right;   // find right min node
        while (y->left)
            y = y->left;
        x = y->right;
    }

    if (y != z)  // if y is z's successor // the third
    {
        z->left->parent = y;
        y->left = z->left;

        if (y != z->right)
        {
            x_parent = y->parent;
            if (x)
                x->parent = y->parent;
            y->parent->left = x;
            y->right = z->right;
            z->right->parent = y;
        }
        else
            x_parent = y;

        if (root() == z)
            root() = y;
        else if (z->parent->left == z)
            z->parent->left = y;
        else
            z->parent->right = y;

        y->parent = z->parent;
        swap(y->color, z->color);
        y = z;
    }
    else
    {
        x_parent = y->parent;
        if (x)
            x->parent = y->parent;

        if (root() == z)
            root() = x;
        else if (z->parent->left == z)
            z->parent->left = x;
        else
            z->parent->right = x;
    }
    // now, y is pointing to what you will erase!
    //      x is the child of y, and note that x might be nullptr.



    // Now, the actual reblance is coming!
    // .....
    if (y->color == black)
    {
        while (x != root() && (x == nullptr || x->color == black))
        {
            if (x == x_parent->left)
            {
                Node * w = x_parent->right;  // w can not possibly be nullptr!

                if (w->color == red)                                      // Case 1
                {
                    w->color = black;
                    x_parent->color = red;
                    rotate_left(x_parent);
                    w = x_parent->right;
                }

                if ((w->left == nullptr || w->left->color == black) &&    // Case 2
                    (w->right == nullptr || w->right->color == black))
                {
                    w->color = red;
                    x = x_parent;
                    x_parent = x_parent->parent;
                }
                else
                {
                    if (w->right == nullptr || w->right->color == black)  //Case 3
                    {
                        if (w->left)
                            w->left->color = black;
                        w->color = red;
                        rotate_right(w);
                        w = x_parent->right;
                    }

                    w->color = x_parent->color;                           // Case 4
                    x_parent->color = black;
                    if (w->right)
                        w->right->color = black;
                    rotate_left(x_parent);
                    break;
                }
            }
            else  // same as above, just left <-> right
            {
                Node * w = x_parent->left;

                if (w->color == red)
                {
                    w->color = black;
                    x_parent->color = red;
                    rotate_right(x_parent);
                    w = x_parent->left;
                }

                if ((w->right == nullptr || w->right->color == black) &&
                    (w->left == nullptr || w->left->color == black))
                {
                    w->color = red;
                    x = x_parent;
                    x_parent = x_parent->parent;
                }
                else
                {
                    if (w->left == nullptr || w->left->color == black)
                    {
                        if (w->right)
                            w->right->color = black;
                        w->color = red;
                        rotate_left(w);
                        w = x_parent->left;
                    }

                    w->color = x_parent->color;
                    x_parent->color = black;
                    if (w->left)
                        w->left->color = black;
                    rotate_right(x_parent);
                    break;
                }
            }
        }  // while (x != root() && (x == nullptr || x->color == black))

        if (x)
            x->color = black;
    }  // if (y->color == black)
}

RBTree::RBTree()
{
    header = new Node(0);
}

RBTree::~RBTree()
{
    destroy(root());
    delete header;
    header = nullptr;
}

Node * RBTree::insert(int key)
{
    Node * cur = root();
    Node * pre = header;

    while (cur)
    {
        pre = cur;
        if (key < cur->key)
            cur = cur->left;
        else if (key > cur->key)
            cur = cur->right;
        else
            return nullptr;
    }

    cur = new Node(key);
    cur->parent = pre;

    if (pre == header || key < pre->key)
        pre->left = cur;
    else
        pre->right = cur;

    insert_rebalance(cur);

    return cur;
}

Node * RBTree::find(int key)
{
    Node * z = root();

    while (z)
    {
        if (key < z->key)
            z = z->left;
        else if (key > z->key)
            z = z->right;
        else
            return z;
    }

    return z;
}

void RBTree::erase(int key)
{
    Node * z = find(key);

    if (z)
    {
        erase_rebalance(z);
        delete z;
    }
}

void RBTree::doprint(Node *T, int level, QString &str)
{
    if (T == nullptr) return;        //如果指针为空，返回上一层

    doprint(T->right, level + 1, str);   //打印右子树，并将层次加1
    for (int i = 0; i<level; i++)    //按照递归的层次打印空格
    {
        str += "    ";//printf("   ");
    }
    char num[10];

    sprintf(num, "%d", T->key);
    str += QString(num);

    str += (T->color == red) ? "R\n\n" : "B\n\n";
    doprint(T->left, level + 1, str);    //打印左子树，并将层次加1
    str += "\n";
}

void RBTree::print(QString &str)
{

    doprint(this->root(), 1, str);

}
