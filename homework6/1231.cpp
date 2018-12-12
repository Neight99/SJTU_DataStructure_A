#include <iostream>

using namespace std;

const int maxN = 1e6 + 100;

int size1 = 0;
long long N, X, Y, Xtemp, Ytemp;
long long father[maxN] = {0}, XFather[maxN] = {0};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> X >> Y;
    long long temp1, temp2;

    for (long long i = 1; i <= N; i++) {
        cin >> temp1 >> temp2;
        if (temp1 != 0) {
            father[temp1] = i;
        }
        if (temp2 != 0) {
            father[temp2] = i;
        }
    }

    Xtemp = X;
    Ytemp = Y;
    while (Xtemp != 0) {
        XFather[size1++] = Xtemp;
        Xtemp = father[Xtemp];
    }

    while (Ytemp != 0) {
        for (int i = 0; i < size1; i++) {
            if (XFather[i] == Ytemp) {
                cout << Ytemp << '\n';
                return 0;
            }
        }

        Ytemp = father[Ytemp];
    }

    return 0;
}