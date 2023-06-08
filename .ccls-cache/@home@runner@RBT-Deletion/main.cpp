/*
* Tyler Du
* 5/21/23
* Red Black Tree Deletion
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
        left = NULL;
        right = NULL;
        parent = NULL;
        isRed = true;
    }
};

void insert(Node* &root, Node* current);
void RBTInsert(Node* current, Node* &root);
void print(Node* root, int numTabs);
void leftRotate(Node* current, Node* &root);
void rightRotate(Node* current, Node* &root);
void search(Node* root, int value);
Node* getParent(Node* current);
Node* getGrandparent(Node* current);
Node* getSibling(Node* current);
Node* getUncle(Node* current);
bool color(Node* current);

int main() {
    char input[10];
    bool running = true;
    Node* root = NULL;

    while (running == true) {
        cout << "Add, print, file, or search?" << endl;

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
    if (parent == NULL) { 
        return NULL;
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
    if (grandparent == NULL) { 
        return NULL;
    }
    return getSibling(parent);
}

bool color(Node* current) { // gets color (red or black)
    if (current == NULL) {
        return false;
    }
    return current->isRed;
}

void insert(Node* &root, Node* current) { // inserts node 
    if (root == NULL) { 
        root = current;
        root->isRed = false;
    }
    else { 
        if (current->data < root->data) { 
            if (root->left == NULL) { 
                root->left = current;
                current->parent = root;
            }
            else { 
                insert(root->left, current);
            }
        }
        else { // if greater
            if (root->right == NULL) { 
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
    if (getParent(current) == NULL) { 
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
    if (root == NULL) { 
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
    if (root == NULL) { 
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
    if (currentRight->left != NULL) { 
        cout << "Node is not null" << endl;
        currentRight->left->parent = current;
    }
    currentRight->left = current;
    currentRight->parent = current->parent;
    if (current->parent == NULL) { 
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
    if (currentLeft->right != NULL) { 
        cout << "Node is not null" << endl;
        currentLeft->right->parent = current;
    }
    currentLeft->right = current;
    currentLeft->parent = current->parent;
    if (current->parent == NULL) { 
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