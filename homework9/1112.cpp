#include <iostream>

using namespace std;

struct student {
    int num;
    int knowledge;

    bool operator<(const student &right) const {
        return knowledge < right.knowledge;
    }
};

const int maxN = 1e3 + 10;

int interest[maxN] = {0}, n, k;
bool rec[maxN][maxN] = {0}, inque[maxN] = {0};
student stu[maxN] = {0};

template <class Type>
class priorityQueue {
   private:
    int currentSize;
    Type *array;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int);

   public:
    priorityQueue(int capacity = maxN);
    priorityQueue(const Type *data, int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
};

template <class Type>
priorityQueue<Type>::priorityQueue(int capacity)
    : maxSize(capacity), currentSize(0) {
    array = new Type[capacity];
}

template <class Type>
priorityQueue<Type>::priorityQueue(const Type *data, int size)
    : maxSize(size + 10), currentSize(size) {
    array = new Type[maxSize];

    for (int i = 0; i < size; i++) {
        array[i + 1] = data[i];
    }

    buildHeap();
}

template <class Type>
priorityQueue<Type>::~priorityQueue() {
    delete[] array;
}

template <class Type>
bool priorityQueue<Type>::isEmpty() const {
    return currentSize == 0;
}

template <class Type>
Type priorityQueue<Type>::getHead() const {
    return array[1];
}

template <class Type>
void priorityQueue<Type>::enQueue(const Type &x) {
    if (currentSize == maxSize - 1) {
        // doubleSpace();
    }

    int hole = ++currentSize;
    for (; hole > 1 && x < array[hole / 2]; hole /= 2) {
        array[hole] = array[hole / 2];
    }

    array[hole] = x;
}

template <class Type>
Type priorityQueue<Type>::deQueue() {
    Type minItem;

    minItem = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);

    return minItem;
}

template <class Type>
void priorityQueue<Type>::percolateDown(int hole) {
    int child;
    Type tmp = array[hole];

    for (; hole * 2 <= currentSize; hole = child) {
        child = hole * 2;

        if (child != currentSize && array[child + 1] < array[child]) {
            child++;
        }

        if (array[child] < tmp) {
            array[hole] = array[child];
        } else {
            break;
        }
    }
    array[hole] = tmp;
}

template <class Type>
void priorityQueue<Type>::doubleSpace() {
    Type *tmp = array;

    maxSize *= 2;

    array = new Type[maxSize];
    for (int i = 0; i < currentSize; i++) {
        array[i] = tmp[i];
    }

    delete[] tmp;
}

template <class Type>
void priorityQueue<Type>::buildHeap() {
    for (int i = currentSize / 2; i > 0; i--) {
        percolateDown(i);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    priorityQueue<student> que;

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        stu[i].num = i;
        cin >> stu[i].knowledge;
        stu[i].knowledge = -stu[i].knowledge;
    }
    for (int i = 0; i < k; i++) {
        int temp;
        cin >> temp;
        que.enQueue(stu[temp]);
        inque[temp] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> rec[i][j];
        }
    }

    while (!que.isEmpty()) {
        int temp = que.deQueue().num;
        cout << temp << '\n';

        for (int i = 1; i <= n; i++) {
            if (!inque[i] && rec[temp][i]) {
                que.enQueue(stu[i]);
                inque[i] = 1;
            }
        }
    }

    return 0;
}