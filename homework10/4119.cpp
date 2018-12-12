#include <iostream>

using namespace std;

const int maxN = 2e4 + 100;

struct edgeNode {
    int data;
    int weight;
    edgeNode *next;

    edgeNode(int d = 0, int w = 0, edgeNode *n = 0)
        : data(d), weight(w), next(n) {}
};

struct verNode {
    int data;
    edgeNode *head;

    verNode(int d = 0, edgeNode *h = 0) : data(d), head(h) {}
};

struct Node {
    int data;
    int sum;

    Node(int d = 0, int s = 0) : data(d), sum(s) {}
};

int N, A, B, C, sum = 1e9, pos = 0;
int Distance[4][maxN] = {0};
verNode *nodes[maxN];
bool isVisited[maxN] = {0};
Node que[100000];

void BFS(int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> A >> B >> C;

    for (int i = 1; i <= N; i++) {
        nodes[i] = new verNode(i);
    }

    for (int i = 0; i < N - 1; i++) {
        int temp1, temp2, temp3;
        cin >> temp1 >> temp2 >> temp3;
        nodes[temp1]->head = new edgeNode(temp2, temp3, nodes[temp1]->head);
        nodes[temp2]->head = new edgeNode(temp1, temp3, nodes[temp2]->head);
    }

    BFS(A);
    BFS(B);
    BFS(C);

    for (int i = N; i >= 1; i--) {
        int temp = Distance[0][i] + Distance[1][i] + Distance[2][i];
        if (temp <= sum) {
            sum = temp;
            pos = i;
        }
    }

    cout << pos << '\n' << sum;

    return 0;
}

void BFS(int s) {
    for (int i = 0; i <= N; i++) {
        isVisited[i] = 0;
    }

    int head = 0, tail = 0;
    isVisited[s] = 1;
    que[tail++] = Node(s, 0);

    while (head != tail) {
        Node temp = que[head++];
        edgeNode *p = nodes[temp.data]->head;

        while (p != 0) {
            if (isVisited[p->data]) {
                p = p->next;
                continue;
            } else {
                isVisited[p->data] = 1;
                que[tail++] = Node(p->data, temp.sum + p->weight);
                if (s == A) {
                    Distance[0][p->data] = temp.sum + p->weight;
                } else if (s == B) {
                    Distance[1][p->data] = temp.sum + p->weight;
                } else {
                    Distance[2][p->data] = temp.sum + p->weight;
                }
                p = p->next;
            }
        }
    }
}