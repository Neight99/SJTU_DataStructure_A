#include <iostream>

using namespace std;

const int maxN = 2e5 + 100;

struct Mouse {
    int id;
    int score;
    int strength;

    bool operator<(const Mouse &right) {
        if ((score < right.score) || (score == right.score && id > right.id)) {
            return 1;
        } else {
            return 0;
        }
    }

    bool operator>(const Mouse &right) {
        if ((score > right.score) || (score == right.score && id < right.id)) {
            return 1;
        } else {
            return 0;
        }
    }
};

void qSort(Mouse *, int, int);
void contest();
void bubble();

int n, R, N;
Mouse mice[maxN] = {0};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> R;

    N = 2 * n;

    for (int i = 1; i <= N; i++) {
        mice[i].id = i;
        cin >> mice[i].score;
    }
    for (int i = 1; i <= N; i++) {
        cin >> mice[i].strength;
    }

    qSort(mice, 1, N);

    for (int i = 0; i < R; i++) {
        contest();
        bubble();
    }

    for (int i = 1; i <= N; i++) {
        cout << mice[i].id << ' ';
    }

    return 0;
}

void qSort(Mouse *nums, int l, int h) {
    if (l >= h) {
        return;
    }
    Mouse temp = nums[l];
    int i = l, j = l + 1, mid;
    for (; j <= h; j++) {
        if (mice[j] > temp) {
            Mouse temp = mice[j];
            mice[j] = mice[++i];
            mice[i] = temp;
        }
    }
    mice[l] = mice[i];
    mice[i] = temp;
    qSort(nums, l, i - 1);
    qSort(nums, i + 1, h);
}

void contest() {
    int temp1, temp2;

    for (int i = 1; i <= n; i++) {
        temp1 = 2 * i - 1;
        temp2 = 2 * i;

        if (mice[temp1].strength > mice[temp2].strength) {
            mice[temp1].score += 2;
        } else if (mice[temp1].strength < mice[temp2].strength) {
            mice[temp2].score += 2;
        } else {
            mice[temp1].score += 1;
            mice[temp2].score += 1;
        }
    }
}

void bubble() {
    for (int i = 2; i <= N; i++) {
        bool flag = 1;
        for (int j = 1; j <= N - i + 1; j++) {
            if (mice[j + 1] > mice[j]) {
                Mouse temp = mice[j + 1];
                mice[j + 1] = mice[j];
                mice[j] = temp;
                flag = 0;
            }
        }
        if (flag) {
            break;
        }
    }
}