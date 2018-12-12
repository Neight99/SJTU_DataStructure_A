#include <iostream>

using namespace std;

const int maxN = 1e4 + 100;
int good[maxN], bad[maxN];

void qSort(int *, int, int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, ans = 0;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> good[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> bad[i];
    }
    qSort(good, 0, N - 1);
    qSort(bad, 0, M - 1);

    int g = 0, b = 0;
    while (g < N && b < M) {
        if (good[g] > bad[b]) {
            b++;
        }
        g++;
    }
    ans = N + b;
    cout << ans;

    return 0;
}

void qSort(int *nums, int l, int h) {
    if (l >= h) {
        return;
    }
    int first = l, last = h;
    int key = nums[first];

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