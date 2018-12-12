#include <iostream>

using namespace std;

void merge(int *&, int *&, int, int);

int main() {
    int N, M, *num1, *num2;

    cin >> N >> M;
    num1 = new int[N + 10];
    num2 = new int[M + 10];

    for (int i = 0; i < N; i++) {
        cin >> num1[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> num2[i];
    }

    if (N == 0) {
        for (int i = 0; i < M; i++) {
            cout << num2[i] << ' ';
        }
    } else if (M == 0) {
        for (int i = 0; i < N; i++) {
            cout << num1[i] << ' ';
        }
    } else if (N == 0 && M == 0) {
        cout << ' ';
    } else {
        merge(num1, num2, N, M);
        for (int i = 0; i < N + M; i++) {
            cout << num1[i] << ' ';
        }
    }

    delete[] num1;
    delete[] num2;
    return 0;
}

void merge(int *&num1, int *&num2, int N, int M) {
    int *ans = new int[N + M + 10], l = 0, r = 0, i = 0;

    while (l < N && r < M) {
        if (num1[l] < num2[r]) {
            ans[i++] = num1[l++];
        } else {
            ans[i++] = num2[r++];
        }
    }

    if (l == N) {
        while (r < M) {
            ans[i++] = num2[r++];
        }
    } else if (r == M) {
        while (l < N) {
            ans[i++] = num1[l++];
        }
    }

    delete[] num1;
    num1 = 0;
    num1 = ans;
}