#ifndef TREE_HPP
#define TREE_HPP

#include <stdint.h>
#include <iostream>

struct tree
{
    tree() : data(0), parent(nullptr), left(nullptr), right(nullptr) {}
    tree(tree *parent, uint8_t data) : data(data), parent(parent), left(nullptr), right(nullptr) {}
    tree(std::istream &is, tree *parent = nullptr);
    tree(tree *left, tree *right) : data(0), parent(nullptr), left(left), right(right) {left->parent = this; right->parent = this;};
    ~tree() { delete left; delete right; }

    tree *first() { return left ? left->first() : this; }
    tree *last() { return right ? right->last() : this; }
    tree *next();
    tree *prev();
    template <typename T> T magnitude();
    bool explode(int depth = 0);
    void reduce();
    bool split();

    uint8_t data;
    tree *parent, *left, *right;
};

bool tree::explode(int depth)
{
    if (left && right)
    {
        if (depth == 4)
        {
            if ( left->prev())  left->prev()->data +=  left->data;
            if (right->next()) right->next()->data += right->data;
            delete left;  left = nullptr;
            delete right; right = nullptr;
            return true;
        }
        return left->explode(depth + 1) || right->explode(depth + 1);
    }
    return false;
}

template <typename T> T tree::magnitude()
{
    return (left && right) ? T(3)*left->magnitude<T>() + T(2)*right->magnitude<T>() : (T)data;
}

// Returns the leaf node to the right of this one, if one exists. Otherwise returns nullptr.
// Assumes this is a leaf node, otherwise it makes no sense to call anyway and may crash
tree *tree::next()
{
    // Ascend the tree until this is no longer the right-most leaf of the subtree we are looking at.
    // If we get all the way to the tree's root, then there is no next leaf. We were at the end.
    tree *t = this, *p = parent;
    while (p->right == t)
    {
        t = p;
        p = p->parent;
        if (!p) return nullptr;
    }

    // Take the left-most leaf under the parent's right branch
    return p->right->first();
}

// Assumes this function is called on a leaf node (otherwise will crash!)
// Returns the leaf node to the left  of this one, if one exists. Otherwise returns nullptr.
tree *tree::prev()
{
    // Ascend the tree until this is no longer the left-most leaf of the subtree we are looking at.
    // If we get all the way to the tree's root, then there is no next leaf. We were at the beginning.
    tree *t = this, *p = parent;
    while (p->left == t)
    {
        t = p;
        p = p->parent;
        if (!p) return nullptr;
    }

    // Take the right-most leaf under the parent's left branch
    return p->left->last();
}

void tree::reduce()
{
    while (explode() || split()) continue;
}

bool tree::split()
{
    if (data > 9)
    {
        uint8_t d = data / 2;
        left = new tree(this, d);
        right = new tree(this, data - d);
        data = 0;
        return true;
    }
    if (left && right)
        return left->split() || right->split();
    return false;
}

tree::tree(std::istream &is, tree *parent)
 : tree(parent, (uint8_t)0)
{
    char ch;
    is >> ch;
    if (ch == '[')
    {
        left = new tree(is, this);
        is.ignore(1); // ignore ','
        right = new tree(is, this);
        is.ignore(1); // ignore ']'
    }
    else // '0' <= ch <= '9'
    {
        data = (uint8_t)(ch - '0');
    }
}

#endif
