#include <iostream>

using namespace std;

const int maxN = 1e5 + 100;
const int maxM = 2e6 + 100;
const int maxD = 1e9;

struct edgeNode {
    int data;
    int weight;
    edgeNode *next;

    edgeNode(int d = 0, int w = 0, edgeNode *n = 0)
        : data(d), weight(w), next(n) {}
};

struct verNode {
    int data;
    edgeNode *head;

    verNode(int d = 0, edgeNode *h = 0) : data(d), head(h) {}
};

struct queueNode {
    int dist;
    int node;

    bool operator<(const queueNode &right) const { return dist < right.dist; }
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
    priorityQueue(int capacity = maxM);
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
    // if (currentSize == maxSize - 1) {
    //     doubleSpace();
    // }

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

int n, m, Start, End, sum = 0, minSum = 0, dis = 0;
int Distance[maxN], prev1[maxN], path[maxN], ansPath[maxN];
verNode *nodes[maxN];
bool known[maxN] = {0}, isVisited[maxN] = {0};

void Dijkstra(int);
void calPath(int, int, int *);
void DFS(int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> Start >> End;

    for (int i = 1; i <= n; i++) {
        nodes[i] = new verNode(i);
    }

    for (int i = 0; i < m; i++) {
        int temp1, temp2, temp3;
        cin >> temp1 >> temp2 >> temp3;
        nodes[temp1]->head = new edgeNode(temp2, temp3, nodes[temp1]->head);
    }

    Dijkstra(Start);
    dis = 0;
    calPath(Start, End, prev1);
    DFS(Start);

    if (dis > Distance[End]) {
        cout << dis << '\n';
    } else {
        cout << Distance[End] << '\n';
    }

    for (int i = 0; i < minSum; i++) {
        cout << ansPath[i] << ' ';
    }

    return 0;
}

void Dijkstra(int start) {
    int sNo;
    edgeNode *p;
    priorityQueue<queueNode> que;
    queueNode min, succ;

    for (int i = 1; i <= n; i++) {
        known[i] = 0;
        Distance[i] = maxD;
    }

    for (sNo = 1; sNo <= n; sNo++) {
        if (nodes[sNo]->data == start) {
            break;
        }
    }

    Distance[sNo] = 0;
    prev1[sNo] = sNo;
    min.dist = 0;
    min.node = sNo;
    que.enQueue(min);

    while (!que.isEmpty()) {
        min = que.deQueue();
        if (known[min.node]) {
            continue;
        } else {
            known[min.node] = 1;
            for (p = nodes[min.node]->head; p; p = p->next) {
                if (!known[p->data] &&
                    Distance[p->data] > min.dist + p->weight) {
                    succ.dist = Distance[p->data] = min.dist + p->weight;
                    prev1[p->data] = min.node;
                    succ.node = p->data;
                    que.enQueue(succ);
                }
            }
        }
    }
}

void calPath(int start, int end, int *prev1) {
    if (start == end) {
        ansPath[minSum++] = nodes[start]->data;
    } else {
        calPath(start, prev1[end], prev1);
        ansPath[minSum++] = nodes[end]->data;
    }
}

void DFS(int now) {
    path[sum++] = now;
    isVisited[now] = 1;

    if (now == End && sum < minSum && dis <= Distance[End]) {
        for (int i = 0; i < sum; i++) {
            ansPath[i] = path[i];
        }
        minSum = sum;
    } else if (now != End && sum < minSum && dis <= Distance[End]) {
        for (edgeNode *p = nodes[now]->head; p; p = p->next) {
            if (!isVisited[p->data]) {
                dis += p->weight;
                DFS(p->data);
                dis -= p->weight;
            }
        }
    }

    sum--;
    isVisited[now] = 0;
}