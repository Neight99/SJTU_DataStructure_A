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
    seqQueue(int size = 1000);
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
   public:
    virtual void clear() = 0;
    virtual bool isEmpty() const = 0;
    virtual T Root(T flag) const = 0;
    virtual T parent(T x, T flag) const = 0;
    virtual T lchild(T x, T flag) const = 0;
    virtual T rchild(T x, T flag) const = 0;
    virtual void delLeft(T x) = 0;
    virtual void delRight(T x) = 0;
    virtual void preOrder() const = 0;
    virtual void midOrder() const = 0;
    virtual void postOrder() const = 0;
    virtual void levelOrder() const = 0;
};

template <class T>
class binaryTree : public bTree<T> {
    template <class S>
    friend void printTree(const binaryTree<S> &, S flag);

   private:
    struct Node {
        Node *left, *right;
        T data;

        Node() : left(NULL), right(NULL) {}
        Node(T x, Node *L = NULL, Node *R = NULL)
            : data(x), left(L), right(R) {}
        ~Node() {}
    };
    Node *root;

   public:
    binaryTree() : root(NULL) {}
    binaryTree(T x) { root = new Node(x); }
    ~binaryTree();
    void clear();
    bool isEmpty() const;
    T Root(T flag) const;
    T lchild(T x, T flag) const;
    T rchild(T x, T flag) const;
    void delLeft(T x);
    void delRight(T x);
    void preOrder() const;
    void midOrder() const;
    void postOrder() const;
    void levelOrder() const;
    void createTree(T flag);
    T parent(T x, T flag) const { return flag; }

   private:
    Node *find(T x, Node *t) const;
    void clear(Node *&t);
    void preOrder(Node *t) const;
    void midOrder(Node *t) const;
    void postOrder(Node *t) const;
};

template <class T>
bool binaryTree<T>::isEmpty() const {
    return root == NULL;
}

template <class T>
T binaryTree<T>::Root(T flag) const {
    if (root == NULL) {
        return flag;
    } else {
        return root->data;
    }
}

template <class T>
void binaryTree<T>::clear(binaryTree<T>::Node *&t) {
    if (t == NULL) {
        return;
    }

    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}

template <class T>
void binaryTree<T>::clear() {
    clear(root);
}

template <class T>
binaryTree<T>::~binaryTree() {
    clear(root);
}

template <class T>
void binaryTree<T>::preOrder(binaryTree<T>::Node *t) const {
    if (t == NULL) {
        return;
    }
    cout << t->data << ' ';
    preOrder(t->left);
    preOrder(t->right);
}

template <class T>
void binaryTree<T>::preOrder() const {
    cout << "\n前序遍历：";
    preOrder(root);
}

template <class T>
void binaryTree<T>::postOrder(binaryTree<T>::Node *t) const {
    if (t == NULL) {
        return;
    }
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data << ' ';
}

template <class T>
void binaryTree<T>::postOrder() const {
    cout << "\n后序遍历：";
    postOrder(root);
}

template <class T>
void binaryTree<T>::midOrder(binaryTree<T>::Node *t) const {
    if (t == NULL) {
        return;
    }
    midOrder(t->left);
    cout << t->data << ' ';
    midOrder(t->right);
}

template <class T>
void binaryTree<T>::midOrder() const {
    cout << "\n后序遍历：";
    midOrder(root);
}

template <class T>
void binaryTree<T>::levelOrder() const {
    seqQueue<Node *> que;
    Node *tmp;

    cout << "\n层次遍历：";
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

template <class T>
typename binaryTree<T>::Node *binaryTree<T>::find(
    T x, binaryTree<T>::Node *t) const {
    Node *tmp;
    if (t == NULL) {
        return NULL;
    }
    if (t->data == x) {
        return t;
    }
    if (tmp = find(x, t->left)) {
        return tmp;
    } else {
        return find(x, t->right);
    }
}

template <class T>
void binaryTree<T>::delLeft(T x) {
    Node *tmp = find(x, root);
    if (tmp == NULL) {
        return;
    }
    clear(tmp->left);
}

template <class T>
void binaryTree<T>::delRight(T x) {
    Node *tmp = find(x, root);
    if (tmp == NULL) {
        return;
    }
    clear(tmp->right);
}

template <class T>
T binaryTree<T>::lchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == NULL || tmp->left == NULL) {
        return flag;
    }
    return tmp->left->data;
}

template <class T>
T binaryTree<T>::rchild(T x, T flag) const {
    Node *tmp = find(x, root);
    if (tmp == NULL || tmp->right == NULL) {
        return flag;
    }
    return tmp->right->data;
}

template <class T>
void binaryTree<T>::createTree(T flag) {
    seqQueue<Node *> que;
    Node *tmp;
    T x, ldata, rdata;
    cout << "\n 输入根节点:";
    cin >> x;
    root = new Node(x);
    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        cout << "\n输入 " << tmp->data << "的两个儿子(" << flag
             << "表示空节点):";
        cin >> ldata >> rdata;
        if (ldata != flag) {
            que.enQueue(tmp->left = new Node(ldata));
        }
        if (rdata != flag) {
            que.enQueue(tmp->right = new Node(rdata));
        }
    }

    cout << "create complete!\n";
}

template <class S>
void printTree(const binaryTree<S> &t, S flag) {
    seqQueue<S> q;
    q.enQueue(t.root->data);
    cout << endl;
    while (!q.isEmpty()) {
        char p, l, r;
        p = q.deQueue();
        l = t.lchild(p, flag);
        r = t.rchile(p, flag);
        cout << p << " " << l << " " << r << endl;
        if (l != '@') {
            q.enQueue(l);
        }
        if (r != '@') {
            q.enQueue(r);
        }
    }
}
