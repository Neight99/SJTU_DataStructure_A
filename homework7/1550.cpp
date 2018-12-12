#include <iostream>

using namespace std;

const int maxN = 1e4 + 100;
int height[maxN] = {0};
char input[maxN] = {0};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int k = 0, N, maxHeight = 0, distance = 0;
    long long waterSum = 0;
    bool flag = 0;
    char *ch;
    cin >> N;
    cin >> input;

    ch = input;
    while (*ch) {
        if (*ch >= '0' && *ch <= '9') {
            int temp = 0;
            while (*ch >= '0' && *ch <= '9') {
                temp *= 10;
                temp += (*ch - '0');
                ch++;
            }
            height[k] = temp;
            if (height[k] > maxHeight) {
                maxHeight = height[k];
            }
            k++;
        }
        ch++;
    }

    for (int i = 0; i < maxHeight; i++) {
        int j;
        for (j = 0, flag = 0, distance = 0; j < N; j++) {
            if (height[j] > i && flag == 0) {
                flag = 1;
            } else if (height[j] <= i && flag == 1) {
                distance++;
            }
            if (height[j] > i && flag == 1) {
                waterSum += distance;
                distance = 0;
            }
        }
    }

    cout << waterSum;

    return 0;
}