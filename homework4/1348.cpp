#include <iomanip>
#include <iostream>

using namespace std;

int lengths[100100] = {0}, boyTimes[1000100], girlTimes[1000100];

template <class elemType>
class queue {
   public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const elemType &) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~queue() {}
};

template <class elemType>
class seqQueue : public queue<elemType> {
   private:
    elemType *data;
    int maxSize;
    int front, rear;
    void doubleSpace();

   public:
    seqQueue(int size = 10000000);
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
    maxSize *= 2;
    delete tmp;
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
    if ((rear + 1) % maxSize == front) {
        doubleSpace();
    }
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

void qSort(int *, int, int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, people, currentSong = 0, currentTime = 0, boySum = 0, girlSum = 0;
    double boyWait = 0, girlWait = 0;
    seqQueue<int> boys, girls;

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> lengths[i];
    }

    cin >> people;
    for (int i = 0; i < people; i++) {
        int tmp, times1;
        cin >> tmp >> times1;
        if (tmp == 1) {
            boyTimes[boySum] = times1;
            boySum++;
        } else if (tmp == 2) {
            girlTimes[girlSum] = times1;
            girlSum++;
        }
    }

    qSort(boyTimes, 0, boySum - 1);
    qSort(girlTimes, 0, girlSum - 1);

    for (int i = 0; i < boySum; i++) {
        boys.enQueue(boyTimes[i]);
    }
    for (int i = 0; i < girlSum; i++) {
        girls.enQueue(girlTimes[i]);
    }

    for (int currentSong = -1; currentSong < N; currentSong++) {
        if (currentSong == -1) {
            currentTime = 0;
        } else if (currentSong == N - 2) {
            currentTime += lengths[currentSong];
            while (!boys.isEmpty()) {
                boyWait += currentTime - boys.deQueue();
            }
            while (!girls.isEmpty()) {
                girlWait += currentTime - girls.deQueue();
            }
            break;
        } else {
            currentTime += lengths[currentSong];
        }

        while (!boys.isEmpty() && !girls.isEmpty() &&
               boys.getHead() <= currentTime &&
               girls.getHead() <= currentTime) {
            boyWait += currentTime - boys.deQueue();
            girlWait += currentTime - girls.deQueue();
        }
    }
    cout << setiosflags(ios::fixed) << setprecision(2) << (boyWait / boySum)
         << ' ' << (girlWait / girlSum);

    return 0;
}

void qSort(int *num, int l, int h) {
    if (l >= h) {
        return;
    }
    int first = l, last = h, key = num[first];

    while (first < last) {
        while (first < last && num[last] >= key) {
            --last;
        }
        num[first] = num[last];
        while (first < last && num[first] <= key) {
            ++first;
        }
        num[last] = num[first];
    }
    num[first] = key;
    qSort(num, l, first - 1);
    qSort(num, first + 1, h);
}