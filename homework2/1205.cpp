#include <iostream>

using namespace std;

int Ackerman(int, int);

int main() {
    int m, n, p;
    cin >> m >> n;

    p = Ackerman(m, n);

    cout << p;

    return 0;
}

int Ackerman(int m, int n) {
    int q;

    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return Ackerman(m - 1, 1);
    } else {
        q = Ackerman(m, n - 1);
        return Ackerman(m - 1, q);
    }
}