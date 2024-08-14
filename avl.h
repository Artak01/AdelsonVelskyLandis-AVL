#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

template <typename T>
class AVL {
private:
    struct Node {
        T val;
        Node* left;
        Node* right;

        Node(T val) 
            : val(val) 
            , left(nullptr) 
            , right(nullptr) 
        {}
    };

    Node* root;

    Node* insertHelp(Node*& node, T value);
    Node* searchHelp(Node* node, T value) const;
    
    Node* Balance(Node* node);
    Node* leftRotate(Node* node);
    Node* rightRotate(Node* node);
    int getBF(Node* node) const;

    void inorderHelp(Node* node) const;
    void preorderHelp(Node* node) const;
    void postorderHelp(Node* node) const;
    void clear(Node* node);
    Node* deleteNodeHelp(Node* node, T value);
    Node* getMin(Node* node) const;
    Node* getMax(Node* node) const;
    int getHeightHelp(Node* node) const;
    int getSizeHelp(Node* node) const;
    Node* getPredecessorHelp(Node* node, T value) const;
    Node* getSuccessorHelp(Node* node, T value) const;
public:
    AVL();
    ~AVL();
    
    void insert(T value);
    bool search(T value) const;
    void inorder() const;
    void preorder() const;
    void postorder() const;
    void deleteValue(T value);
    int getHeight() const;
    int getSize() const;
    T getPredecessor(T value) const;
    T getSuccessor(T value) const;
};

#include "avl.cpp"
#endif
