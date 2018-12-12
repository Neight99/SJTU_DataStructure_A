#include <iostream>

using namespace std;

const int maxN = 1e5 + 100;

template <class elemType>
class seqQueue {
   private:
    elemType *data;
    int maxSize;
    int front, rear;
    void doubleSpace();

   public:
    seqQueue(int size = maxN);
    ~seqQueue();
    bool isEmpty() const;
    void enQueue(const elemType &);
    elemType deQueue();
    elemType getHead() const;
    int length() const;
};

template <class elemType>
void seqQueue<elemType>::doubleSpace() {
    elemType *tmp = data;
    data = new elemType[maxSize * 2];

    for (int i = 1; i <= maxSize; i++) {
        data[i] = tmp[(front + i) % maxSize];
    }

    front = 0;
    rear = maxSize;
    maxSize *= 2;
    delete[] tmp;
}

template <class elemType>
seqQueue<elemType>::seqQueue(int size) : maxSize(size), front(0), rear(0) {
    data = new elemType[size];
}

template <class elemType>
seqQueue<elemType>::~seqQueue() {
    delete[] data;
}

template <class elemType>
bool seqQueue<elemType>::isEmpty() const {
    return front == rear;
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x) {
    // if ((rear + 1) % maxSize == front) {
    //     doubleSpace();
    // }
    rear = (rear + 1) % maxSize;
    data[rear] = x;
}

template <class elemType>
elemType seqQueue<elemType>::deQueue() {
    front = (front + 1) % maxSize;
    return data[front];
}

template <class elemType>
elemType seqQueue<elemType>::getHead() const {
    return data[(front + 1) % maxSize];
}

template <class elemType>
int seqQueue<elemType>::length() const {
    return ((rear + maxSize - front) % maxSize);
}

struct edgeNode {
    int data;
    edgeNode *next;

    edgeNode(int d = 0, edgeNode *n = 0) : data(d), next(n) {}
};

struct verNode {
    int data;
    int times;
    edgeNode *head;

    verNode(int d = 0, edgeNode *h = 0) : data(d), times(0), head(h) {}
};

int n, m, temp1, temp2, ans = 0, inDegree[maxN] = {0};
verNode *nodes[maxN];
seqQueue<int> que;

void topSort();

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        nodes[i] = new verNode(i);
    }

    for (int i = 0; i < m; i++) {
        cin >> temp1 >> temp2;
        nodes[temp2]->head = new edgeNode(temp1, nodes[temp2]->head);
    }

    topSort();

    for (int i = 1; i <= n; i++) {
        ans = (nodes[i]->times > ans) ? nodes[i]->times : ans;
    }

    cout << ans;

    return 0;
}

void topSort() {
    edgeNode *p;
    int current;

    for (int i = 1; i <= n; i++) {
        for (p = nodes[i]->head; p; p = p->next) {
            inDegree[p->data]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!inDegree[i]) {
            que.enQueue(i);
            nodes[i]->times++;
        }
    }

    while (!que.isEmpty()) {
        current = que.deQueue();
        for (p = nodes[current]->head; p; p = p->next) {
            if (--inDegree[p->data] == 0) {
                nodes[p->data]->times = nodes[current]->times + 1;
                que.enQueue(p->data);
            }
        }
    }
}
