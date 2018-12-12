#include <iostream>

using namespace std;

const int maxN = 1e5 + 100;

int a[maxN] = {0}, b[maxN] = {0}, c[maxN] = {0};

int LIS(int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, temp, ans;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> temp;
        c[temp] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> temp;
        a[i] = c[temp];
    }

    ans = LIS(n);

    cout << ans;

    return 0;
}

int LIS(int n) {
    int ans = 1;
    b[0] = a[1];

    for (int i = 1; i < n; i++) {
        int left = 0, right = ans - 1, mid = (left + right) / 2;

        while (left < right) {
            if (a[i + 1] == b[mid]) {
                break;
            } else if (a[i + 1] < b[mid]) {
                right = mid;
            } else {
                left = mid + 1;
            }
            mid = (left + right) / 2;
        }

        if (a[i + 1] > b[mid]) {
            mid++;
        }

        if (mid == ans) {
            b[ans++] = a[i + 1];
        } else {
            b[mid] = a[i + 1];
        }
    }

    return ans;
}