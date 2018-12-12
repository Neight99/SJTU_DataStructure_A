#include <iostream>

using namespace std;

const int maxN = 1e6 + 100;

struct edgeNode {
    int data;
    edgeNode *next;

    edgeNode(int d = 0, edgeNode *n = 0) : data(d), next(n) {}
    ~edgeNode() {
        if (next) {
            delete next;
        }
    }
};

struct verNode {
    int data;
    int size;
    edgeNode *head;

    verNode(int d = 0, int s = 0, edgeNode *h = 0)
        : data(d), size(s), head(h) {}
    ~verNode() {
        if (head) {
            delete head;
        }
    }
};

int T, N, K;
int father[maxN] = {0}, fa;
verNode *nodes[maxN];
bool isVisited[maxN] = {0};

int DFS(int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;

    for (int j = 0; j < T; j++) {
        int ans = 0;
        bool flag = 0;

        cin >> N >> K;

        for (int i = 1; i <= N; i++) {
            father[i] = 0;
            isVisited[i] = 0;
            nodes[i] = new verNode(i);
        }

        for (int i = 1; i < N; i++) {
            int temp1, temp2;
            cin >> temp1 >> temp2;
            father[temp2] = temp1;
            nodes[temp1]->head = new edgeNode(temp2, nodes[temp1]->head);
        }

        for (int i = 1; i <= N; i++) {
            if (!father[i]) {
                fa = i;
                break;
            }
        }

        DFS(fa);

        if (N % K == 0) {
            for (int i = 1; i <= N; i++) {
                if (nodes[i]->size % K == 0) {
                    ans++;
                }
            }
            if (ans == N / K) {
                flag = 1;
            }
        }

        if (flag) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }

        for (int i = 1; i <= N; i++) {
            delete nodes[i];
        }
    }

    return 0;
}

int DFS(int i) {
    if (isVisited[i]) {
        return 0;
    } else {
        isVisited[i] = 1;
        edgeNode *p = nodes[i]->head;
        while (p) {
            nodes[i]->size += DFS(p->data);
            p = p->next;
        }
        return ++(nodes[i]->size);
    }
}