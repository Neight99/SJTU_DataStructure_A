#include <cstring>
#include <iostream>

using namespace std;

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

sLinkList<char> *text[105] = {0};
int lines = 0;

void list1(int, int);

void ins(int, int, char *);

void del(int, int, int);

int main() {
    text[0] = new sLinkList<char>();
    char in;
    char order[10];
    char str[150];
    int x, y, i;
    cin.get(in);
    while (in != '*') {
        if (in == '\n') {
            text[++lines] = new sLinkList<char>();
        } else {
            text[lines]->push(in);
        }
        cin.get(in);
    }

    while (in != '\n') {
        cin.get(in);
    }

    while (1) {
        cin >> order;
        if (strcmp(order, "quit") == 0) {
            break;
        } else if (strcmp(order, "list") == 0) {
            cin >> x >> y;
            list1(x, y);
        } else if (strcmp(order, "ins") == 0) {
            cin >> x >> y;
            i = 0;
            cin.get(in);
            while (1) {
                cin.get(in);
                if (in == '\n') break;
                str[i++] = in;
            }
            str[i] = 0;
            ins(x, y, str);
        } else if (strcmp(order, "del") == 0) {
            cin >> x >> y >> i;
            del(x, y, i);
        } else {
            cout << "Error!" << endl;
        }
    }

    for (int i = 0; i < lines; ++i) {
        text[i]->traverse();
        if (i != lines - 1) {
            cout << endl;
        }
    }
    return 0;
}

void list1(int n1, int n2) {
    if (n1 < 1 || n2 < 1 || n1 > n2 || n1 > lines || n2 > lines) {
        cout << "Error!" << endl;
    } else {
        while (n1 <= n2) {
            text[n1 - 1]->traverse();
            cout << endl;
            ++n1;
        }
    }
}

void ins(int i, int j, char *str) {
    if (i < 1 || j < 1 || i > lines || j > text[i - 1]->length() + 1) {
        cout << "Error!" << endl;
    } else {
        int ind = 0;
        while (str[ind]) {
            text[i - 1]->insert(j - 1 + ind, str[ind]);
            ++ind;
        }
    }
}

void del(int i, int j, int num) {
    if (i < 1 || j < 1 || i > lines || j + num > text[i - 1]->length() + 1) {
        cout << "Error!" << endl;
        return;
    } else {
        while (num--) {
            text[i - 1]->remove(j - 1);
        }
    }
}