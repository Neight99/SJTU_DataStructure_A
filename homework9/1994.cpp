#include <iostream>

using namespace std;

const int maxN = 5e2 + 10;

int N = 0, M = 0, worldMap[maxN][maxN] = {0}, ans = 0;

void DFS(int x, int y);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < M + 2; j++) {
            if (i == 0 || i == N + 1 || j == 0 || j == N + 1) {
                worldMap[i][j] = 0;
            } else {
                int temp;
                cin >> temp;
                worldMap[i][j] = temp + 1;
            }
        }
    }

    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < M + 2; j++) {
            if (worldMap[i][j]) {
                ans++;
                DFS(i, j);
            }
        }
    }

    cout << ans;

    return 0;
}

void DFS(int x, int y) {
    if (!worldMap[x][y]) {
        return;
    } else {
        worldMap[x][y] = 0;
        DFS(x - 1, y);
        DFS(x + 1, y);
        DFS(x, y - 1);
        DFS(x, y + 1);
    }
}