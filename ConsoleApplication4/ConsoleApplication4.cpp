#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRec(root, value);
    }

    Node* search(int value) {
        return searchRec(root, value);
    }

    void remove(int value) {
        root = removeRec(root, value);
    }

    string preOrder() {
        stringstream ss;
        preOrderRec(root, ss);
        return ss.str();
    }

    string inOrder() {
        stringstream ss;
        inOrderRec(root, ss);
        return ss.str();
    }

    void clear() {
        clearRec(root);
        root = nullptr;
    }

    int height() {
        return heightRec(root);
    }

    string toString() {
        return preOrder();
    }

private:
    Node* insertRec(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertRec(node->left, value);
        } else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }

        return node;
    }

    Node* searchRec(Node* node, int value) {
        if (node == nullptr || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return searchRec(node->left, value);
        }

        return searchRec(node->right, value);
    }

    Node* removeRec(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = removeRec(node->left, value);
        } else if (value > node->data) {
            node->right = removeRec(node->right, value);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeRec(node->right, temp->data);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void preOrderRec(Node* node, stringstream& ss) {
        if (node != nullptr) {
            ss << node->data << " ";
            preOrderRec(node->left, ss);
            preOrderRec(node->right, ss);
        }
    }

    void inOrderRec(Node* node, stringstream& ss) {
        if (node != nullptr) {
            inOrderRec(node->left, ss);
            ss << node->data << " ";
            inOrderRec(node->right, ss);
        }
    }

    void clearRec(Node* node) {
        if (node != nullptr) {
            clearRec(node->left);
            clearRec(node->right);
            delete node;
        }
    }

    int heightRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int leftHeight = heightRec(node->left);
        int rightHeight = heightRec(node->right);
        return 1 + max(leftHeight, rightHeight);
    }
};

int main() {
    const int MAX_ORDER = 4;

    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);
        BinaryTree tree;

        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            int random_value = rand();
            tree.insert(random_value);
        }
        clock_t t2 = clock();

        cout << "Tree representation after inserting " << n << " elements: " << tree.toString() << endl;

        double insertTime = (double)(t2 - t1) / CLOCKS_PER_SEC;
        cout << "Insertion time for " << n << " elements: " << insertTime << " seconds" << endl;

        const int m = pow(10, 4);
        int hits = 0;
        t1 = clock();
        for (int i = 0; i < m; i++) {
            int random_value = rand();
            Node* foundNode = tree.search(random_value);
            if (foundNode) {
                hits++;
            }
        }
        t2 = clock();

        double searchTime = (double)(t2 - t1) / CLOCKS_PER_SEC;
        cout << "Search time for " << m << " random searches: " << searchTime << " seconds" << endl;

        int treeHeight = tree.height();
        cout << "Height of the tree: " << treeHeight << endl;

        tree.clear();
    }

    return 0;
}
