#include <iostream>

using namespace std;

const int maxN = 1e5 + 100;

int N, B, A[maxN], a[maxN], pos, l[2 * maxN] = {0}, r[2 * maxN] = {0},
                                       left1 = 0, right1 = 0;

int main() {
    int sum=0;

    cin >> N >> B;

    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        if (A[i] > B) {
            a[i] = 1;
        } else if (A[i] == B) {
            a[i] = 0;
            pos = i;
        } else {
            a[i] = -1;
        }
    }

    left1 = right1 = N;

    for (int i = pos; i > 0; i--) {
        left1 += a[i];
        l[left1]++;
    }

    for (int i = pos; i <= N; i++) {
        right1 += a[i];
        r[right1]++;
    }

    for (int i = 1; i <= 2 * N; i++) {
        sum += (l[i] * r[2 * N - i]);
    }

    cout << sum;

    return 0;
}