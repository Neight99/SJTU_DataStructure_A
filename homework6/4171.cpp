#include <iostream>

using namespace std;

const int maxN = 1e6 + 100;

int n;
int A[maxN], B[maxN];
// bool X[maxN][maxN] = {0};

struct Node {
    int x;
    int y;

    Node(int a = 0, int b = 0) : x(a), y(b) {}

    Node &operator=(const Node &right) {
        if (&right != this) {
            x = right.x;
            y = right.y;
        }

        return *this;
    }

    bool operator<(const Node &right) const {
        return ((A[x] + B[y]) < (A[right.x] + B[right.y]));
    }
};

class priorityQueue {
   private:
    int currentSize;
    Node *data;
    int maxSize;

    void doubleSpace();
    void percolateDown(int);

   public:
    priorityQueue(int capacity = 10);
    ~priorityQueue();
    void enQueue(const Node &x);
    Node deQueue();
};

priorityQueue::priorityQueue(int capacity) : currentSize(0), maxSize(capacity) {
    data = new Node[capacity];
}

priorityQueue::~priorityQueue() { delete[] data; }

void priorityQueue::enQueue(const Node &x) {
    if (currentSize == maxSize - 2) {
        doubleSpace();
    }
    /*if (X[x.x][x.y] == 1) {
        return;
    }*/

    // X[x.x][x.y] = 1;

    int hole = ++currentSize;
    for (; hole > 1 && x < data[hole / 2]; hole /= 2) {
        data[hole] = data[hole / 2];
    }

    data[hole] = x;
}

Node priorityQueue::deQueue() {
    Node minItem;

    minItem = data[1];
    data[1] = data[currentSize--];
    percolateDown(1);
    if (minItem.x + 1 < n) {
        enQueue(Node((minItem.x + 1), (minItem.y)));
    }

    return minItem;
}

void priorityQueue::percolateDown(int hole) {
    int child;
    Node tmp = data[hole];

    for (; hole * 2 <= currentSize; hole = child) {
        child = hole * 2;

        if (child != currentSize && data[child + 1] < data[child]) {
            child++;
        }

        if (data[child] < tmp) {
            data[hole] = data[child];
        } else {
            break;
        }
    }
    data[hole] = tmp;
}

void priorityQueue::doubleSpace() {
    Node *tmp = data;

    maxSize *= 2;

    data = new Node[maxSize];
    for (int i = 0; i < currentSize; i++) {
        data[i] = tmp[i];
    }

    delete[] tmp;
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

priorityQueue gold(maxN * 2);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }

    qSort(A, 0, (n - 1));
    qSort(B, 0, (n - 1));
    for (int i = 0; i < n; i++) {
        gold.enQueue(Node(0, i));
    }

    for (int i = 0; i < n; i++) {
        Node temp = gold.deQueue();
        int ans = A[temp.x] + B[temp.y];
        cout << ans << ' ';
    }

    return 0;
}
