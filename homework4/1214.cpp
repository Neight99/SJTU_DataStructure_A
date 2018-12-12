#include <iostream>

using namespace std;

const int maxN = 100000;
int leftNum[maxN + 100] = {0}, rightNum[maxN + 100] = {0};
long long int numNum[maxN + 100] = {0};

template <class elemType>
class queue {
   public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType &) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~queue() {}
};

template <class elemType>
class seqQueue : public queue<elemType> {
   private:
    elemType *data;
    int maxSize;
    int front, rear;
    void doubleSpace();

   public:
    seqQueue(int size = maxN + 100);
    ~seqQueue();
    bool isEmpty() const;
    void enQueue(const elemType &);
    elemType deQueue();
    elemType getHead() const;
    int length() const;
};

template <class elemType>
void seqQueue<elemType>::doubleSpace() {
    elemType *tmp = data;
    data = new elemType[maxSize * 2];

    for (int i = 1; i <= maxSize; i++) {
        data[i] = tmp[(front + i) % maxSize];
    }

    front = 0;
    rear = maxSize;
    maxSize *= 2;
    delete[] tmp;
}

template <class elemType>
seqQueue<elemType>::seqQueue(int size) : maxSize(size), front(0), rear(0) {
    data = new elemType[size];
}

template <class elemType>
seqQueue<elemType>::~seqQueue() {
    delete[] data;
}

template <class elemType>
bool seqQueue<elemType>::isEmpty() const {
    return front == rear;
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x) {
    if ((rear + 1) % maxSize == front) {
        doubleSpace();
    }
    rear = (rear + 1) % maxSize;
    data[rear] = x;
}

template <class elemType>
elemType seqQueue<elemType>::deQueue() {
    front = (front + 1) % maxSize;
    return data[front];
}

template <class elemType>
elemType seqQueue<elemType>::getHead() const {
    return data[(front + 1) % maxSize];
}

template <class elemType>
int seqQueue<elemType>::length() const {
    return ((rear + maxSize - front) % maxSize);
}

template <class T>
class bTree {
   private:
    struct Node {
        T data;
        Node *leftSon;
        Node *leftBrother;
        Node *rightBrother;
        Node *parent;

        Node(T d = 0)
            : data(d), parent(0), leftSon(0), leftBrother(0), rightBrother(0) {}
    };
    Node *root;
    Node *nodes[maxN + 100];
    void clear(Node *);
    void preOrder(Node *) const;
    void postOrder(Node *) const;

   public:
    bTree(int n = 10);
    ~bTree();
    void addNode(int, int, T, bool);
    void findRoot();
    void levelOrder() const;
    void preOrder() const;
    void postOrder() const;
};

template <class T>
bTree<T>::bTree(int n) : root(NULL) {
    for (int i = 1; i <= n + 5; i++) {
        nodes[i] = new Node;
    }
}

template <class T>
bTree<T>::~bTree() {
    clear(root);
}

template <class T>
void bTree<T>::clear(Node *p) {
    if (p == NULL) {
        return;
    }

    clear(p->leftSon);
    clear(p->rightBrother);
    delete p;
}

template <class T>
void bTree<T>::addNode(int n, int i, T x, bool isRight) {
    if (i != 0 && !isRight) {
        nodes[i]->parent = nodes[n];
        nodes[n]->leftSon = nodes[i];
    } else if (i != 0 && isRight) {
        nodes[i]->leftBrother = nodes[n];
        nodes[n]->rightBrother = nodes[i];
    }
    nodes[n]->data = x;
}

template <class T>
void bTree<T>::findRoot() {
    root = nodes[1];
    while (root->parent != NULL || root->rightBrother != NULL ||
           root->leftBrother != NULL) {
        if (root->parent != NULL) {
            root = root->parent;
        } else if (root->leftBrother != NULL) {
            root = root->leftBrother;
        }
    }
}

template <class T>
void bTree<T>::levelOrder() const {
    seqQueue<Node *> que;
    Node *tmp, *tmp1;

    cout << root->data << ' ';
    que.enQueue(root);
    while (!que.isEmpty()) {
        tmp = que.deQueue();
        tmp1 = tmp->leftSon;
        while (tmp1) {
            cout << tmp1->data << ' ';
            que.enQueue(tmp1);
            tmp1 = tmp1->rightBrother;
        }
    }
}

template <class T>
void bTree<T>::preOrder(Node *t) const {
    cout << t->data << ' ';

    Node *tmp = t;
    while (tmp->rightBrother != 0 && t == root) {
        preOrder(tmp->rightBrother);
        tmp = tmp->rightBrother;
    }

    if (t->leftSon != 0) {
        preOrder(t->leftSon);
        Node *tmp1 = t->leftSon;
        while (tmp1->rightBrother != 0) {
            preOrder(tmp1->rightBrother);
            tmp1 = tmp1->rightBrother;
        }
    }
}

template <class T>
void bTree<T>::postOrder(Node *t) const {
    Node *tmp = t;
    while (tmp->rightBrother != 0 && t == root) {
        postOrder(tmp->rightBrother);
        tmp = tmp->rightBrother;
    }

    if (t->leftSon != 0) {
        postOrder(t->leftSon);

        Node *tmp1 = t->leftSon;
        while (tmp1->rightBrother != 0) {
            postOrder(tmp1->rightBrother);
            tmp1 = tmp1->rightBrother;
        }
    }
    cout << t->data << ' ';
}

template <class T>
void bTree<T>::preOrder() const {
    preOrder(root);
}

template <class T>
void bTree<T>::postOrder() const {
    postOrder(root);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;

    cin >> N;
    bTree<long long int> Tree(N);
    for (int i = 1; i <= N; i++) {
        cin >> leftNum[i] >> rightNum[i] >> numNum[i];
    }

    for (int i = 1; i <= N; i++) {
        Tree.addNode(i, leftNum[i], numNum[i], 0);
    }
    for (int i = 1; i <= N; i++) {
        Tree.addNode(i, rightNum[i], numNum[i], 1);
    }

    Tree.findRoot();

    Tree.preOrder();
    cout << '\n';
    Tree.postOrder();
    cout << '\n';
    Tree.levelOrder();

    return 0;
}