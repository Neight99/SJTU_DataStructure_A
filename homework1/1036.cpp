#include <iostream>

using namespace std;

int minTime(long long *);
long long max(long long, long long, long long);

int main() {
    int n;
    long long *times;
    long long w1, sum1, w2, sum2;
    long long wait[3] = {0}, total[3] = {0};
    cin >> n;

    times = new long long[n];

    for (int i = 0; i < n; i++) {
        cin >> times[i];
    }

    //下面是第一种方法
    for (int i = 0; i < n; i += 3) {
        wait[0] += total[0];  //将已经过去的时间加入到该列队伍等待的总时间
        total[0] += times[i];
    }

    for (int i = 1; i < n; i += 3) {
        wait[1] += total[1];
        total[1] += times[i];
    }

    for (int i = 2; i < n; i += 3) {
        wait[2] += total[2];
        total[2] += times[i];
    }

    w1 = wait[0] + wait[1] + wait[2];  //用户等待时间为三列队伍等待时间总和
    sum1 = max(total[0], total[1],
               total[2]);  //花费总时间为三列队伍里最费时间的那个

    wait[0] = wait[1] = wait[2] = total[0] = total[1] = total[2] = 0;

    //下面是第二种方法
    for (int i = 0; i < n; i++) {
        int k = minTime(total);
        wait[k] += total[k];
        total[k] += times[i];
    }
    w2 = wait[0] + wait[1] + wait[2];
    sum2 = max(total[0], total[1], total[2]);

    delete[] times;

    cout << w1 << ' ' << sum1 << '\n' << w2 << ' ' << sum2;
}

int minTime(long long *x) {
    if (x[0] <= x[1] && x[0] <= x[2]) {
        return 0;
    } else if (x[1] <= x[2]) {
        return 1;
    } else {
        return 2;
    }
}

long long max(long long x, long long y, long long z) {
    if (x >= y && x >= z) {
        return x;
    } else if (y >= z) {
        return y;
    } else {
        return z;
    }
}