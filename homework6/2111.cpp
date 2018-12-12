#include <cstring>
#include <iostream>

using namespace std;

int min(int a, int b) { return (a > b) ? b : a; }

class BinarySearchTree {
   private:
    struct Node {
        int data;
        Node *left;
        Node *right;

        Node(int x = 0, Node *l = 0, Node *r = 0)
            : data(x), left(l), right(r) {}
    };

    int sum;
    Node *root;
    void insert(int x, Node *&rht);
    void deleteNode(int x, Node *&rht);
    void deleteEqual(int x, Node *&rht);
    void find(int x, Node *&rht);
    void clear(Node *&rht);

   public:
    BinarySearchTree();
    ~BinarySearchTree();
    void insert(int x);
    void deleteEqual(int x);
    void find(int x);
    void findIth(int i);
    int findMin(int x);
};

BinarySearchTree::BinarySearchTree() : root(0), sum(0) {}

BinarySearchTree::~BinarySearchTree() { clear(root); }

void BinarySearchTree::clear(Node *&rht) {
    if (rht == 0) {
        return;
    }
    clear(rht->left);
    clear(rht->right);
    delete rht;
    sum--;
}

void BinarySearchTree::insert(int x) { insert(x, root); }

void BinarySearchTree::insert(int x, Node *&rht) {
    if (rht == 0) {
        rht = new Node(x);
        sum++;
    } else if (x < rht->data) {
        insert(x, rht->left);
    } else {
        insert(x, rht->right);
    }
}

void BinarySearchTree::deleteNode(int x, Node *&rhs) {
    if (rhs == 0) {
        return;
    }
    if (x < rhs->data) {
        deleteNode(x, rhs->left);
    } else if (x > rhs->data) {
        deleteNode(x, rhs->right);
    } else if (rhs->left != 0 && rhs->right != 0) {
        Node *p = rhs->right;
        while (p->left != 0) {
            p = p->left;
        }
        rhs->data = p->data;
        deleteNode(rhs->data, rhs->right);
    } else {
        Node *clean = rhs;
        rhs = (rhs->left != 0) ? rhs->left : rhs->right;
        delete clean;
        sum--;
    }
}

void BinarySearchTree::deleteEqual(int x) { deleteEqual(x, root); }

void BinarySearchTree::deleteEqual(int x, Node *&rht) {
    deleteNode(x, root);
    if (sum == 0) {
        root = NULL;
    }
}

void BinarySearchTree::find(int x) { find(x, root); }

void BinarySearchTree::find(int x, Node *&rht) {
    if (rht == 0) {
        cout << "N\n";
    } else if (x == rht->data) {
        cout << "Y\n";
    } else if (x < rht->data) {
        find(x, rht->left);
    } else {
        find(x, rht->right);
    }
}

int BinarySearchTree::findMin(int x) {
    int ans = 2147483646;
    int p;
    Node *n = root;

    while (n != 0) {
        if (x < n->data) {
            ans = min((n->data - x), ans);
            n = n->left;
        } else if (x > n->data) {
            ans = min((x - n->data), ans);
            n = n->right;
        } else {
            return 0;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, order;
    int x;
    BinarySearchTree bst;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> order >> x;
        switch (order) {
            case 0:
                cout << bst.findMin(x) << '\n';
                break;
            case 1:
                bst.insert(x);
                break;
            case 2:
                bst.deleteEqual(x);
                break;
        }
    }

    return 0;
}