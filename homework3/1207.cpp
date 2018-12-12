#include <iomanip>
#include <iostream>

using namespace std;

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
    seqQueue(int size = 5);
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

int main() {
    int n, nCoach = 0, nTruck = 0, type, time1, totalTime, currentTime = 0;
    double coachTime = 0, truckTime = 0;
    seqQueue<int> q1, q2;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> type >> time1;
        if (!type) {
            q1.enQueue(time1);
            nCoach++;
        } else {
            q2.enQueue(time1);
            nTruck++;
        }
    }

    while (!(q1.isEmpty() && q2.isEmpty())) {
        int coachOnFerry = 0, allOnFerry = 0;

        while (allOnFerry < 10) {
            if (!q1.isEmpty() && q1.getHead() <= currentTime) {
                if (coachOnFerry < 4) {
                    coachTime += currentTime - q1.deQueue();
                    coachOnFerry++;
                    allOnFerry++;
                } else if (!q2.isEmpty() && q2.getHead() <= currentTime) {
                    truckTime += currentTime - q2.deQueue();
                    allOnFerry++;
                    coachOnFerry = 0;
                } else {
                    coachTime += currentTime - q1.deQueue();
                    allOnFerry++;
                    coachOnFerry++;
                }
            } else if (!q2.isEmpty() && q2.getHead() <= currentTime) {
                truckTime += currentTime - q2.deQueue();
                allOnFerry++;
                coachOnFerry = 0;
            } else {
                break;
            }
        }
        currentTime += 10;
    }

    cout << setiosflags(ios::fixed) << setprecision(3) << coachTime / nCoach
         << ' ' << truckTime / nTruck;
}