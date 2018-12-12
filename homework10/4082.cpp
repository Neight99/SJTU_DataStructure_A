#include <iostream>

using namespace std;

const int maxN = 1e6;

struct edgeNode {
    int data;
    edgeNode *next;

    edgeNode(int d = 0, edgeNode *n = 0) : data(d), next(n) {}
};

struct verNode {
    int data;
    edgeNode *head;
    int degree;

    verNode(int d = 0, edgeNode *h = 0) : data(d), head(h), degree(0) {}
};

int N, M, ans = 0, city = 0, degree = 0;
verNode *nodes[maxN];
bool isVisited[maxN] = {0};

void DFS(int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    for (int i = 0; i <= N; i++) {
        nodes[i] = new verNode(i);
    }

    for (int i = 0; i < M; i++) {
        int temp1, temp2;

        cin >> temp1 >> temp2;

        nodes[temp1]->head = new edgeNode(temp2, nodes[temp1]->head);
        nodes[temp1]->degree++;
        nodes[temp2]->head = new edgeNode(temp1, nodes[temp2]->head);
        nodes[temp2]->degree++;
    }

    for (int i = 0; i <= N; i++) {
        if (!isVisited[i]) {
            city = degree = 0;
            DFS(i);
            ans += ((city * (city - 1)) - degree) / 2;
        }
    }

    cout << ans;

    return 0;
}

void DFS(int i) {
    isVisited[i] = 1;
    city++;
    degree += nodes[i]->degree;

    edgeNode *p = nodes[i]->head;

    while (p) {
        if (!isVisited[p->data]) {
            DFS(p->data);
        }
        p = p->next;
    }
}
