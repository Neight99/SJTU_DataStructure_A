#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    cout << n << '=';

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int tmp = 0;
            while (n % i == 0) {
                n /= i;
                tmp++;
            }
            cout << i << '(' << tmp << ')';
        }
    }

    if (n != 1) {
        cout << n << '(' << 1 << ')';
    }

    return 0;
}