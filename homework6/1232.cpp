#include <iostream>

using namespace std;

const int maxN = 1e6 + 100;

int disjoinSet[maxN] = {0}, map[1010][1010], cell[maxN][2], ans[maxN], N, A, B,
    sum;
bool isVisited[maxN] = {0}, wall[maxN][4] = {0}, found = 0;
int xPlus[] = {-1, -1, 1, 1}, yPlus[] = {-1, 0, 0, 1};

void generate();

int find(int);

void DFS(int, int, int, bool);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> A >> B;
    generate();

    do {
        int x, y;
        cin >> x >> y;
        wall[x][y] = 1;
        switch (y) {
            case 0:
                if (cell[x][1] > 1 && cell[x][0] > 1) {
                    int temp = map[cell[x][0] - 1][cell[x][1] - 1];
                    wall[temp][3] = 1;
                    x = find(x);
                    temp = find(temp);
                    if (temp >= 1 && temp <= sum) {
                        disjoinSet[temp] = disjoinSet[x];
                    }
                }
                break;
            case 1:
                if (cell[x][0] > 1) {
                    int temp = map[cell[x][0] - 1][cell[x][1]];
                    wall[temp][2] = 1;
                    x = find(x);
                    temp = find(temp);
                    if (temp >= 1 && temp <= sum) {
                        disjoinSet[temp] = disjoinSet[x];
                    }
                }
                break;
            case 2:
                if (cell[x][0] < N) {
                    int temp = map[cell[x][0] + 1][cell[x][1]];
                    wall[temp][1] = 1;
                    x = find(x);
                    temp = find(temp);
                    if (temp >= 1 && temp <= sum) {
                        disjoinSet[temp] = disjoinSet[x];
                    }
                }
                break;
            case 3:
                if (cell[x][0] < N) {
                    int temp = map[cell[x][0] + 1][cell[x][1] + 1];
                    wall[temp][0] = 1;
                    x = find(x);
                    temp = find(temp);
                    if (temp >= 1 && temp <= sum) {
                        disjoinSet[temp] = disjoinSet[x];
                    }
                }
                break;
        }
    } while (find(A) != find(B));

    DFS(A, B, 0, found);

    return 0;
}

void generate() {
    sum = 1;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++) {
            map[i][j] = sum;
            disjoinSet[sum] = sum;
            cell[sum][0] = i;
            cell[sum][1] = j;
            sum++;
        }
    }

    sum -= 1;
}

int find(int x) {
    if (x < 1 || x > sum) {
        return -1;
    }
    int stack[maxN], front = 0;

    while (disjoinSet[x] != x) {
        stack[front++] = x;
        x = disjoinSet[x];
    }

    for (int i = 0; i < front; i++) {
        disjoinSet[stack[i]] = x;
    }

    return x;
}

void DFS(int now, int end, int step, bool found) {
    if (found) {
        return;
    } else if (now == end) {
        ans[step++] = now;

        for (int i = 0; i < step; i++) {
            cout << ans[i] << ' ';
        }
        found = 1;
        return;
    }
    isVisited[now] = 1;
    ans[step++] = now;
    for (int i = 0; i < 4; i++) {
        if (!wall[now][i]) {
            continue;
        } else {
            int temp;
            temp = map[cell[now][0] + xPlus[i]][cell[now][1] + yPlus[i]];
            if (temp != 0 && !isVisited[temp] && (find(temp) == find(end))) {
                DFS(temp, end, step, found);
            }
        }
    }

    isVisited[now] = 0;
    step--;
}