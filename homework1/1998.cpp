#include <iostream>

using namespace std;

void quickSort(int *, int, int);

int main() {
    int n, *X, left = 0;
    int *counts;
    long long bestsum, sum = 0;
    cin >> n;
    int right = n, on = 0;
    int x0 = 0;

    X = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> X[i];
    }
    quickSort(X, 0, n - 1);

    counts = new int[X[n - 1] + 1];
    for (int i = 0; i < X[n - 1] + 1; i++) {
        counts[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        counts[X[i]] += 1;
    }

    for (int i = 0; i < X[n - 1] + 1; i++) {
        sum += counts[i] * i;
    }
    bestsum = sum;

    for (int i = 0; i < X[n - 1] + 1; i++) {
        left += on;
        on = counts[i];
        right -= counts[i];
        sum = sum + abs(i - x0) * left - abs(i - x0) * (right + on);
        if (bestsum > sum) {
            bestsum = sum;
        }
        x0 = i;
    }

    cout << bestsum;

    return 0;
}

void quickSort(int *s, int l, int r) {
    if (l < r) {
        int i = l, j = r, x = s[l];

        while (i < j) {
            while (i < j && s[j] >= x) {
                j--;
            }

            if (i < j) {
                s[i++] = s[j];
            }

            while (i < j && s[i] < x) {
                i++;
            }

            if (i < j) {
                s[j--] = s[i];
            }
        }
        s[i] = x;
        quickSort(s, l, i - 1);
        quickSort(s, i + 1, r);
    }
}
