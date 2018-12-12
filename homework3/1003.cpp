#include <iostream>

using namespace std;

int cal(int);

int **pet;

int main() {
    int n, sum;
    cin >> n;

    pet = new int *[n + 2];

    for (int i = 0; i < n + 2; i++) {
        pet[i] = new int[n + 2];
    }

    for (int i = 0; i < n + 2; i++) {
        pet[0][i] = -1;
        pet[n + 1][i] = -1;
        pet[i][0] = -1;
        pet[i][n + 1] = -1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> pet[i][j];
        }
    }
    sum = cal(n);

    cout << sum;

    for (int i = 0; i < n + 2; i++) {
        delete[] pet[i];
    }
    delete[] pet;
}

int cal(int n) {
    int sum = 0;
    bool isFilled = 0;

    while (isFilled != 1) {
        sum++;
        isFilled = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (pet[i][j] == 1) {
                    if (pet[i][j - 1] == 0) {
                        isFilled = 0;
                        pet[i][j - 1] = -2;
                    }
                    if (pet[i][j + 1] == 0) {
                        isFilled = 0;
                        pet[i][j + 1] = -2;
                    }
                    if (pet[i - 1][j] == 0) {
                        isFilled = 0;
                        pet[i - 1][j] = -2;
                    }
                    if (pet[i + 1][j] == 0) {
                        isFilled = 0;
                        pet[i + 1][j] = -2;
                    }
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (pet[i][j] == -2) {
                    pet[i][j] = 1;
                }
            }
        }
    }

    sum--;

    return sum;
}