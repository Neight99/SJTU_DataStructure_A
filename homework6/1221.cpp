#include <cstring>
#include <iostream>

using namespace std;

int findN;
bool flag;

class BinarySearchTree {
    struct Node {
        int data;
        Node *left;
        Node *right;

        Node(int x = 0, Node *l = 0, Node *r = 0)
            : data(x), left(l), right(r) {}

        Node &operator=(Node &other) {
            if (&other != this) {
                data = other.data;
                left = other.left;
                right = other.right;
            }

            return *this;
        }
    };

    Node *root;
    int sum;
    void clear(Node *&rhs);
    void insert(int x, Node *&rhs);
    bool find(int x, Node *&rhs);
    void find_ith(int x, Node *&rhs);
    void deleteNode(int x, Node *&rhs);
    void deleteLess(int x, Node *&rhs);
    void deleteGreater(int x, Node *&rhs);
    void deleteInterval(int low, int high, Node *&rhs);

   public:
    BinarySearchTree() : root(0), sum(0) {}
    ~BinarySearchTree() { clear(root); }
    void insert(int x) { insert(x, root); }
    bool find(int x) { return find(x, root); }
    void find_ith(int pos) {
        if (pos > sum) {
            flag = 0;
            return;
        }
        flag = 0;
        findN = 0;
        find_ith(pos, root);
    }
    void deleteEqual(int x) {
        deleteNode(x, root);
        if (sum == 0) {
            root = NULL;
        }
    }
    void deleteLess(int x) {
        deleteLess(x, root);
        if (sum == 0) {
            root = NULL;
        }
    }
    void deleteGreater(int x) {
        deleteGreater(x, root);
        if (sum == 0) {
            root = NULL;
        }
    }
    void deleteInterval(int low, int high) {
        deleteInterval(low, high, root);
        if (sum == 0) {
            root = NULL;
        }
    }
};

void BinarySearchTree::clear(Node *&rhs) {
    if (rhs == 0) {
        return;
    } else {
        clear(rhs->left);
        clear(rhs->right);
        delete rhs;
        sum--;
    }
}

void BinarySearchTree::insert(int x, Node *&rhs) {
    if (rhs == 0) {
        sum++;
        rhs = new Node(x);
    } else if (x <= rhs->data) {
        insert(x, rhs->left);
    } else {
        insert(x, rhs->right);
    }
}

bool BinarySearchTree::find(int x, Node *&rhs) {
    if (rhs == 0) {
        return 0;
    } else if (rhs->data == x) {
        return true;
    } else if (x < rhs->data) {
        return find(x, rhs->left);
    } else {
        return find(x, rhs->right);
    }
}
void BinarySearchTree::find_ith(int x, Node *&rhs) {
    if (findN > x) {
        return;
    }
    if (rhs->left != 0) {
        find_ith(x, rhs->left);
    }
    if (x == ++findN) {
        cout << rhs->data << '\n';
        flag = 1;
        return;
    }
    if (rhs->right != 0) {
        find_ith(x, rhs->right);
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

void BinarySearchTree::deleteLess(int x, Node *&rhs) {
    if (rhs == 0) {
        return;
    }
    while (rhs != 0 && x > rhs->data) {
        clear(rhs->left);
        Node *temp = rhs->right;
        delete rhs;
        rhs = temp;
        sum--;
    }
    if (rhs != 0 && x <= rhs->data) {
        deleteLess(x, rhs->left);
    }
}

void BinarySearchTree::deleteGreater(int x, Node *&rhs) {
    if (rhs == 0) {
        return;
    }
    while (rhs != 0 && x < rhs->data) {
        clear(rhs->right);
        Node *temp = rhs->left;
        delete rhs;
        rhs = temp;
        sum--;
    }
    if (rhs != 0 && x >= rhs->data) {
        deleteGreater(x, rhs->right);
    }
}

void BinarySearchTree::deleteInterval(int low, int high, Node *&rhs) {
    if (low >= high || rhs == 0) {
        return;
    }
    while (rhs != 0 && rhs->data < high && rhs->data > low) {
        deleteNode(rhs->data, rhs);
    }

    if (rhs != 0 && rhs->data >= high) {
        deleteInterval(low, high, rhs->left);
    }

    if (rhs != 0 && rhs->data <= low) {
        deleteInterval(low, high, rhs->right);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    BinarySearchTree bst;
    char order[100] = {0};
    int n1, n2;
    int times = 0;

    cin >> times;

    for (int i = 0; i < times; i++) {
        cin >> order;

        if (!strcmp(order, "insert")) {
            cin >> n1;
            bst.insert(n1);
        } else if (!strcmp(order, "delete")) {
            cin >> n1;
            bst.deleteEqual(n1);
        } else if (!strcmp(order, "delete_less_than")) {
            cin >> n1;
            bst.deleteLess(n1);
        } else if (!strcmp(order, "delete_greater_than")) {
            cin >> n1;
            bst.deleteGreater(n1);
        } else if (!strcmp(order, "delete_interval")) {
            cin >> n1 >> n2;
            bst.deleteInterval(n1, n2);
        } else if (!strcmp(order, "find")) {
            cin >> n1;
            bool flag = bst.find(n1);
            if (flag == 1) {
                cout << "Y" << '\n';
            } else {
                cout << "N" << '\n';
            }
        } else if (!strcmp(order, "find_ith")) {
            cin >> n1;
            bst.find_ith(n1);
            if (!flag) {
                cout << "N\n";
            }
        }
    }

    return 0;
}
