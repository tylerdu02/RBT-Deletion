/*
* Tyler Du
* 4/30/23
* Red Black Tree Insertion
* https://www.programiz.com/dsa/red-black-tree
* https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
* Links used for reference to help
*/

#include <iostream>
#include <string.h>
#include <fstream>
#include <cstring>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    bool isRed;
    Node(int data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        isRed = true;
    }
};

void insert(Node* &root, Node* current);
void RBTInsert(Node* current, Node* &root);
void print(Node* root, int numTabs);
void leftRotate(Node* current, Node* &root);
void rightRotate(Node* current, Node* &root);
void search(Node* root, int value);
void Delete(Node* &root, int value);
void RBTDelete(Node* current, Node* &root);
Node* getParent(Node* current);
Node* getGrandparent(Node* current);
Node* getSibling(Node* current);
Node* getUncle(Node* current);
Node* find(Node* root, int value);
bool color(Node* current);

int main() {
    char input[10];
    bool running = true;
    Node* root = nullptr;

    while (running == true) {
        cout << "Add, print, file, delete or search?" << endl;

        cin.get(input, 10);
        cin.ignore(1, '\n');

        if (input[0] == 'A' || input[0] == 'a') { // input
            int num;
            cout << "Input a number 1-999" << endl;
            cin >> num;
            cin.ignore(1, '\n');
            if (num >= 1 && num <= 999) { // checks if input is valid
                Node* current = new Node(num);
                insert(root, current);
                RBTInsert(current, root);
            }
            else { 
                cout << "Invalid input. Try again." << endl;
            }
        }
        else if (input[0] == 'P' || input[0] == 'p') { // prints 
            print(root, 0);
            cout << endl;
        }
        else if (input[0] == 'F' || input[0] == 'f') { // generates numbers from numbers.txt
            cout << "Numbers from tree have been generated into tree" << endl;
            ifstream numbers;
            numbers.open("numbers.txt");
            int numnums;
            while (numbers >> numnums) { 
                Node* current = new Node(numnums);
                insert(root, current);
                RBTInsert(current, root);
            }
            numbers.close();
        }
        else if (input[0] == 'D' || input[0] == 'd') { // deletes 
            int deleteNum;
            cout << "What number would you like to delete?" << endl;
            cin >> deleteNum;
            cin.ignore(1, '\n');
            if (deleteNum >= 1 && deleteNum <= 999) { 
                Delete(root, deleteNum);
                cout << deleteNum << " has been deleted" << endl;
            }
            else { // if input is not valids
                cout << "Invalid input. Try again" << endl;
            }
        }
        else if (input[0] == 'S' || input[0] == 's') { // searches
            int searchNum;
            cout << "What number would you like to search?" << endl;
            cin >> searchNum;
            cin.ignore(1, '\n');
            search(root, searchNum);
        }
        else {
            cout << "Invalid input. Try again." << endl;
        }
    }
}

Node* getParent(Node* current) { // returns the parent of the node
    return current->parent;
}

Node* getGrandparent(Node* current) { // returns the grandparent of the node
    return getParent(getParent(current));
}

Node* getSibling(Node* current) { // returns the sibling of the node
    Node* parent = getParent(current);
    if (parent == nullptr) { 
        return nullptr;
    }
    if (current == parent->left) { // left child
        return parent->right;
    }
    else { // right child
        return parent->left;
    }
}

Node* getUncle(Node* current) { // returns the uncle of the node
    Node* parent = getParent(current);
    Node* grandparent = getGrandparent(current);
    if (grandparent == nullptr) { 
        return nullptr;
    }
    return getSibling(parent);
}

Node* find(Node* root, int value) { // finds node
    if (root == nullptr || root->data == value) { 
        return root;
    }
    if (root->data < value) { 
        return find(root->right, value);
    }
    return find(root->left, value);
}

bool color(Node* current) { // gets color (red or black)
    if (current == nullptr) {
        return false;
    }
    return current->isRed;
}

void insert(Node* &root, Node* current) { // inserts node 
    if (root == nullptr) { 
        root = current;
        root->isRed = false;
    }
    else { 
        if (current->data < root->data) { 
            if (root->left == nullptr) { 
                root->left = current;
                current->parent = root;
            }
            else { 
                insert(root->left, current);
            }
        }
        else { // if greater
            if (root->right == nullptr) { 
                root->right = current;
                current->parent = root;
            }
            else { 
                insert(root->right, current);
            }
        }
    }
}

void RBTInsert(Node* current, Node* &root) { // insertion part
    if (getParent(current) == nullptr) { 
        current->isRed = false;
    }
    else if (color(getParent(current)) == false) { // black
        return;
    }
    else if (color(getUncle(current)) == true) { // red
        getParent(current)->isRed = false;
        getUncle(current)->isRed = false;
        getGrandparent(current)->isRed = true;
        RBTInsert(getGrandparent(current), root);
    }
    else { 
        Node* parent = getParent(current);
        Node* grandparent = getGrandparent(current);

        if (current == parent->right && parent == grandparent->left) { 
            leftRotate(parent, root);
            current = current->left;
        }
        else if (current == parent->left && parent == grandparent->right) { 
            rightRotate(parent, root);
            current = current->right;
        }

        parent = getParent(current);
        grandparent = getGrandparent(current);

        if (current == parent->left) { 
            rightRotate(grandparent, root);
        }
        else { 
            leftRotate(grandparent, root);
        }
        parent->isRed = false;
        grandparent->isRed = true;
    }
}

void print(Node* root, int numTabs) { // prints 
    if (root == nullptr) { 
        return;
    }
    numTabs += 10;

    print(root->right, numTabs); 
    cout << endl;
    for (int i = 10; i < numTabs; i++) { 
        cout << " ";
    }
    cout << root->data;
    if (root->isRed == true) { // prints the color 
        cout << " (Red)" << endl;
    }
    else { 
        cout << " (Black)" << endl;
    }
    cout << endl;
    print(root->left, numTabs); 
}

void search(Node* root, int value) { // searches 
    if (root == nullptr) { 
        cout << "Invalid input. Try again." << endl;
        return;
    }
    else if (value < root->data) { // less than 
        search(root->left, value);
    }
    else if (value > root->data) { // greater than 
        search(root->right, value);
    }
    else if (value == root->data) { // equal 
        cout << "Number found: " << value << endl;
    }
    else { 
        cout << "Invalid input. Try again." << endl;
    }
}

// https://www.programiz.com/dsa/red-black-tree
void leftRotate(Node* current, Node* &root) { // rotate
    cout << "Left rotate" << endl;
    Node* currentRight = current->right;
    current->right = currentRight->left;
    if (currentRight->left != nullptr) { 
        cout << "Node is not null" << endl;
        currentRight->left->parent = current;
    }
    currentRight->left = current;
    currentRight->parent = current->parent;
    if (current->parent == nullptr) { 
        root = currentRight;
        cout << "Node is the root" << endl;
    }
    else if (current == current->parent->left) { 
        current->parent->left = currentRight;
        cout << "Node is left child of parent" << endl;
    }
    else { 
        current->parent->right = currentRight;
        cout << "Node is right child of parent" << endl;
    } 
    current->parent = currentRight;
}

void rightRotate(Node* current, Node* &root) { // rotate
    cout << "Right rotate" << endl;
    Node* currentLeft = current->left;
    current->left = currentLeft->right;
    if (currentLeft->right != nullptr) { 
        cout << "Node is not null" << endl;
        currentLeft->right->parent = current;
    }
    currentLeft->right = current;
    currentLeft->parent = current->parent;
    if (current->parent == nullptr) { 
        cout << "Node is the root" << endl;
        root = currentLeft;
    }
    else if (current == current->parent->left) { 
        cout << "Node is left child of parent" << endl;
        current->parent->left = currentLeft;
    }
    else { 
        cout << "Node is right child of parent" << endl;
        current->parent->right = currentLeft;
    }
    current->parent = currentLeft;
}

// https://www.programiz.com/dsa/deletion-from-a-red-black-tree
void Delete(Node* &root, int value) { // deletes a value 
    Node* node = find(root, value); 
    Node* deleteNode = nullptr; 
    Node* childNode = nullptr; 
    if (node == nullptr) { 
        return;
    }
    if (node->left == nullptr || node->right == nullptr) { // if node has one child
        deleteNode = node;
    } 
    else { // if node has two 
        deleteNode = node->right;
        while (deleteNode->left != nullptr) {
            deleteNode = deleteNode->left;
        }
    }
    if (deleteNode->left != nullptr) { 
        childNode = deleteNode->left;
    } 
    else { 
        childNode = deleteNode->right;
    }
    if (childNode != nullptr) { 
        childNode->parent = deleteNode->parent;
    }
    if (deleteNode->parent == nullptr) { 
        root = childNode;
    }
    else if (deleteNode == deleteNode->parent->left) { 
        deleteNode->parent->left = childNode;
    }
    else { 
        deleteNode->parent->right = childNode;
    }
    if (deleteNode != node) { 
        node->data = deleteNode->data;
    }
    if (deleteNode->isRed == false && childNode != nullptr) { 
        RBTDelete(childNode, root);
    }
}

void RBTDelete(Node* current, Node* &root) { // fixes tree 
    while (current != root && color(current) == false) {  
        if (current == getParent(current)->left) { 
            Node* sibling = getSibling(current);
            if (color(sibling) == true) { 
                sibling->isRed = false;
                getParent(current)->isRed = true;
                leftRotate(getParent(current), root);
                sibling = getParent(current)->right;
            }
            if (color(sibling->left) == false && color(sibling->right) == false) { 
                sibling->isRed = true;
                current = getParent(current);
            } 
            else { 
                if (color(sibling->right) == false) { 
                    sibling->left->isRed = false;
                    sibling->isRed = true;
                    rightRotate(sibling, root);
                    sibling = getParent(current)->right;
                }
                sibling->isRed = color(getParent(current));
                getParent(current)->isRed = false;
                sibling->right->isRed = false;
                leftRotate(getParent(current), root);
                current = root;
            }
        } 
        else { 
            Node* sibling = getSibling(current);
            if (color(sibling) == true) {
                sibling->isRed = false;
                getParent(current)->isRed = true;
                rightRotate(getParent(current), root);
                sibling = getParent(current)->left;
            }
            if (color(sibling->right) == false && color(sibling->left) == false) { 
                sibling->isRed = true;
                current = getParent(current);
            }
            else { 
                if (color(sibling->left) == false) { 
                    sibling->right->isRed = false;
                    sibling->isRed = true;
                    leftRotate(sibling, root);
                    sibling = getParent(current)->left;
                }
                sibling->isRed = color(getParent(current));
                getParent(current)->isRed = false;
                sibling->left->isRed = false;
                rightRotate(getParent(current), root);
                current = root;
            }
        }
    }
    if (current != nullptr) { // if node is not null
        current->isRed = false;
    }
}