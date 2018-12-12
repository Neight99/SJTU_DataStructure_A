#include <iostream>

using namespace std;

const int maxN = 100000;
class bTree {
   private:
    struct Node {
        int data;
        Node *parent;
        Node *left;
        Node *right;

        Node(int d, Node *p = NULL, Node *l = NULL, Node *r = NULL)
            : data(d), parent(p), left(l), right(r) {}
    };
    Node *nodes[maxN + 100] = {NULL};
    void clear(Node *n);
    void preOrder(Node *p) const;

   public:
    bTree();
    ~bTree();
    void add(int n, int a, int b);
    void find(int n);
    void change(int n);
    void preOrder() const;
};

bTree::bTree() {
    Node *tmp = new Node(1);
    nodes[1] = tmp;
}

bTree::~bTree() {
    // clear(nodes[1]);
}

void bTree::clear(Node *n) {
    nodes[n->data] = 0;
    if (n->left) {
        clear(n->left);
    }
    if (n->right) {
        clear(n->right);
    }
    delete n;
}

void bTree::add(int n, int a, int b) {
    if (nodes[n] == NULL || nodes[n]->left != NULL || nodes[n]->right != NULL ||
        nodes[a] != NULL || nodes[b] != NULL || a == b) {
        cout << "Error!" << '\n';
        return;
    }
    nodes[a] = new Node(a, nodes[n], 0, 0);
    nodes[b] = new Node(b, nodes[n], 0, 0);
    nodes[n]->left = nodes[a];
    nodes[n]->right = nodes[b];
    cout << "Ok!" << '\n';
}

void bTree::find(int n) {
    if (nodes[n] == NULL) {
        cout << "Error!" << '\n';
        return;
    }
    if (nodes[n]->parent == NULL) {
        cout << 0 << ' ';
    } else {
        cout << nodes[n]->parent->data << ' ';
    }
    if (nodes[n]->left == NULL) {
        cout << 0 << ' ';
    } else {
        cout << nodes[n]->left->data << ' ';
    }
    if (nodes[n]->right == NULL) {
        cout << 0 << ' ';
    } else {
        cout << nodes[n]->right->data << ' ';
    }
    cout << '\n';

    return;
}

void bTree::change(int n) {
    if (nodes[n] == NULL || n == 1) {
        cout << "Error!" << '\n';
        return;
    }

    Node *tmp = nodes[n]->parent, *lTmp = tmp->left;
    if (tmp->left == nodes[n]) {
        cout << tmp->right->data << '\n';
    } else {
        cout << tmp->left->data << '\n';
    }
    tmp->left = tmp->right;
    tmp->right = lTmp;

    return;
}

void bTree::preOrder() const { preOrder(nodes[1]); }

void bTree::preOrder(Node *p) const {
    if (p == NULL) {
        return;
    }
    cout << p->data << ' ';
    preOrder(p->left);
    preOrder(p->right);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int m, n, a, b, c;
    bTree tree1;

    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> n;
        if (n == 1) {
            cin >> a >> b >> c;
            tree1.add(a, b, c);
        } else if (n == 2) {
            cin >> a;
            tree1.find(a);
        } else if (n == 3) {
            cin >> a;
            tree1.change(a);
        }
    }
    tree1.preOrder();
    return 0;
}