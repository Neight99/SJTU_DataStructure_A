#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;

class num {
    struct node {
        int data;
        node *next;

        node() : next(NULL) {}

        node(int d, node *N = NULL) : data(d), next(N) {}
    };

    node *head;

   public:
    int len;

    num();

    num(const num &other);

    num(int x);

    ~num();

    void show();

    void operate(num &b);

    int sub(num &b);

    void add(num &b);

    void force();
};

void num::add(num &b) {
    int carry = 0, tem;
    node *cur1 = head;
    node *cur2 = b.head;
    while (cur1->next && cur2->next) {
        tem = carry + cur1->data + cur2->data;
        if (tem >= 10) {
            carry = 1;
            tem -= 10;
        } else {
            carry = 0;
        }
        cur1->data = tem;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    while (cur1->next) {
        tem = carry + cur1->data;
        if (tem >= 10) {
            carry = 1;
            tem -= 10;
        } else {
            carry = 0;
        }
        cur1->data = tem;
        cur1 = cur1->next;
    }

    while (cur2->next) {
        tem = carry + cur2->data;
        if (tem >= 10) {
            carry = 1;
            tem -= 10;
        } else {
            carry = 0;
        }
        cur1->data = tem;
        cur1 = cur1->next = new node();
        cur2 = cur2->next;
    }

    if (carry) {
        cur1->data = carry;
        cur1->next = new node();
    }
}

void num::force() {
    ++len;
    head = new node(0, head);
}

num::num(int x) {
    len = 1;
    head = new node();
    head = new node(x, head);
}

num::num(const num &other) {
    len = 0;
    node *p = other.head;
    head = new node(p->data);
    node *cur = head;

    while (1) {
        p = p->next;
        if (!p) {
            break;
        }
        cur = cur->next = new node(p->data);
    }

    len = other.len;
}

void num::show() {
    node *cur = head;
    while (cur->next) {
        cout << cur->data;
        cur = cur->next;
    }
}

void num::operate(num &b) {
    num ans(0);
    node *cur;
    int d, flag;

    while (1) {
        num tem(b), addin(1);
        d = max(0, len - b.len - 1);

        for (int i = 0; i < d; ++i) {
            tem.force();
        }

        flag = sub(tem);

        if (flag) {
            for (int i = 0; i < d; ++i) {
                addin.force();
            }

            ans.add(addin);
        } else {
            break;
        }
    }
    node *out = NULL;
    cur = ans.head;
    while (cur->next) {
        out = new node(cur->data, out);
        cur = cur->next;
    }

    while (out) {
        cout << out->data;
        cur = out;
        out = out->next;
        delete cur;
    }
}

int num::sub(num &b) {
    node *cur1 = head;
    node *cur2 = b.head;
    int lend = 0, tem, last0;

    if (len < b.len) {
        return 0;
    }

    while (cur1->next && cur2->next) {
        tem = cur1->data - cur2->data - lend;
        if (tem < 0) {
            lend = 1;
            tem += 10;
        } else {
            lend = 0;
        }
        cur1->data = tem;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }

    while (cur1->next) {
        tem = cur1->data - lend;
        if (tem < 0) {
            lend = 1;
            tem += 10;
        } else {
            lend = 0;
        }
        cur1->data = tem;
        cur1 = cur1->next;
    }

    if (!cur1->next && !cur2->next && lend) {
        return 0;
    } else {
        cur1 = head;
        while (cur1->next) {
            if (cur1->data != 0) {
                last0 = 0;
            } else {
                ++last0;
            }
            cur1 = cur1->next;
        }

        cur1 = head;

        for (int i = 0; i < len - last0 - 1; ++i) {
            cur1 = cur1->next;
        }

        for (int i = 0; i < last0; ++i) {
            cur2 = cur1->next;
            if (!cur2->next) {
                break;
            }
            cur1->next = cur2->next;
            delete cur2;
        }

        len -= last0;
    }
    return 1;
}

num::num() {
    len = 0;
    head = new node;
    char ch;
    while (1) {
        cin.get(ch);
        if (ch == '\n') break;
        head = new node(ch - '0', head);
        ++len;
    }
}

num::~num() {
    if (len > 0) {
        node *cur = head;
        while (head) {
            head = head->next;
            delete cur;
            cur = head;
        }
    }
}

int main() {
    num n1, n2;
    n1.operate(n2);
    return 0;
}
