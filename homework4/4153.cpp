#include <iostream>

using namespace std;

const int maxN = 100000 + 100;
int n, m, k;
long long l, r, mid, ans, pos[maxN];
bool stone[maxN];

void qSort(long long *, int, int);
bool judge(long long);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        cin >> pos[i];
    }
    qSort(pos, 0, n - 1);

    if (pos[0] < 0) {
        for (int i = n - 1; i >= 0; i--) {
            pos[i] -= pos[0];
        }
    }

    l = pos[0];
    r = pos[n - 1];

    while (l <= r) {
        mid = (l + r) / 2;
        if (judge(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << ans;

    return 0;
}

void qSort(long long *num, int l, int h) {
    if (l >= h) {
        return;
    }
    int first = l, last = h;
    long long key = num[first];

    while (first < last) {
        while (first < last && num[last] >= key) {
            --last;
        }
        num[first] = num[last];
        while (first < last && num[first] <= key) {
            ++first;
        }
        num[last] = num[first];
    }
    num[first] = key;
    qSort(num, l, first - 1);
    qSort(num, first + 1, h);
}

bool judge(long long x) {
    if (k == 1) {
        int sum = n - m, now = 0;

        for (int i = 1; i < n - 1; i++) {
            if (pos[i] - pos[now] < x) {
                sum--;
                if (sum < 0) {
                    return 0;
                }
            } else {
                now = i;
            }
        }

        if (pos[n - 1] - pos[now] < x && sum == 0) {
            return 0;
        } else {
            return 1;
        }
    } else {
        int sum = n - m + 1, now = 0;
        for (int i = 0; i < n; i++) {
            stone[i] = 1;
        }

        for (int i = 1; i < n - 1; i++) {
            if (pos[i] - pos[now] < x) {
                sum--;
                stone[i] = 0;
                if (sum < 0) {
                    return 0;
                }
            } else {
                now = i;
            }
        }

        if (pos[n - 1] - pos[now] < x) {
            sum--;
        }
        if (sum > 0) {
            return 1;
        } else if (sum < 0) {
            return 0;
        } else {
            stone[now] = 0;
        }

        int l, r;
        for (int i = 1; i < n - 1; i++) {
            if (stone[i] == 1) {
                continue;
            } else {
                l = i;
                r = i;
                while (stone[l] == 0 && l >= 0) {
                    l--;
                }
                while (stone[r] == 0 && r < n) {
                    r++;
                }

                if (((pos[r] - pos[i]) >= x) || ((pos[i] - pos[l]) >= x)) {
                    return 1;
                }
            }
        }
        return 0;
    }
}