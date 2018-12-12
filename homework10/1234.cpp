#include <iostream>

using namespace std;

const int maxN = 1e4 + 100;
const int maxM = 1e5 + 100;

struct edge {
    int beg;
    int end;
    int weight;
};

class DisjointSet {
   private:
    int size;
    int *parent;

   public:
    DisjointSet(int s);
    ~DisjointSet() { delete[] parent; }
    void Union(int root1, int root2);
    int Find(int x);
};

DisjointSet::DisjointSet(int n) : size(n) {
    parent = new int[size];
    for (int i = 0; i < size; i++) {
        parent[i] = -1;
    }
}

int DisjointSet::Find(int x) {
    if (parent[x] < 0) {
        return x;
    }
    return parent[x] = Find(parent[x]);
}

void DisjointSet::Union(int root1, int root2) {
    root1 = Find(root1);
    root2 = Find(root2);
    if (root1 == root2) {
        return;
    } else if (parent[root1] < parent[root2]) {
        parent[root1] += parent[root2];
        parent[root2] = root1;
    } else {
        parent[root2] += parent[root1];
        parent[root1] = root2;
    }
}

edge e[maxM];
int ans = 0, n, m;

void qSort(edge *, int, int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    DisjointSet ds(n + 10);

    for (int i = 1; i <= m; i++) {
        int temp1, temp2, temp3;
        cin >> temp1 >> temp2 >> temp3;
        e[i].beg = temp1;
        e[i].end = temp2;
        e[i].weight = temp3;
    }

    qSort(e, 1, m);

    for (int i = 1; i <= m; i++) {
        int from = e[i].beg, to = e[i].end;
        if (ds.Find(from) != ds.Find(to)) {
            ds.Union(from, to);
            ans += e[i].weight;
        }
    }

    cout << ans;

    return 0;
}

void qSort(edge *nums, int l, int h) {
    if (l >= h) {
        return;
    }
    int first = l, last = h, wmid = e[(first + last) / 2].weight;
    while (first <= last) {
        while (e[first].weight < wmid) {
            first++;
        }
        while (e[last].weight > wmid) {
            last--;
        }
        if (first <= last) {
            edge temp = e[last];
            e[last] = e[first];
            e[first] = temp;
            first++;
            last--;
        }
    }
    qSort(nums, l, last);
    qSort(nums, first, h);
}