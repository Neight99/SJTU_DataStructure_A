#include <iostream>

using namespace std;

int main() {
    int money[12] = {0}, cost[12] = {0}, save = 0;
    double total;

    for (int i = 0; i < 12; i++) {
        cin >> cost[i];
    }

    for (int i = 0; i < 12; i++) {
        int save1 = 0;
        money[i] += 300;
        money[i] -= cost[i];

        if (money[i] < 0) {
            cout << '-' << i + 1;
            return 0;
        }

        if (i < 11) {
            save1 = (money[i] / 100) * 100;
            save += save1;
            money[i] -= save1;
            money[i + 1] += money[i];
        }

        if (i == 11) {
            save1 = (money[i] / 100) * 100;
            save += save1;
            money[i] -= save1;
        }
    }

    total = save * 1.2 + money[11];
    cout << total;
    return 0;
}
