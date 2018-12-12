#include <iostream>

using namespace std;

const int maxN = 10 + 10;

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

int n, m, Start, End, temp1, temp2, temp3, ans = 1e9;
verNode *nodes[maxN];
bool isVisited[maxN] = {0};

void DFS(int i, int w);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> Start >> End;

    for (int i = 1; i <= n; i++) {
        nodes[i] = new verNode(i);
    }

    for (int i = 0; i < m; i++) {
        cin >> temp1 >> temp2 >> temp3;
        nodes[temp1]->head = new edgeNode(temp2, temp3, nodes[temp1]->head);
    }

    DFS(Start, 0);

    cout << ans;

    return 0;
}

void DFS(int i, int w) {
    if (isVisited[i]) {
        return;
    }
    if (i == End) {
        ans = (w < ans) ? w : ans;
        return;
    }
    isVisited[i] = 1;
    edgeNode *p = nodes[i]->head;
    while (p) {
        DFS(p->data, w + p->weight);
        p = p->next;
    }
    isVisited[i] = 0;
}