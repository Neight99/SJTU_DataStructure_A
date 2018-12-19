template <class T>
class doubleList {
   private:
    struct Node {
        T data;
        Node *next;
        Node *prev;

        Node(T x = 0, Node *n = NULL, Node *p = NULL)
            : data(x), next(p), prev(n) {}
        ~Node() {}
    };
    Node *head, *tail;
    int currentLength;
    Node *move(int i) const;

   public:
    doubleList();
    // doubleList(const doubleList &);
    ~doubleList();
    void insert(int i, T x);
    int search(const T &x) const;
    void clear();
    void remove(int x);
    int length() const;
    T visit(int) const;
    void traverse() const;
    // doubleList operator=(const doubleList &);
};

template <class T>
doubleList<T>::doubleList() {
    head = new Node;

    head->next = tail = new Node(0, head, NULL);
    currentLength = 0;
}

template <class T>
doubleList<T>::~doubleList() {
    clear();
    delete head;
    delete tail;
}

template <class T>
void doubleList<T>::clear() {
    Node *p = head->next, *q;

    head->next = tail;
    tail->prev = head;

    while (p != tail) {
        q = p;
        p = p->next;
        delete q;
    }

    currentLength = 0;
}

template <class T>
typename doubleList<T>::Node *doubleList<T>::move(int i) const {
    Node *p = head;

    while (i-- >= 0) {
        if (p->next == NULL) {
            return NULL;
        }
        p = p->next;
    }

    return p;
}

template <class T>
void doubleList<T>::insert(int i, T x) {
    Node *pos, *tmp;

    pos = move(i);
    tmp = new Node(x, pos->prev, pos);
    pos->prev->next = tmp;
    pos->prev = tmp;

    currentLength++;
}

template <class T>
int doubleList<T>::search(const T &x) const {
    int i = 0;
    Node *pos = head->next;

    for (; pos != tail && pos->data != x; i++) {
        pos = pos->next;
    }
    if (pos == tail) {
        return -1;
    } else {
        return i;
    }
}

template <class T>
void doubleList<T>::remove(int x) {
    Node *tmp = move(x);

    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;

    delete tmp;
}

template <class T>
T doubleList<T>::visit(int i) const {
    return move(i)->data;
}

template <class T>
int doubleList<T>::length() const {
    return currentLength;
}

template <class T>
void doubleList<T>::traverse() const {
    Node *p = head->next;
    cout << endl;
    while (p != tail) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}
