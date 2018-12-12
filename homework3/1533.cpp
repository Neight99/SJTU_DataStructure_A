#include <iostream>

using namespace std;

int main() {
    int **road, n, x = 1, y = 1, step = 0, turn = 0, x0, y0;
    cin >> n >> x0 >> y0;

    road = new int *[n + 2];

    for (int i = 0; i < n + 2; i++) {
        road[i] = new int[n + 2];
        for (int j = 0; j < n + 2; j++) {
            if (i == 0 || i == n + 1 || j == 0 || j == n + 1) {
                road[i][j] = -1;
            } else {
                road[i][j] = 0;
            }
        }
    }

    road[x0][y0] = 1;

    while (1) {
        if (road[x][y] == 1) {
            break;
        } else if (road[x][y] == -1) {
            if (turn == 0) {
                y--;
                turn = 1;
            } else if (turn == 1) {
                x--;
                turn = 2;
            } else if (turn == 2) {
                y++;
                turn = 3;
            } else if (turn == 3) {
                x++;
                turn = 0;
            }
            road[x][y] = -2;
        } else if (road[x][y] == 0 || road[x][y] == -2) {
            if (road[x][y] == 0) {
                step++;
            }
            road[x][y] = -1;
            if (turn == 0) {
                y++;
            } else if (turn == 1) {
                x++;
            } else if (turn == 2) {
                y--;
            } else if (turn == 3) {
                x--;
            }
        }
    }

    cout << step;

    for (int i = 0; i < n + 2; i++) {
        delete[] road[i];
    }
    delete[] road;

    return 0;
}