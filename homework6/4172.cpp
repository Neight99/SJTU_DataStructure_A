#include <cmath>
#include <iostream>

using namespace std;

const int maxN = 1e6 + 100;

bool roses[maxN] = {0};

class segmentTree {
   private:
    struct Node {
        int l;
        int r;
        int lMax;
        int rMax;
        int mMax;
        int amount;
        int add;

        Node() : l(0), r(0), lMax(0), rMax(0), mMax(0), amount(0), add(0) {}
    };
    Node *data;
    int length;

    void buildTree(int X, int l, int r);
    void update(int X, int l, int r, bool c);
    void pushUp(int X);
    void pushDown(int X);
    int searchMany(int X, int l, int r);
    int searchLongest(int X, int l, int r);

   public:
    segmentTree(int l = maxN) : length(l) { data = new Node[length * 4 + 100]; }
    ~segmentTree() { delete[] data; }

    void buildTree(int n);
    void update(int l, int r, bool c);
    int searchMany(int l, int r);
    int searchLongest(int l, int r);
};

void segmentTree::pushUp(int X) {
    int leftSon = 2 * X, rightSon = 2 * X + 1,
        leftLength = data[leftSon].r - data[leftSon].l + 1,
        rightLength = data[rightSon].r - data[rightSon].l + 1;

    data[X].lMax = data[leftSon].lMax;
    data[X].rMax = data[rightSon].rMax;
    if (data[X].lMax == leftLength) {
        data[X].lMax += data[rightSon].lMax;
    }
    if (data[X].rMax == rightLength) {
        data[X].rMax += data[leftSon].rMax;
    }
    data[X].amount = data[leftSon].amount + data[rightSon].amount;
    data[X].mMax =
        max(max(data[leftSon].rMax + data[rightSon].lMax, data[leftSon].mMax),
            data[rightSon].mMax);
}

void segmentTree::pushDown(int X) {
    int leftSon = 2 * X, rightSon = 2 * X + 1;
    if (data[X].add == 0) {
        return;
    } else if (data[X].l != data[X].r) {
        int add = data[X].add;
        data[leftSon].add = data[rightSon].add = add;
        if (add == 1) {
            data[leftSon].lMax = data[leftSon].rMax = data[leftSon].amount =
                data[leftSon].mMax = 0;
            data[rightSon].lMax = data[rightSon].rMax = data[rightSon].amount =
                data[rightSon].mMax = 0;
        } else if (add == 2) {
            data[leftSon].lMax = data[leftSon].rMax = data[leftSon].amount =
                data[leftSon].mMax = data[leftSon].r - data[leftSon].l + 1;
            data[rightSon].lMax = data[rightSon].rMax = data[rightSon].amount =
                data[rightSon].mMax = data[rightSon].r - data[rightSon].l + 1;
        }
        data[X].add = 0;
    }
}

void segmentTree::buildTree(int n) { buildTree(1, 1, n); }

void segmentTree::buildTree(int X, int l, int r) {
    data[X].add = 0;
    data[X].l = l;
    data[X].r = r;
    if (l == r) {
        data[X].lMax = roses[l];
        data[X].rMax = roses[l];
        data[X].mMax = roses[l];
        data[X].amount = roses[l];
        return;
    }
    int mid = (l + r) >> 1;
    buildTree(2 * X, l, mid);
    buildTree(2 * X + 1, mid + 1, r);
    pushUp(X);
}

void segmentTree::update(int l, int r, bool c) { update(1, l, r, c); }

void segmentTree::update(int X, int l, int r, bool c) {
    if (l <= data[X].l && r >= data[X].r) {
        if (c == 0) {
            data[X].lMax = data[X].mMax = data[X].rMax = data[X].amount = 0;
        } else {
            data[X].lMax = data[X].mMax = data[X].rMax = data[X].amount =
                data[X].r - data[X].l + 1;
        }

        data[X].add = c + 1;
    } else {
        int mid = (data[X].l + data[X].r) >> 1;
        pushDown(X);

        if (l <= mid) {
            update(2 * X, l, r, c);
        }
        if (r > mid) {
            update(2 * X + 1, l, r, c);
        }

        pushUp(X);
    }
}

int segmentTree::searchMany(int l, int r) { return searchMany(1, l, r); }

int segmentTree::searchMany(int X, int l, int r) {
    if (data[X].l > r || data[X].r < l) {
        return 0;
    } else if (l <= data[X].l && data[X].r <= r) {
        return data[X].amount;
    } else {
        int mid = (data[X].l + data[X].r) >> 1;

        pushDown(X);

        int ans = 0;

        return searchMany(2 * X, l, r) + searchMany(2 * X + 1, l, r);
    }
}

int segmentTree::searchLongest(int l, int r) { return searchLongest(1, l, r); }

int segmentTree::searchLongest(int X, int l, int r) {
    if (data[X].l > r || data[X].r < l) {
        return 0;
    } else if (data[X].l >= l && data[X].r <= r) {
        return data[X].mMax;
    } else {
        if (data[X].add != 0) {
            pushDown(X);
        }
        int mid = (data[X].l + data[X].r) >> 1;

        if (r <= mid) {
            return searchLongest(2 * X, l, r);
        } else if (l > mid) {
            return searchLongest(2 * X + 1, l, r);
        } else {
            int left1 = searchLongest(2 * X, l, r),
                right1 = searchLongest(2 * X + 1, l, r);
            int leftRight = data[2 * X].rMax, rightLeft = data[2 * X + 1].lMax;
            if (leftRight > mid - l + 1) {
                leftRight = mid - l + 1;
            }
            if (rightLeft > r - mid) {
                rightLeft = r - mid;
            }

            return max(max(left1, right1), (leftRight + rightLeft));
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    segmentTree smt;

    for (int i = 1; i < n + 1; i++) {
        cin >> roses[i];
    }

    smt.buildTree(n);

    for (int i = 0; i < m; i++) {
        int order, l, r, x, ans;
        cin >> order;
        switch (order) {
            case 1:
                cin >> l >> r >> x;
                smt.update(l, r, x);
                break;
            case 3:
                cin >> l >> r;
                ans = smt.searchLongest(l, r);
                cout << ans << '\n';
                break;
            case 2:
                cin >> l >> r;
                ans = smt.searchMany(l, r);
                cout << ans << '\n';
                break;
        }
    }

    return 0;
}