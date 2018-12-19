template <class elemType>
class list {
   public:
    virtual void clear() = 0;
    virtual int length() const = 0;
    virtual void insert(int i, const elemType &x) = 0;
    virtual void remove(int i) = 0;

    virtual elemType visit(int i) const = 0;
    virtual ~list(){};
};

template <class elemType>
class sLinkList : public list<elemType> {
   private:
    struct Node {
        elemType data;
        Node *next;

        Node(const elemType &x, Node *n = NULL) : data(x), next(n) {}
        Node() : next(NULL) {}
        ~Node() {}
    };
    Node *head;
    int Length;

    Node *move(int i) const;

   public:
    sLinkList();

    ~sLinkList() {
        clear();
        delete head;
    }

    void push(const elemType &x) { insert(Length, x); }

    void clear();

    int length() const { return Length; }

    void insert(int i, const elemType &x);

    void remove(int i);

    elemType visit(int i) const;

    void erase(int i);

    void erase(const elemType &x, const elemType &y);

    void traverse() const {
        Node *cur = head->next;
        while (cur) {
            cout << cur->data;
            cur = cur->next;
        }
    }
};

template <class elemType>
void sLinkList<elemType>::erase(const elemType &x, const elemType &y) {
    Node *p = head->next, *q = head;
    while (p) {
        if (p->data > x && p->data < y) {
            q->next = p->next;
            delete p;
            p = q->next;
        } else {
            p = p->next;
            q = q->next;
        }
    }
}

template <class elemType>
typename sLinkList<elemType>::Node *sLinkList<elemType>::move(int i) const {
    Node *p = head;
    while (i-- >= 0) {
        p = p->next;
    }
    return p;
}

template <class elemType>
sLinkList<elemType>::sLinkList() {
    head = new Node;
    Length = 0;
}

template <class elemType>
void sLinkList<elemType>::clear() {
    Node *p = head->next, *q;
    head->next = NULL;
    while (p != NULL) {
        q = p->next;
        delete p;
        p = q;
    }

    Length = 0;
}

template <class elemType>
void sLinkList<elemType>::insert(int i, const elemType &x) {
    Node *pos;
    pos = move(i - 1);
    pos->next = new Node(x, pos->next);
    ++Length;
}

template <class elemType>
void sLinkList<elemType>::remove(int i) {
    Node *pos, *delp;
    pos = move(i - 1);
    delp = pos->next;
    pos->next = delp->next;
    delete delp;
    --Length;
}

template <class elemType>
elemType sLinkList<elemType>::visit(int i) const {
    return move(i)->data;
}

template <class elemType>
void sLinkList<elemType>::erase(int i) {
    elemType tmp = move(i)->data;
    Node *p = head->next;
    int j = 0;
    while (p) {
        if (p->data == tmp) {
            p = p->next;
            remove(j);
        } else {
            p = p->next;
            ++j;
        }
    }
}