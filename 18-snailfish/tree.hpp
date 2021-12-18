#ifndef TREE_HPP
#define TREE_HPP

#include <stdint.h>
#include <iostream>

struct tree
{
    tree() : data(0), parent(nullptr), left(nullptr), right(nullptr) {}
    tree(tree *parent, uint8_t data) : data(data), parent(parent), left(nullptr), right(nullptr) {}
    ~tree() { delete left; delete right; }
    tree *first() { return left ? left->first() : this; }
    tree *last() { return right ? right->last() : this; }
    tree *next();
    tree *prev();
    uint16_t magnitude();

    bool explode(int depth = 0);
    void reduce();
    bool split();

    uint8_t data;
    tree *parent, *left, *right;
};

bool tree::explode(int depth)
{
    if (depth == 4 && left && right)
    {
        if (left->prev()) left->prev()->data += left->data;
        if (right->next()) right->next()->data += right->data;
        delete left;
        delete right;
        left = nullptr;
        right = nullptr;
        return true;
    }
    if (!left || !right)
    {
        // If this is a leaf node
        return false;
    }
    return left->explode(depth + 1) || right->explode(depth + 1);
}

uint16_t tree::magnitude()
{
    uint16_t ret = (uint16_t)data;
    if (left)  ret += 3*left->magnitude();
    if (right) ret += 2*right->magnitude();
    return ret;
}

// Assumes this function is called on a leaf node (otherwise will crash!)
// Returns the leaf node to the right of this one, if one exists. Otherwise returns nullptr.
tree *tree::next()
{
    tree *t = this;
    tree *p = parent;

    // Ascend the tree until this is no longer the right-most leaf of the subtree we are looking at.
    // If we get all the way to the tree's root, then there is no next leaf. We were at the end.
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
    tree *t = this;
    tree *p = parent;

    // Ascend the tree until this is no longer the left-most leaf of the subtree we are looking at.
    // If we get all the way to the tree's root, then there is no next leaf. We were at the end.
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
    while (explode() || split())
        continue;
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

tree *str_to_tree(std::istream &is)
{
    tree *t = new tree();

    char ch;
    is >> ch;
    if (ch == '[')
    {
        t->left = str_to_tree(is);
        is.ignore(1); // ignore ','
        t->right = str_to_tree(is);
        is.ignore(1); // ignore ']'
        t->left->parent = t;
        t->right->parent = t;
    }
    else // '0' <= ch <= '9'
    {
        t->data = (uint8_t)(ch - '0');
    }

    return t;
}

#endif
