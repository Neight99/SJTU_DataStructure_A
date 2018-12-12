#include <cstring>
#include <iostream>

using namespace std;

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
    priorityQueue(int capacity = 20010);
    // priorityQueue(const Type data[],int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    int find(Type, int, int &) const;
    void decrease(const int &, const Type &);
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

template <class Type>
int priorityQueue<Type>::find(Type x, int hole, int &pos) const {
    int left, right, num1, num2;
    if (hole > currentSize) {
        pos = -1;
        return 2147483647;
    } else if (array[hole] > x) {
        pos = hole;
        return array[hole];
    } else {
        num1 = find(x, 2 * hole, left);
        num2 = find(x, 2 * hole + 1, right);

        if (num1 < num2) {
            pos = left;
            return num1;
        } else if (num1 > num2) {
            pos = right;
            return num2;
        } else {
            if (left > right) {
                pos = right;
            } else {
                pos = left;
            }
            return num1;
        }
    }
}

template <class Type>
void priorityQueue<Type>::decrease(const int &x, const Type &n) {
    if (x > currentSize) {
        return;
    } else {
        array[x] -= n;

        if (n > 0) {
            int tmp = x;
            for (; (tmp / 2) != 0 && array[tmp / 2] > array[tmp]; tmp /= 2) {
                Type temp = array[tmp];
                array[tmp] = array[tmp / 2];
                array[tmp / 2] = temp;
            }
        } else {
            percolateDown(x);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int m, x, n, ans;
    char order[10];
    priorityQueue<int> tree;

    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> order;

        if (strcmp(order, "insert") == 0) {
            cin >> n;
            tree.enQueue(n);
        } else if (strcmp(order, "find") == 0) {
            cin >> n;
            tree.find(n, 1, ans);
            cout << ans << '\n';
        } else if (strcmp(order, "decrease") == 0) {
            cin >> x >> n;
            tree.decrease(x, n);
        }
    }

    return 0;
}