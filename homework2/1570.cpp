#include <iostream>

using namespace std;

int found(int *, int, int, int);

int main() {
    int n, t;
    int *N, *T;

    scanf("%d", &n);
    scanf("%d", &t);
    N = new int[n];
    T = new int[t];

    for (int i = 0; i < n; i++) {
        cin >> N[i];
    }
    for (int i = 0; i < t; i++) {
        cin >> T[i];
    }

    for (int i = 0; i < t; i++) {
        int m = found(N, T[i], 0, n - 1);
        printf("%d\n", n - 1 - m);
    }
}

int found(int *N, int n, int x, int y) {
    int Middle = (x + y) / 2;
    if (x == y) {
        if (N[x] <= n) {
            return x;
        } else {
            return x - 1;
        }
    } else {
        if (N[Middle] <= n) {
            return found(N, n, Middle + 1, y);
        } else {
            return found(N, n, x, Middle);
        }
    }
}