#include <iostream>

using namespace std;

const int hashNum = 1e4 + 9;
const int maxN = 1e5 + 10;

int calHash(int x) { return x % hashNum; }

class Hash {
   private:
    struct Node {
        int data;
        int count;
        Node *next;

        Node(int d = 0, int c = 1, Node *ne = 0)
            : data(d), count(c), next(ne) {}
    };
    Node *data[hashNum];

   public:
    Hash() {
        for (int i = 0; i < hashNum; i++) {
            data[i] = 0;
        }
    }

    ~Hash() {
        for (int i = 0; i < hashNum; i++) {
            if (!data[i]) {
                Node *p = data[i], *q;
                while (p != NULL) {
                    q = p->next;
                    delete p;
                    p = q;
                }
            }
        }
    }

    int insert(int x) {
        int index = calHash(x);
        if (!data[index]) {
            data[index] = new Node(x);
            return 1;
        } else {
            Node *p = data[index];
            while (p != NULL && p->data != x) {
                p = p->next;
            }
            if (p != NULL) {
                p->count++;
                return p->count;
            } else {
                p = new Node(x);
                p->next = data[index];
                data[index] = p;
                return 1;
            }
        }
    }

    int remove(int x) {
        int index = calHash(x);
        if (!data[index]) {
            return 0;
        } else {
            Node *p = data[index];
            while (p != NULL && p->data != x) {
                p = p->next;
            }
            if (p != NULL) {
                p->count--;
                return (p->count);
            } else {
                return 0;
            }
        }
    }
};

int input[maxN];
Hash hashLabel;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, K, ans = 0, count = 0, start = 0;
    cin >> N >> K;

    for (int i = 0; i < N; i++) {
        cin >> input[i];
        int temp = hashLabel.insert(input[i]);

        ans = (ans < temp) ? temp : ans;

        if (temp == 1) {
            count++;
        }

        if (count > K + 1) {
            int i;
            for (i = start;; i++) {
                if (hashLabel.remove(input[i]) == 0) {
                    break;
                }
            }
            start = i + 1;
            count--;
        }
    }

    cout << ans << '\n';

    return 0;
}