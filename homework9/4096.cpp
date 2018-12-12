#include <cstring>
#include <iostream>

using namespace std;

const int maxN = 25 + 10;

struct Node {
    int data;
    Node *next, *prev;

    Node(int d = 0, Node *nxt = 0, Node *pev = 0)
        : data(d), next(nxt), prev(pev) {}
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Node *boxNow[maxN] = {0}, *boxes[maxN] = {0};
    char order1[10], order2[10];
    int N, x, y;
    cin >> N;

    for (int i = 0; i < N; i++) {
        boxes[i] = new Node(i);
        boxNow[i] = boxes[i];
    }

    while (1) {
        cin >> order1;
        if (!strcmp(order1, "quit")) {
            break;
        } else {
            bool flag = 0;

            cin >> x >> order2 >> y;
            Node *temp1 = boxes[x];
            while (temp1 != 0) {
                if (temp1->data == y) {
                    flag = 1;
                    break;
                }
                temp1 = temp1->next;
            }
            temp1 = boxes[y];
            while (temp1 != 0 && !flag) {
                if (temp1->data == x) {
                    flag = 1;
                    break;
                }
                temp1 = temp1->next;
            }
            if (flag) {
                continue;
            }

            if (!strcmp(order1, "move") && !strcmp(order2, "over")) {
                Node *p = boxes[x]->next, *q;
                while (p != 0) {
                    q = p->next;
                    p->prev->next = 0;
                    p->prev = 0;
                    boxNow[p->data] = p;
                    p = q;
                }

                p = boxes[y];
                while (p->next != 0) {
                    p = p->next;
                }
                p->next = boxes[x];
                if (boxes[x]->prev != 0) {
                    boxes[x]->prev->next = 0;
                }
                if (boxNow[x] == boxes[x]) {
                    boxNow[x] = 0;
                }
                boxes[x]->prev = p;
            } else if (!strcmp(order1, "move") && !strcmp(order2, "onto")) {
                Node *p = boxes[x]->next, *q;
                while (p != 0) {
                    q = p->next;
                    p->prev->next = 0;
                    p->prev = 0;
                    boxNow[p->data] = p;
                    p = q;
                }
                p = boxes[y]->next;
                while (p != 0) {
                    q = p->next;
                    p->prev->next = 0;
                    p->prev = 0;
                    boxNow[p->data] = p;
                    p = q;
                }

                p = boxes[y];
                p->next = boxes[x];
                if (boxes[x]->prev != 0) {
                    boxes[x]->prev->next = 0;
                }
                if (boxNow[x] == boxes[x]) {
                    boxNow[x] = 0;
                }
                boxes[x]->prev = p;
            } else if (!strcmp(order1, "pile") && !strcmp(order2, "over")) {
                Node *p = boxes[y];
                while (p->next != 0) {
                    p = p->next;
                }
                p->next = boxes[x];
                if (boxes[x]->prev != 0) {
                    boxes[x]->prev->next = 0;
                }
                if (boxNow[x] == boxes[x]) {
                    boxNow[x] = 0;
                }
                boxes[x]->prev = p;
            } else if (!strcmp(order1, "pile") && !strcmp(order2, "onto")) {
                Node *p = boxes[y]->next, *q;
                while (p != 0) {
                    q = p->next;
                    p->prev->next = 0;
                    p->prev = 0;
                    boxNow[p->data] = p;
                    p = q;
                }

                p = boxes[y];
                while (p->next != 0) {
                    p = p->next;
                }
                p->next = boxes[x];
                if (boxes[x]->prev != 0) {
                    boxes[x]->prev->next = 0;
                }
                if (boxNow[x] == boxes[x]) {
                    boxNow[x] = 0;
                }
                boxes[x]->prev = p;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        cout << i << ':';
        Node *p = boxNow[i];
        while (p != 0) {
            cout << ' ' << p->data;
            p = p->next;
        }
        cout << '\n';
    }

    return 0;
}