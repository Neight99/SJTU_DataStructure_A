#include <iostream>

using namespace std;

const int maxN = 100000;
int leftNum[maxN + 100] = {0}, rightNum[maxN + 100] = {0},
                   numNum[maxN + 100] = {0};

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
        Node *left;
        Node *right;
        Node *parent;

        Node(T d = 0, Node *p = 0, Node *l = 0, Node *r = 0)
            : data(d), parent(p), left(l), right(r) {}
    };
    Node *root;
    Node *nodes[maxN + 100];
    void clear(Node *);

   public:
    bTree(int n = 10);
    ~bTree();
    void addNode(int, int, T, bool);
    void findRoot();
    void levelOrder() const;
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

    clear(p->left);
    clear(p->right);
    delete p;
}

template <class T>
void bTree<T>::addNode(int n, int i, T x, bool isRight) {
    if (i != 0 && !isRight) {
        nodes[i]->parent = nodes[n];
        nodes[n]->left = nodes[i];
    } else if (i != 0 && isRight) {
        nodes[i]->parent = nodes[n];
        nodes[n]->right = nodes[i];
    }
    nodes[n]->data = x;
}

template <class T>
void bTree<T>::findRoot() {
    root = nodes[1];
    while (root->parent != NULL) {
        root = root->parent;
    }
}

template <class T>
void bTree<T>::levelOrder() const {
    seqQueue<Node *> que;
    Node *tmp;

    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        cout << tmp->data << ' ';
        if (tmp->left) {
            que.enQueue(tmp->left);
        }
        if (tmp->right) {
            que.enQueue(tmp->right);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;

    cin >> N;
    bTree<int> Tree(N);
    for (int i = 1; i <= N; i++) {
        cin >> leftNum[i] >> rightNum[i] >> numNum[i];
    }

    for (int i = 1; i <= N; i++) {
        Tree.addNode(i, leftNum[i], numNum[i], 0);
        Tree.addNode(i, rightNum[i], numNum[i], 1);
    }

    Tree.findRoot();

    Tree.levelOrder();

    return 0;
}