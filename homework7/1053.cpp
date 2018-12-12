#include <iostream>

using namespace std;

const int maxN = 1e6 + 100;

struct Node {
    int row;
    int colume;
    int data;

    bool operator<(Node &right) {
        if (row != right.row) {
            return row < right.row;
        } else {
            return colume < right.colume;
        }
    }

    bool operator>(Node &right) {
        if (row != right.row) {
            return row > right.row;
        } else {
            return colume > right.colume;
        }
    }
};

Node arr[maxN];
int row[maxN] = {0}, col[maxN] = {0};

void qSort(Node *, int, int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int r, c, d;
        cin >> r >> c >> d;

        arr[i].row = r;
        arr[i].colume = c;
        arr[i].data = d;
    }

    qSort(arr, 0, n - 1);

    for (int i = 0; i < maxN; i++) {
        row[i] = i;
        col[i] = i;
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        int order, x, y, temp;
        cin >> order >> x >> y;
        switch (order) {
            case 0:
                temp = row[x];
                row[x] = row[y];
                row[y] = temp;
                break;
            case 1:
                temp = col[x];
                col[x] = col[y];
                col[y] = temp;
                break;
            case 2:
                int r = row[x], c = col[y];
                bool flag = 0;
                for (int i = 0; i < n; i++) {
                    if (arr[i].row == r && arr[i].colume == c) {
                        cout << arr[i].data << '\n';
                        flag = 1;
                    }
                }
                if (!flag) {
                    cout << 0 << '\n';
                }
        }
    }

    return 0;
}

void qSort(Node *nums, int l, int h) {
    if (l >= h) {
        return;
    }
    int first = l, last = h;
    Node key = nums[first];

    while (first < last) {
        while (first < last && nums[last] > key) {
            --last;
        }
        nums[first] = nums[last];
        while (first < last && nums[first] < key) {
            ++first;
        }
        nums[last] = nums[first];
    }
    nums[first] = key;
    qSort(nums, l, first - 1);
    qSort(nums, first + 1, h);
}