#include <iostream>

using namespace std;

const int maxN = 10 + 10;

struct edgeNode {
    int data;
    edgeNode *next;

    edgeNode(int d = 0, edgeNode *n = 0) : data(d), next(n) {}
};

struct verNode {
    int data;
    edgeNode *head;

    verNode(int d = 0, edgeNode *h = 0) : data(d), head(h) {}
};

int n, m, start, M, temp1, temp2, ans = 0;
verNode *nodes[maxN];
bool isVisited[maxN] = {0};

void DFS(int i, int len);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> start >> M;

    for (int i = 1; i <= n; i++) {
        nodes[i] = new verNode(i);
    }

    for (int i = 0; i < m; i++) {
        cin >> temp1 >> temp2;
        bool flag = 1;
        edgeNode *p = nodes[temp1]->head;
        while (p) {
            if (p->data == temp2) {
                flag = 0;
                break;
            }
            p = p->next;
        }
        if (flag) {
            nodes[temp1]->head = new edgeNode(temp2, nodes[temp1]->head);
        }
    }

    DFS(start, 0);

    cout << ans;

    return 0;
}

void DFS(int i, int len) {
    if (isVisited[i]) {
        return;
    }
    isVisited[i] = 1;
    if (len == M) {
        ans++;
        isVisited[i] = 0;
        return;
    }
    edgeNode *p = nodes[i]->head;
    while (p) {
        DFS(p->data, len + 1);
        p = p->next;
    }
    isVisited[i] = 0;
}