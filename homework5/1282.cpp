#include <cmath>
#include <iostream>

using namespace std;

const int maxN = 2000 + 100;

long long ans = 1e17, height[maxN] = {0}, height1[maxN] = {0},
          dp[maxN][maxN] = {0};

void qSort(long long *, int, int);
void DP(int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> height[i];
        height1[i] = height[i];
    }
    qSort(height1, 0, n - 1);
    DP(n);
    cout << ans;

    return 0;
}

void qSort(long long *nums, int l, int h) {
    if (l >= h) {
        return;
    }
    int first = l, last = h;
    long long key = nums[first];

    while (first < last) {
        while (first < last && nums[last] >= key) {
            --last;
        }
        nums[first] = nums[last];
        while (first < last && nums[first] <= key) {
            ++first;
        }
        nums[last] = nums[first];
    }
    nums[first] = key;
    qSort(nums, l, first - 1);
    qSort(nums, first + 1, h);
}

void DP(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                if (j == 0) {
                    dp[i][j] = abs(height1[j] - height[i]);
                } else {
                    dp[i][j] = min(abs(height1[j] - height[i]), dp[i][j - 1]);
                }
            } else if (j == 0) {
                dp[i][j] = dp[i - 1][j] + abs(height1[j] - height[i]);
            } else {
                dp[i][j] = min(dp[i - 1][j] + abs(height1[j] - height[i]),
                               dp[i][j - 1]);
            }

            if (i == n - 1) {
                ans = min(ans, dp[i][j]);
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (i == n - 1) {
                if (j == 0) {
                    dp[i][j] = abs(height1[j] - height[i]);
                } else {
                    dp[i][j] = min(abs(height1[j] - height[i]), dp[i][j - 1]);
                }
            } else if (j == 0) {
                dp[i][j] = dp[i + 1][j] + abs(height1[j] - height[i]);
            } else {
                dp[i][j] = min(dp[i + 1][j] + abs(height1[j] - height[i]),
                               dp[i][j - 1]);
            }

            if (i == 0) {
                ans = min(ans, dp[i][j]);
            }
        }
    }

    return;
}