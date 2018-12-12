#include <iostream>

using namespace std;

const int maxN = 4e2 + 10;
int A[maxN][maxN], temp[maxN] = {0}, N, zero[maxN];
long long ans0 = 0, ans1 = 0;

void count();

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int temp1;
            cin >> temp1;
            A[i][j] = temp1 % 2;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp[j] = A[i][j];
        }
        count();
        for (int j = i + 1; j < N; j++) {
            for (int k = 0; k < N; k++) {
                temp[k] += A[j][k];
                temp[k] %= 2;
            }
            count();
        }
        for (int j = 0; j < N; j++) {
            temp[j] = 0;
        }
    }
    ans1 = N * (N + 1) / 2;
    ans1 *= ans1;
    ans1 -= ans0;

    cout << ans0 << ' ' << ans1 << '\n';

    return 0;
}

void count() {
    int t = 0, len = 0;
    for (int i = 0; i < N; i++) {
        t++;
        if (temp[i] == 1) {
            zero[len++] = t;
            t = 0;
        }
    }

    if (len == 0) {
        return;
    } else {
        zero[len++] = ++t;
        for (int i = 0; i < len; i++) {
            for (int j = i + 1; j < len; j += 2) {
                ans0 += (zero[i] * zero[j]);
            }
        }
        len = 0;
    }
}