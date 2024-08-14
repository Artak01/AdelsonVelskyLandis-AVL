#include <iostream>
#include "avl.h"

int main() {
    // Create an AVL tree instance
    AVL<int> avl;

    // Insert elements into the AVL tree
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    // Inorder traversal (should print sorted order)
    std::cout << "Inorder traversal: ";
    avl.inorder();
    std::cout << std::endl;

    // Preorder traversal
    std::cout << "Preorder traversal: ";
    avl.preorder();
    std::cout << std::endl;

    // Postorder traversal
    std::cout << "Postorder traversal: ";
    avl.postorder();
    std::cout << std::endl;

    // Search for a value
    int searchValue = 30;
    if (avl.search(searchValue)) {
        std::cout << searchValue << " found in the AVL tree." << std::endl;
    } else {
        std::cout << searchValue << " not found in the AVL tree." << std::endl;
    }

    // Get the height of the AVL tree
    std::cout << "Height of the AVL tree: " << avl.getHeight() << std::endl;

    // Get the size of the AVL tree
    std::cout << "Size of the AVL tree: " << avl.getSize() << std::endl;

    // Get predecessor of a value
    int predecessorValue = 30;
    try {
        int predecessor = avl.getPredecessor(predecessorValue);
        std::cout << "Predecessor of " << predecessorValue << " is " << predecessor << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    // Get successor of a value
    int successorValue = 30;
    try {
        int successor = avl.getSuccessor(successorValue);
        std::cout << "Successor of " << successorValue << " is " << successor << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    // Delete a value from the AVL tree
    int deleteValue = 40;
    avl.deleteValue(deleteValue);
    std::cout << "Inorder traversal after deleting " << deleteValue << ": ";
    avl.inorder();
    std::cout << std::endl;

    return 0;
}

