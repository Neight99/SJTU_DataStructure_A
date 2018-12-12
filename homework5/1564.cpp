#include <iostream>

using namespace std;

int x0, y0, x1, y1, chessboard[10][10] = {-10}, minCost = 2147483647;
bool visited[10][10] = {0};

void visit(int, int, int, int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int m = 0; m < n; m++) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                cin >> chessboard[i][j];
            }
        }
        cin >> x0 >> y0 >> x1 >> y1;
        visit(x0, y0, 0, 1);
        cout << minCost << '\n';
    }
}

void visit(int x0, int y0, int cost, int status) {
    if (minCost > cost) {
        if (x0 == x1 && y0 == y1) {
            minCost = cost;
            return;
        } else {
            int x2 = x0 - 1, y2 = y0;
            if (x2 >= 0 && x2 < 6 && !visited[x2][y2]) {
                int costTmp = status * chessboard[x2][y2];
                visited[x2][y2] = 1;
                visit(x2, y2, cost + costTmp, costTmp % 4 + 1);
                visited[x2][y2] = 0;
            }
            x2 = x0 + 1, y2 = y0;
            if (x2 >= 0 && x2 < 6 && !visited[x2][y2]) {
                int costTmp = status * chessboard[x2][y2];
                visited[x2][y2] = 1;
                visit(x2, y2, cost + costTmp, costTmp % 4 + 1);
                visited[x2][y2] = 0;
            }
            x2 = x0, y2 = y0 - 1;
            if (y2 >= 0 && y2 < 6 && !visited[x2][y2]) {
                int costTmp = status * chessboard[x2][y2];
                visited[x2][y2] = 1;
                visit(x2, y2, cost + costTmp, costTmp % 4 + 1);
                visited[x2][y2] = 0;
            }
            x2 = x0, y2 = y0 + 1;
            if (y2 >= 0 && y2 < 6 && !visited[x2][y2]) {
                int costTmp = status * chessboard[x2][y2];
                visited[x2][y2] = 1;
                visit(x2, y2, cost + costTmp, costTmp % 4 + 1);
                visited[x2][y2] = 0;
            }
        }
    }
}
