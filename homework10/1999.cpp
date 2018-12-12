#include <iostream>

using namespace std;

const int maxN = 1e3 + 10;
const int maxD = 1e9;

template <class elemType>
class seqQueue {
   private:
    elemType *data;
    int maxSize;
    int front, rear;
    void doubleSpace();

   public:
    seqQueue(int size = 1000000);
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

struct Point {
    int x;
    int y;
    int sum;

    Point(int a = 0, int b = 0, int s = 0) : x(a), y(b), sum(s) {}
};

int N, M, boxNum = 0, ans = maxD;
int maze[maxN][maxN] = {0}, note[10][10] = {0}, x0, y0, dx[4] = {-1, 1, 0, 0},
    dy[4] = {0, 0, -1, 1};
Point box[10];
bool isVisited[maxN][maxN] = {0}, choose[10] = {0};

int BFS(int x0, int y0, int x1, int y1);
void DFS(int i, int times, int sum);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < M + 2; j++) {
            if (i == 0 || j == 0 || i == N + 1 || j == M + 1) {
                maze[i][j] = -1;
            } else {
                cin >> maze[i][j];
                if (maze[i][j] == 2) {
                    maze[i][j] = 0;
                    box[0] = Point(i, j);
                } else if (maze[i][j] == 1) {
                    box[++boxNum] = Point(i, j);
                }
            }
        }
    }

    for (int i = 0; i <= boxNum; i++) {
        for (int j = i + 1; j <= boxNum; j++) {
            int temp = BFS(box[i].x, box[i].y, box[j].x, box[j].y);
            note[i][j] = note[j][i] = temp;
        }
    }

    DFS(0, boxNum, 0);

    if (ans == maxD) {
        cout << -1;
    } else {
        cout << ans;
    }

    return 0;
}

int BFS(int x0, int y0, int x1, int y1) {
    seqQueue<Point> que;

    for (int i = 0; i <= N + 1; i++) {
        for (int j = 0; j <= M + 1; j++) {
            isVisited[i][j] = 0;
        }
    }

    isVisited[x0][y0] = 1;
    que.enQueue(Point(x0, y0, 0));

    while (!que.isEmpty()) {
        Point p = que.deQueue();

        for (int i = 0; i < 4; i++) {
            int x2 = p.x + dx[i], y2 = p.y + dy[i];
            if (x2 == x1 && y2 == y1) {
                return p.sum + 1;
            }
            if (!isVisited[x2][y2] && !maze[x2][y2]) {
                isVisited[x2][y2] = 1;
                que.enQueue(Point(x2, y2, p.sum + 1));
            }
        }
    }

    return maxD;
}

void DFS(int i, int times, int sum) {
    if (sum > ans) {
        return;
    } else if (times == 0) {
        ans = sum;
        return;
    } else {
        for (int j = 1; j <= boxNum; j++) {
            if (!choose[j] && note[i][j] != maxD) {
                choose[j] = 1;
                DFS(j, times - 1, sum + note[i][j]);
                choose[j] = 0;
            }
        }
    }
}