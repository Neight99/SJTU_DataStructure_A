#include <iostream>

using namespace std;

int **city, **skytim, **home, m, n;

int main() {
    int **city, **skytim, **home, a = 0, b = 0;
    cin >> n >> m;
    int less = m * n;

    city = new int *[m + 2];
    skytim = new int *[m + 2];
    home = new int *[m + 2];

    for (int i = 0; i < m + 2; i++) {
        city[i] = new int[n + 2];
        skytim[i] = new int[n + 2];
        home[i] = new int[n + 2];
    }

    for (int i = 0; i < m + 2; i++) {
        city[i][0] = skytim[i][0] = home[i][0] = -10;
        city[i][n + 1] = skytim[i][n + 1] = home[i][n + 1] = -10;
    }

    for (int i = 0; i < n + 2; i++) {
        city[0][i] = skytim[0][i] = home[0][i] = -10;
        city[m + 1][i] = skytim[m + 1][i] = home[m + 1][i] = -10;
    }

    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            cin >> city[i][j];
            if (city[i][j] == 1) {
                skytim[i][j] = -2;
                home[i][j] = -2;
            } else if (city[i][j] == 2) {
                skytim[i][j] = 0;
                home[i][j] = -1;
                b++;
            } else if (city[i][j] == 3) {
                home[i][j] = 0;
                skytim[i][j] = -1;
                a++;
            } else {
                skytim[i][j] = -1;
                home[i][j] = -1;
                a++;
                b++;
            }
        }
    }

    int N = 0;
    while (a != 0) {
        bool key = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (skytim[i][j] == N) {
                    if (skytim[i - 1][j] == -1) {
                        skytim[i - 1][j] = N + 1;
                        a--;
                        key = 0;
                    }
                    if (skytim[i + 1][j] == -1) {
                        skytim[i + 1][j] = N + 1;
                        a--;
                        key = 0;
                    }
                    if (skytim[i][j - 1] == -1) {
                        skytim[i][j - 1] = N + 1;
                        a--;
                        key = 0;
                    }
                    if (skytim[i][j + 1] == -1) {
                        skytim[i][j + 1] = N + 1;
                        a--;
                        key = 0;
                    }
                }
            }
        }

        if (key == 1) {
            break;
        }

        N++;
    }

    N = 0;
    while (b != 0) {
        bool key = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (home[i][j] == N) {
                    if (home[i - 1][j] == -1) {
                        home[i - 1][j] = N + 1;
                        b--;
                        key = 0;
                    }
                    if (home[i + 1][j] == -1) {
                        home[i + 1][j] = N + 1;
                        b--;
                        key = 0;
                    }
                    if (home[i][j - 1] == -1) {
                        home[i][j - 1] = N + 1;
                        b--;
                        key = 0;
                    }
                    if (home[i][j + 1] == -1) {
                        home[i][j + 1] = N + 1;
                        b--;
                        key = 0;
                    }
                }
            }
        }

        if (key == 1) {
            break;
        }

        N++;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (city[i][j] == 4 && home[i][j] >= 1 && skytim[i][j] >= 1) {
                int tmp = home[i][j] + skytim[i][j];
                less = (tmp < less) ? tmp : less;
            }
        }
    }

    cout << less;
}