#include <iostream>

using namespace std;

const int maxN = 1e2 + 100;

int n, m, x1, y1, x2, y2, sjtu[maxN][maxN] = {0}, ans = 1e8;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
bool visited[maxN][maxN] = {0};

struct Node {
    int x, y, sum;

    Node(int a = 0, int b = 0, int c = 0) : x(a), y(b), sum(c) {}
};

template <class elemType>
class seqQueue {
   private:
    elemType *data;
    int maxSize;
    int front, rear;
    void doubleSpace();

   public:
    seqQueue(int size = 1e5);
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
    /*if ((rear + 1) % maxSize == front) {
        doubleSpace();
    }*/
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

seqQueue<Node> que;

void BFS(int, int, int, int, int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> x1 >> y1 >> x2 >> y2;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char temp;
            cin >> temp;
            switch (temp) {
                case '.':
                    sjtu[i][j] = 1;
                    break;
                case '|':
                    sjtu[i][j] = 2;
                    break;
                case '-':
                    sjtu[i][j] = 3;
                    break;
                case '*':
                    sjtu[i][j] = 0;
                    break;
            }
        }
    }

    BFS(x1, y1, x2, y2, 0);

    if (ans == (int)1e8) {
        ans = -1;
    }

    cout << ans;

    return 0;
}

void BFS(int x1, int y1, int x2, int y2, int sum) {
    Node start(x1, y1, 0);
    que.enQueue(start);

    visited[x1][y1] = 1;

    while (!que.isEmpty()) {
        Node now = que.deQueue();

        int temp = sjtu[now.x][now.y];

        if (temp == 1) {
            for (int i = 0; i < 2; i++) {
                if ((sjtu[now.x + dx[i]][now.y] == 1 ||
                     sjtu[now.x + dx[i]][now.y] == 2) &&
                    !visited[now.x + dx[i]][now.y]) {
                    Node next(now.x + dx[i], now.y, now.sum + 1);
                    que.enQueue(next);
                    visited[next.x][next.y] = 1;
                    if (next.x == x2 && next.y == y2) {
                        ans = next.sum;
                        return;
                    }
                }
            }

            for (int i = 2; i < 4; i++) {
                if ((sjtu[now.x][now.y + dy[i]] == 1 ||
                     sjtu[now.x][now.y + dy[i]] == 3) &&
                    !visited[now.x][now.y + dy[i]]) {
                    Node next(now.x, now.y + dy[i], now.sum + 1);
                    que.enQueue(next);
                    visited[next.x][next.y] = 1;
                    if (next.x == x2 && next.y == y2) {
                        ans = next.sum;
                        return;
                    }
                }
            }
        } else if (temp == 2) {
            for (int i = 0; i < 2; i++) {
                if ((sjtu[now.x + dx[i]][now.y] == 1 ||
                     sjtu[now.x + dx[i]][now.y] == 2) &&
                    !visited[now.x + dx[i]][now.y]) {
                    Node next(now.x + dx[i], now.y, now.sum + 1);
                    que.enQueue(next);
                    visited[next.x][next.y] = 1;
                    if (next.x == x2 && next.y == y2) {
                        ans = next.sum;
                        return;
                    }
                }
            }
        } else if (temp == 3) {
            for (int i = 2; i < 4; i++) {
                if ((sjtu[now.x][now.y + dy[i]] == 1 ||
                     sjtu[now.x][now.y + dy[i]] == 3) &&
                    !visited[now.x][now.y + dy[i]]) {
                    Node next(now.x, now.y + dy[i], now.sum + 1);
                    que.enQueue(next);
                    visited[next.x][next.y] = 1;
                    if (next.x == x2 && next.y == y2) {
                        ans = next.sum;
                        return;
                    }
                }
            }
        }
    }
}
