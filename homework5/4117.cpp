#include <iostream>

using namespace std;

const int maxN = 1e5 + 100;

long long nums[maxN];

long long question(int, int);

void plusn(int, int, long long);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, tmp1, tmp2;
    char order;
    long long tmp3, sum;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> order;

        if (order == 'Q') {
            cin >> tmp1 >> tmp2;
            sum = question(tmp1, tmp2);
            cout << sum << '\n';
        } else if (order == 'C') {
            cin >> tmp1 >> tmp2 >> tmp3;
            plusn(tmp1, tmp2, tmp3);
        }
    }

    return 0;
}

long long question(int x, int y) {
    long long sum = 0;

    for (int i = x; i <= y; i++) {
        sum += nums[i];
    }

    return sum;
}

void plusn(int x, int y, long long n) {
    for (int i = x; i <= y; i++) {
        nums[i] += n;
    }

    return;
}