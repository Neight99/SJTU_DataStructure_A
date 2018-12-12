#include <iostream>

using namespace std;

const int maxN = 1e6 + 100;

int N, M;
long long WPL = 0;

struct HfNode {
    long long data, sum, depth;

    HfNode(long long d = 0, long long s = 0, long long de = 0)
        : data(d), sum(s), depth(de) {}

    HfNode(const HfNode &right)
        : data(right.data), sum(right.sum), depth(right.depth) {}

    bool operator<(const HfNode &other) const {
        if (data == other.data) {
            return depth > other.depth;
        }
        return data < other.data;
    }

    HfNode &operator=(const HfNode &other) {
        if (&other != this) {
            data = other.data;
            sum = other.sum;
            depth = other.depth;
        }

        return *this;
    }
};

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
    priorityQueue(int capacity = 2 * maxN);
    priorityQueue(const Type *data, int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;
    int Size() const { return currentSize; }
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

priorityQueue<HfNode> que;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        long long d;
        cin >> d;
        HfNode temp(d);
        que.enQueue(temp);
    }

    if ((N - M) % (M - 1)) {
        int tmp = (M - 1) - (N - M) % (M - 1);
        for (int i = 0; i < tmp; i++) {
            HfNode temp;
            que.enQueue(temp);
        }
    }

    while (que.Size() > 1) {
        HfNode sum, temp;

        for (int i = 0; i < M; i++) {
            temp = que.getHead();
            que.deQueue();

            sum.data += temp.data;
            sum.sum += temp.data + temp.sum;

            if (sum.depth <= 0 || sum.depth < temp.depth + 1) {
                sum.depth = temp.depth + 1;
            }
        }
        if (sum.data == 0) {
            sum.depth--;
        }

        que.enQueue(sum);
    }

    WPL = que.getHead().sum;

    cout << WPL;

    return 0;
}
