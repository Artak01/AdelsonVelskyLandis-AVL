#include "avl.h"

template <typename T>
AVL<T>::AVL()
    : root {nullptr}
{}

template <typename T>
AVL<T>::~AVL()
{
    clear(root);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::insertHelp(Node*& node, T value)
{
    if (!node) {
        return new Node(value);
    }
    if (node -> val > value) {
        node -> left = insertHelp(node -> left, value);
    } else {
        node -> right = insertHelp(node -> right, value);
    }
    return Balance(node);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::searchHelp(Node* node, T value) const
{
    if (!node) {
        return node;
    }
    if (node -> val == value) {
        return node;
    } else if (node -> val > value) {
        return searchHelp(node -> left, value);
    } else 
        return searchHelp(node -> right, value);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::Balance(Node* node)
{
    int bf = getBF(node);
    if (bf >= -1 && bf <= 1) {
        return node;
    }
    if (bf > 1 && getBF(node -> left) > 0) {
        return rightRotate(node);
    }
    if (bf > 1 && getBF(node -> left) < 0) {
        node -> left = leftRotate(node -> left);
        return rightRotate(node);
    }
    if (bf < -1 && getBF(node -> right) < 0) {
        return leftRotate(node);
    }
    if (bf < -1 && getBF(node -> right) > 0) {
        node -> right = rightRotate(node -> right);
        return leftRotate(node);
    }
    return node;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::leftRotate(Node* node)
{
    Node* y = node -> right;  
    Node* tmp = y -> left;
    y -> left = node;
    node -> right = tmp;
    return y;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rightRotate(Node* node)
{
    Node* y = node -> left;  
    Node* tmp = y -> right;
    y -> right = node;
    node -> left = tmp;
    return y;
}

template <typename T>  
int AVL<T>::getBF(Node* node) const
{
    return getHeightHelp(node -> left) - getHeightHelp(node -> right); 
}


template <typename T>
void AVL<T>::inorderHelp(Node* node) const
{
    if (!node) {
        return;
    }
    inorderHelp(node -> left);
    std::cout << node -> val << " ";
    inorderHelp(node -> right);
}
    
template <typename T>
void AVL<T>::preorderHelp(Node* node) const
{
    if (!node) {
        return;
    }
    std::cout << node -> val << " ";
    preorderHelp(node -> left);
    preorderHelp(node -> right);
}

template <typename T>
void AVL<T>::postorderHelp(Node* node) const
{
    if (!node) {
        return;
    }
    postorderHelp(node -> left);
    postorderHelp(node -> right);
    std::cout << node -> val << " ";
}

template <typename T>
void AVL<T>::clear(Node* node)
{
    if (!node) {
        return;
    }
    clear(node -> left);
    clear(node -> right);
    delete node;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::deleteNodeHelp(Node* node, T value)
{
    if (!node) {
        return node;
    }
    if (node -> val < value) {
        node -> right = deleteNodeHelp(node -> right, value);
    } else if (node -> val > value) {
        node -> left = deleteNodeHelp(node -> left, value);
    } else if (node -> val == value) {
        if (!node -> left) {
            Node* tmp = node -> right;
            delete node;
            return tmp;
        } else if (!node -> right) {
            Node* tmp = node -> left;
            delete node;
            return tmp;
        } else {
            Node* tmp = getMax(node -> left);
            node -> val = tmp -> val;
            node = deleteNodeHelp(node -> left, tmp -> val);
        }
    }
    return Balance(node);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::getMin(Node* node) const
{
    while (node && node -> left) {
        node = node -> left;
    }
    return node;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::getMax(Node* node) const
{
    while (node && node -> right) {
        node = node -> right;
    }
    return node;    
}



template <typename T>
int AVL<T>::getHeightHelp(Node* node) const
{
    if (!node) {
        return 0;
    }
    return std::max(getHeightHelp(node -> left), getHeightHelp(node -> right)) + 1;
}

template <typename T>
int AVL<T>::getSizeHelp(Node* node) const
{
    if (!node) {
        return 0;
    }
    return getSizeHelp(node -> left) + getSizeHelp(node -> right) + 1;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::getPredecessorHelp(Node* node, T value) const
{
    Node* curr = searchHelp(node, value);

    if (!curr) {
        throw std::invalid_argument("Invalid value!");
    }
    
    if (curr -> left) {
        return getMax(curr -> left);
    }

    Node* predecessor = nullptr;
    Node* ancestor = node;
    while (ancestor != curr) {
        if (ancestor -> val < value) {
            predecessor = ancestor;
            ancestor = ancestor -> right;
        } else {
            ancestor = ancestor -> left;
        }
    }
    return predecessor;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::getSuccessorHelp(Node* node, T value) const
{
    Node* curr = searchHelp(node, value);
    if (!curr) {
        throw std::invalid_argument("Invalid value!");
    }
    if (curr -> right) {
        return getMin(curr -> right);
    }

    Node* successor = nullptr;
    Node* ancestor = node;
    while (curr != ancestor) {
        if (ancestor -> val > value) {
            successor = ancestor;
            ancestor = ancestor -> left;
        } else {
            ancestor = ancestor -> right;
        }
    }
    return successor;
}



////////////////////////////////

template <typename T>
void AVL<T>::insert(T value)
{
    root = insertHelp(root, value);
}

template <typename T>
bool AVL<T>::search(T value) const
{
    return searchHelp(root, value);
}

template <typename T>
void AVL<T>::inorder() const
{
    inorderHelp(root);
    std::cout << std::endl;
}

template <typename T>
void AVL<T>::preorder() const
{
    preorderHelp(root);
    std::cout << std::endl;
}

template <typename T>
void AVL<T>::postorder() const
{
    postorderHelp(root);
    std::cout << std::endl;
}

template <typename T>
void AVL<T>::deleteValue(T value)
{
    deleteNodeHelp(root, value);
}

template <typename T>
int AVL<T>::getHeight() const
{
    return getHeightHelp(root);
}


template <typename T>
int AVL<T>::getSize() const
{
    return getSizeHelp(root);
}

template <typename T>
T AVL<T>::getPredecessor(T value) const
{
    Node* node = getPredecessorHelp(root, value);
    if (!node) {
        throw std::invalid_argument("The value is first element!");
    }
    return node -> val;
}

template <typename T>
T AVL<T>::getSuccessor(T value) const
{
    Node* node = getSuccessorHelp(root, value);
    if (!node) {
        throw std::invalid_argument("The value is last element!");
    }
    return node -> val;
}

