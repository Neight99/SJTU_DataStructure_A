#include <iostream>

using namespace std;

int main() {
    int M, *Kn, n = 0;

    cin >> M;
    Kn = new int[M];

    Kn[0] = 0;
    for (int i = 1; i < M; i++) {
        cin >> Kn[i];
    }

    for (int i = 2; i < M + 1; i++) {
        n = (n + Kn[M - i + 1]) % i;
    }

    cout << n + 1 << endl;

    return 0;
}