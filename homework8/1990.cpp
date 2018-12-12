#include <iostream>

using namespace std;

const int maxN = 2e6 + 100;

struct Node {
    int id;
    int like;
    int date;
};

int pos[maxN] = {0}, N, M, date = 1;
Node heap[maxN] = {0};

void buildHeap();
void percolateUp(int);
void percolateDown(int);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> heap[i].like;
        heap[i].id = i;
        heap[i].date = date++;
        pos[i] = i;
    }

    buildHeap();

    int x, y;
    for (int i = 0; i < M; i++) {
        cin >> x >> y;
        heap[pos[x]].like += y;
        heap[pos[x]].date = date++;
        if (y > 0) {
            percolateDown(pos[x]);
        } else if (y < 0) {
            percolateUp(pos[x]);
        }
        cout << heap[1].id << '\n';
    }

    return 0;
}

void buildHeap() {
    for (int i = N / 2; i > 0; i--) {
        percolateDown(i);
    }
}

void percolateUp(int hole) {
    int like = heap[hole].like, id = heap[hole].id, date = heap[hole].date,
        parent;

    while (hole / 2 != 0) {
        parent = hole / 2;
        if (like <= heap[parent].like) {
            heap[hole].like = heap[parent].like;
            heap[hole].id = heap[parent].id;
            heap[hole].date = heap[hole].date;
            pos[heap[hole].id] = hole;
            hole = parent;
        } else {
            break;
        }
    }
    heap[hole].id = id;
    heap[hole].like = like;
    heap[hole].date = date;
    pos[id] = hole;
}

void percolateDown(int hole) {
    int like = heap[hole].like, id = heap[hole].id, data = heap[hole].date,
        child;

    while ((hole * 2) <= N) {
        child = hole * 2;
        if (child < N) {
            if (heap[child + 1].like < heap[child].like ||
                (heap[child + 1].like == heap[child].like &&
                 heap[child + 1].date > heap[child].date)) {
                child += 1;
            }
        }
        if (like > heap[child].like ||
            (like == heap[child].like && date < heap[child].date)) {
            heap[hole].like = heap[child].like;
            heap[hole].id = heap[child].id;
            heap[hole].date = heap[child].date;
            pos[heap[hole].id] = hole;
            hole = child;
        } else {
            break;
        }
    }
    heap[hole].id = id;
    heap[hole].date = date;
    heap[hole].like = like;
    pos[id] = hole;
}