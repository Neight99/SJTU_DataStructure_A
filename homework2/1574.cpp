#include <cmath>
#include <iostream>

using namespace std;

int mods(int, int, int);

int main() {
    long long Answer;
    int n, m, k, x;

    cin >> n >> m >> k >> x;
    Answer = m * mods(10, k, n);
    Answer %= n;
    Answer += x;
    Answer %= n;
    cout << Answer << endl;

    return 0;
}

int mods(int x, int y, int n) {
    int Answer = 1;
    x %= n;
    while (y > 0) {
        if (y & 1) {
            Answer *= x;
            Answer %= n;
        }
        y /= 2;
        x = (x * x) % n;
    }

    return Answer;
}
