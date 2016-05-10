/*
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел 
K добавляется в правое поддерево root; иначе в левое поддерево root.

Выведите элементы в порядке post-order (снизу вверх)
*/
#include <iostream>

using namespace std;

struct Node {
    int Value;
    Node* Left;
    Node* Right;

    Node(int val) : Value(val), Left(0), Right(0) {}

    ~Node() {
        delete Left;
        delete Right;
    }
};

class Tree {
public:
    Tree() : root(0) {}
    ~Tree() { delete root; }

    void Add(int nodeData);
    void TraverseDFS() {
        TraverseDFS(root);
    }

private:
    Node* root;
 
    void Visit(Node* node) {
        cout << node->Value << " ";
    }

    void TraverseDFS(Node *node);
};

void Tree::TraverseDFS(Node *node) {
    if (node == 0)
        return;

    TraverseDFS(node->Left);
    TraverseDFS(node->Right);
    Visit(node);
}

void Tree::Add(int data) {
    Node* newNode = new Node(data);

    if (root == 0) {
        root = newNode;
        return;
    }

    Node* nextNode = root;
    while (true) {
        if (data < nextNode->Value) {
            if (nextNode->Left != 0)
                nextNode = nextNode->Left;
            else {
                nextNode->Left = newNode;
                return;
            }
        } else {
            if (nextNode->Right != 0)
                nextNode = nextNode->Right;
            else {
                nextNode->Right = newNode;
                return;
            }
        }
    }
}

int main() {
    int value, num = 0;
    cin >> num;

    if (num == 0)
        return 1;

    Tree tree;

    for (int i = 0; i < num; ++i) {
        cin >> value;
        tree.Add(value);
    }

    tree.TraverseDFS();

    return 0;
}