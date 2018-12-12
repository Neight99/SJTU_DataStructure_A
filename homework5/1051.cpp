#include <iostream>

using namespace std;

int compare = 0;

class sLinkList {
   private:
    struct Node {
        int data;
        Node *next;

        Node() : data(0), next(NULL) {}
        Node(int d, Node *n = NULL) : data(d), next(n) {}
        ~Node() {}
    };
    Node *head;
    int Length;

    Node *move(int) const;

   public:
    sLinkList();
    ~sLinkList();
    void push_back(const int &);
    void push_first(const int &);
    void clear();
    void remove(const int &);
    int find(const int &);
    void moveToFirst(const int &);
    int visit(const int &);
};

typename sLinkList::Node *sLinkList::move(int i) const {
    Node *p = head;
    while (i-- >= 0) {
        p = p->next;
    }

    return p;
}

sLinkList::sLinkList() {
    head = new Node;
    Length = 0;
}

sLinkList::~sLinkList() {
    clear();
    delete head;
}

void sLinkList::clear() {
    Node *p = head->next, *q;
    head->next = NULL;
    while (p != NULL) {
        q = p->next;
        delete p;
        p = q;
    }
    Length = 0;
}

void sLinkList::push_back(const int &x) {
    Node *p = move(Length - 1);
    p->next = new Node(x, p->next);
    ++Length;
}

void sLinkList::push_first(const int &x) {
    Node *p = head;
    p->next = new Node(x, p->next);
    ++Length;
}

void sLinkList::remove(const int &i) {
    if (i == -1) {
        return;
    } else {
        Node *p, *q;
        p = move(i - 1);
        q = p->next;
        p->next = q->next;
        delete q;
        --Length;
    }
}

int sLinkList::find(const int &x) {
    int n = 0;
    Node *p = head->next;
    while (p != NULL) {
        compare++;
        if (p->data == x) {
            return n;
        } else {
            p = p->next;
            n++;
        }
    }

    return -1;
}

int sLinkList::visit(const int &x) { return move(x)->data; }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, tmp, pos;
    sLinkList lists;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        lists.push_back(tmp);
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> tmp;
        pos = lists.find(tmp);
        if (pos != -1) {
            lists.remove(pos);
            lists.push_first(tmp);
        }
    }

    cout << compare;

    return 0;
}