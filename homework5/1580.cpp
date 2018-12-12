#include <iostream>

using namespace std;

const int maxN = 1e6 + 100;

int n;
long long nums[maxN], ans[maxN] = {0};

int m(int left, int right) { return (left >= right) ? left : right; }

int LIS() {
    int max = 0;

    for (int k = 0; k < n; k++) {
        int i = 0, j = max;
        while (i != j) {
            int m = (i + j) / 2;
            if (ans[m] < nums[k]) {
                i = m + 1;
            } else {
                j = m;
            }
        }
        ans[i] = nums[k];
        max = m(i + 1, max);
    }

    return max;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int result;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    result = LIS();

    cout << result;

    return 0;
}