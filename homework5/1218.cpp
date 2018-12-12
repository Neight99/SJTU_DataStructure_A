#include <iostream>

using namespace std;

const int maxN = 1e5 + 100;
int lists[maxN] = {0}, length = 0;

void qSort(int *, int, int);
bool find(int);
int search(int, int *, int, int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, tmp;
    char order;
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> order >> M;

        if (order == '+') {
            for (int j = 0; j < M; j++) {
                cin >> tmp;
                if (find(tmp)) {
                    lists[length] = tmp;
                    length++;
                }
            }
            qSort(lists, 0, length - 1);
        } else if (order == '-') {
            bool isHere[maxN];
            for (int j = 0; j < length + 10; j++) {
                isHere[j] = 1;
            }

            int listsTmp[maxN] = {0};
            for (int j = 0; j < M; j++) {
                cin >> tmp;
                int pos = search(tmp, lists, 0, length - 1);
                if (pos != -1) {
                    isHere[pos] = 0;
                }
            }
            int lengthTmp = length, pos = 0;
            for (int j = 0; j < lengthTmp; j++) {
                if (!isHere[j]) {
                    length--;
                    continue;
                } else {
                    listsTmp[pos] = lists[j];
                    pos++;
                }
            }

            for (int j = 0; j < length; j++) {
                lists[j] = listsTmp[j];
            }
        } else if (order == '*') {
            bool isHere[maxN] = {0};
            int listsTmp[maxN] = {0};
            for (int j = 0; j < M; j++) {
                cin >> tmp;
                int pos = search(tmp, lists, 0, length - 1);
                if (pos != -1) {
                    isHere[pos] = 1;
                }
            }
            int lengthTmp = length, pos = 0;
            for (int j = 0; j < lengthTmp; j++) {
                if (!isHere[j]) {
                    length--;
                    continue;
                } else {
                    listsTmp[pos] = lists[j];
                    pos++;
                }
            }
            for (int j = 0; j < length; j++) {
                lists[j] = listsTmp[j];
            }
        }

        for (int j = 0; j < length; j++) {
            cout << lists[j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}

void qSort(int *nums, int l, int h) {
    if (l >= h) {
        return;
    }
    int first = l, last = h;
    int key = nums[first];

    while (first < last) {
        while (first < last && nums[last] >= key) {
            --last;
        }
        nums[first] = nums[last];
        while (first < last && nums[first] <= key) {
            ++first;
        }
        nums[last] = nums[first];
    }
    nums[first] = key;
    qSort(nums, l, first - 1);
    qSort(nums, first + 1, h);
}

bool find(int x) {
    for (int i = 0; i < length; i++) {
        if (x == lists[i]) {
            return 0;
        }
    }
    return 1;
}

int search(int x, int *nums, int l, int h) {
    if (l > h) {
        return -1;
    }
    int mid = (l + h) / 2;
    if (nums[mid] == x) {
        return mid;
    } else if (nums[mid] < x) {
        return search(x, nums, mid + 1, h);
    } else if (nums[mid] > x) {
        return search(x, nums, l, mid - 1);
    }

    return -1;
}