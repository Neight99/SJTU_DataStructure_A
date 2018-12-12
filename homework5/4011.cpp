#include <iostream>

using namespace std;

const int maxN = 10000;

class bigint {
   private:
    long long data[20];
    const long long base = 1e8;

   public:
    bigint(int x = 0);
    bigint& operator=(const bigint&);
    bigint operator+(const bigint&) const;
    bool operator==(const int) const;
    void output() const;
};

bigint::bigint(int x) {
    for (int i = 0; i < 20; i++) {
        data[i] = 0;
    }
    data[0] = x;
}

bigint& bigint::operator=(const bigint& right) {
    for (int i = 0; i < 20; i++) {
        data[i] = right.data[i];
    }

    return *this;
}

bigint bigint::operator+(const bigint& right) const {
    bigint ans(0);
    long long carry = 0;

    for (int i = 0; i < 20 && (carry || data[i] || right.data[i]); i++) {
        ans.data[i] = data[i] + right.data[i] + carry;
        carry = ans.data[i] / base;
        ans.data[i] %= base;
    }

    return ans;
}

bool bigint::operator==(const int x) const {
    for (int i = 19; i > 0; i--) {
        if (data[i] != 0) {
            return 0;
        }
    }

    return data[0] == x;
}

void bigint::output() const {
    int i = 19;
    while (data[i] == 0) {
        i--;
    }

    printf("%lld", data[i]);
    i--;
    for (; i >= 0; i--) {
        printf("%08lld", data[i]);
    }

    return;
}

bigint dp[maxN][maxN];

bigint DP(int, int, int);

int main() {
    int k, h;
    bigint ans;

    scanf("%d%d", &k, &h);
    ans = DP(k, h, k);

    ans.output();

    return 0;
}

bigint DP(int a, int b, int k) {
    if (!(dp[a][b] == 0)) {
        return dp[a][b];
    } else if (b == 2) {
        dp[a][b] = a;
        return dp[a][b];
    } else {
        for (int i = 0; i < a; i++) {
            dp[a][b] = dp[a][b] + DP(k - i, b - 1, k);
        }
        return dp[a][b];
    }
}