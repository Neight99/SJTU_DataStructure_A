#include <iostream>

using namespace std;

const int maxN = 100;
int DP[maxN][maxN], path[maxN][maxN], tree[maxN] = {0};

int search(int, int);

void output(int, int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> tree[i];
    }
    cout << search(1, n) << '\n';
    output(1, n);

    return 0;
}

int search(int left, int right) {
    if (left > right) {
        return 1;
    } else if (left == right) {
        DP[left][right] = tree[left];
        path[left][right] = left;
    } else if (DP[left][right] > 0) {
        return DP[left][right];
    } else {
        for (int i = left; i <= right; i++) {
            int x = search(left, i - 1) * search(i + 1, right) + tree[i];
            if (x > DP[left][right]) {
                DP[left][right] = x;
                path[left][right] = i;
            }
        }
    }

    return DP[left][right];
}

void output(int left, int right) {
    if (left > right) {
        return;
    }

    cout << path[left][right] << ' ';
    output(left, path[left][right] - 1);
    output(path[left][right] + 1, right);
}
