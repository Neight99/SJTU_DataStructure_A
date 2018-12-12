#include <iostream>

using namespace std;

const int maxN = 200000 + 100;

int k, n;
long long nums[maxN] = {0}, maxNums[maxN] = {0};

class deque {
   private:
    int data[maxN];
    int f, b;

   public:
    deque() : f(0), b(0) {}

    void push_front(int &x) {
        data[f] = x;
        f += (maxN - 1);
        f %= maxN;
    }

    void push_back(int &x) {
        b = (b + 1) % maxN;
        data[b] = x;
    }

    int front() { return data[(f + 1) % maxN]; }

    int back() { return data[b]; }

    int pop_front() {
        f = (f + 1) % maxN;
        return data[f];
    }

    int pop_back() {
        int temp = data[b];
        b += (maxN - 1);
        b %= maxN;
        return temp;
    }

    bool is_empty() { return f == b; }
};

int main() {
    deque maxNum;

    cin >> k >> n;

    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    for (int i = 1; i <= n; i++) {
        while (!maxNum.is_empty() && nums[i] > nums[maxNum.back()]) {
            maxNum.pop_back();
        }

        if (!maxNum.is_empty() && i - maxNum.front() >= k) {
            maxNum.pop_front();
        }

        maxNum.push_back(i);
        maxNums[i] = nums[maxNum.front()];
    }

    for (int i = k; i <= n; i++) {
        cout << maxNums[i] << ' ';
    }

    return 0;
}