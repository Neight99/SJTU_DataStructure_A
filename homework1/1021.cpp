#include <iomanip>
#include <iostream>

using namespace std;

void go(int, int **);
bool stop(int, int **);

int main() {
    int n;
    cin >> n;

    int **mountain = new int *[n];
    for (int i = 0; i < n; i++) {
        mountain[i] = new int[n];
        for (int j = 0; j < n; j++) {
            mountain[i][j] = 0;
        }
    }

    go(n, mountain);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(6) << mountain[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] mountain[i];
    }
    delete[] mountain;

    return 0;
}

void go(int n, int **mountain) {
    int turn = 0, x = 0, y = 0, count1 = 1;
    while (stop(n, mountain)) {
        if (turn == 0) {
            while (y < n && mountain[x][y] == 0) {
                mountain[x][y] = count1;
                count1++;
                y++;
            }
            y--;
            turn = 1;
        } else if (turn == 1) {
            x++;
            while (x < n && mountain[x][y] == 0) {
                mountain[x][y] = count1;
                count1++;
                x++;
            }
            x--;
            turn = 2;
        } else if (turn == 2) {
            y--;
            while (y >= 0 && mountain[x][y] == 0) {
                mountain[x][y] = count1;
                count1++;
                y--;
            }
            y++;
            turn = 3;
        } else if (turn == 3) {
            x--;
            while (x >= 0 && mountain[x][y] == 0) {
                mountain[x][y] = count1;
                count1++;
                x--;
            }
            x++;
            y++;
            turn = 0;
        }
    }
}

bool stop(int n, int **mountain) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mountain[i][j] == 0) {
                return 1;
            }
        }
    }
    return 0;
}