#include <iostream>

using namespace std;

const int maxN = 1e5 + 100;

struct Node {
    int data;
    Node *next;

    Node(int d = 0, Node *n = 0) : data(d), next(n) {}
};

Node son[maxN] = {0};
int father[maxN] = {0}, Size[maxN] = {0}, ans[maxN] = {};
bool isNode[maxN] = {0};

int DFS(int, int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, k = 0, root;
    cin >> N;
    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        son[u].data = u;
        son[v].data = v;
        ans[u] = ans[v] = 1;
        if ((!isNode[u] && !isNode[v]) || (isNode[u] && !isNode[v])) {
            Node *p = &(son[u]);
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = new Node(v);
            father[v] = u;
            isNode[u] = isNode[v] = 1;
        } else if (isNode[v] && isNode[u]) {
            Node *p = &son[v];
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = new Node(u);
            father[u] = v;
            isNode[u] = isNode[v] = 1;
        }
    }

    for (int i = 1; i <= N; i++) {
        if (father[i] == 0) {
            root = i;
            break;
        }
    }

    DFS(root, N);

    for (int i = 1; i <= N; i++) {
        bool flag = 1;
        Node *p = &son[i];
        while (p->next != NULL) {
            p = p->next;
            if (Size[p->data] > N / 2) {
                flag = 0;
                break;
            }
        }
        if (N - Size[i] - 1 > N / 2) {
            flag = 0;
        }
        if (flag) {
            ans[k] = i;
            k++;
        }
    }

    for (int i = 0; i < k; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}

int DFS(int x, int N) {
    if (son[x].next == NULL) {
        return 1;
    } else {
        Node *p = &(son[x]);
        while (p->next != NULL) {
            p = p->next;
            Size[x] += DFS(p->data, N);
        }
        return Size[x] + 1;
    }
}