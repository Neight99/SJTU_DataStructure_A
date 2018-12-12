#include <cmath>
#include <iostream>

using namespace std;

const int maxN = 1e3 + 100;

int n, m, dp[maxN][maxN] = {0};
char N[maxN] = {0}, M[maxN] = {0};

int DP(int, int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int ans;
    cin >> n >> m >> N >> M;
    ans = DP(n - 1, m - 1);

    cout << ans;
    return 0;
}

int DP(int x, int y) {
    if (x < 0 || y < 0) {
        return 0;
    } else if (dp[x][y] != 0) {
        return dp[x][y];
    } else if (N[x] == M[y]) {
        dp[x][y] = DP(x - 1, y - 1) + 1;
    } else {
        dp[x][y] = max(DP(x - 1, y), DP(x, y - 1));
    }

    return dp[x][y];
}