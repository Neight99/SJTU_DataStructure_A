#include <iostream>

using namespace std;

const int maxN = 1e5 + 100;

struct M {
    long long pos;
    long long height;

    M() : pos(0), height(0) {}

    M(long long a, long long b) : pos(a), height(b) {}

    M operator=(M &right) {
        if (&right != this) {
            this->pos = right.pos;
            this->height = right.height;
        }

        return *this;
    }

    M(const M &right) {
        this->pos = right.pos;
        this->height = right.height;
    }
};

void qSort(M *nums, int l, int h) {
    if (l >= h) {
        return;
    }
    int first = l, last = h;
    M key(nums[first]);

    while (first < last) {
        while (first < last && nums[last].pos >= key.pos) {
            --last;
        }
        nums[first] = nums[last];
        while (first < last && nums[first].pos <= key.pos) {
            ++first;
        }
        nums[last] = nums[first];
    }
    nums[first] = key;
    qSort(nums, l, first - 1);
    qSort(nums, first + 1, h);
}

M mountain[maxN] = {};
int n, sum = 0;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        long long p;
        cin >> p;
        mountain[i].pos = p;
    }
    for (int i = 1; i <= n; i++) {
        long long h;
        cin >> h;
        mountain[i].height = h;
    }
    if (n == 1) {
        cout << 1;
        return 0;
    } else if (n == 2) {
        cout << 2;
        return 0;
    }

    qSort(mountain, 1, n);

    for (int i = 2; i < n; i++) {
        if (mountain[i].pos + mountain[i].height < mountain[i + 1].pos ||
            mountain[i].pos - mountain[i].height > mountain[i - 1].pos) {
            sum++;
        }
    }
    sum += 2;

    cout << sum;

    return 0;
}
