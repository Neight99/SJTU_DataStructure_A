#include <iostream>

using namespace std;

const int maxN = 1e5 + 100;

template <class Type>
class priorityQueue {
   private:
    int currentSize;
    Type *array;
    int maxSize;

    void doubleSpace();
    // void buildHeap();
    void percolateDown(int);

   public:
    priorityQueue(int capacity = maxN);
    // priorityQueue(const Type data[],int size);
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
        doubleSpace();
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, tmp1, tmp2, tmp3;
    long long strength = 0;
    priorityQueue<int> fruits;

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> tmp1;
        fruits.enQueue(tmp1);
    }

    for (int i = 0; i < N - 1; i++) {
        tmp1 = fruits.deQueue();
        tmp2 = fruits.deQueue();
        tmp3 = tmp1 + tmp2;
        fruits.enQueue(tmp3);
        strength += tmp3;
    }

    cout << strength;
}