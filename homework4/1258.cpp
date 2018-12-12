#include <iostream>

using namespace std;

long long sum = 0, trees[100100], newTrees[100100];
int n;

void cal(int, int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> trees[i];
    }

    cal(0, n - 1);

    cout << sum;

    return 0;
}

void cal(int l, int r) {
    int mid = (l + r) / 2;
    int i, j, tmp;

    if (r > l) {
        cal(l, mid);
        cal(mid + 1, r);
        tmp = l;

        for (i = l, j = mid + 1; i <= mid && j <= r;) {
            if (trees[i] > trees[j]) {
                newTrees[tmp++] = trees[j++];
                sum += mid - i + 1;
            } else {
                newTrees[tmp++] = trees[i++];
            }
        }
        if (i <= mid) {
            for (; i <= mid;) {
                newTrees[tmp++] = trees[i++];
            }
        }

        if (j <= r) {
            for (; j <= r;) {
                newTrees[tmp++] = trees[j++];
            }
        }

        for (i = l; i <= r; i++) {
            trees[i] = newTrees[i];
        }
    }
}