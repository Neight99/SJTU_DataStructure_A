#include <iostream>

using namespace std;

const int maxN = 3e4 + 100;

long long a[maxN], b[maxN];
long long ans = 0;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> b[i];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            long long temp = (a[i] xor b[j]);
            if (temp > ans) {
                ans = temp;
            }
        }
    }

    cout << ans;

    return 0;
}