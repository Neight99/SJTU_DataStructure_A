#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
    int pos;
    int data;
};

bool cmp(Node, Node);

int Low(int);

void plus1(int);

int sum1(int);

Node A[100010], B[100010];
int c[100010], d[100010], N, ans;
int main() {
    cin >> N;
    for (int i = 1; i < N + 1; i++) {
        cin >> A[i].data;
        A[i].pos = i;
    }
    for (int i = 1; i < N + 1; i++) {
        cin >> B[i].data;
        B[i].pos = i;
    }

    sort(A + 1, A + N + 1, cmp);
    sort(B + 1, B + N + 1, cmp);

    for (int i = 1; i < N + 1; i++) {
        d[A[i].pos] = B[i].pos;
    }

    for (int i = N; i > 0; i--) {
        plus1(d[i]);
        ans = (ans + sum1(d[i] - 1)) % 99999997;
    }

    cout << ans % 99999997;

    return 0;
}

bool cmp(Node x, Node y) { return x.data < y.data; }

int Low(int x) { return x & (-x); }

void plus1(int x) {
    for (int i = x; i < N + 1; i += Low(i)) {
        c[i]++;
    }
    return;
}

int sum1(int x) {
    int sum = 0;
    for (int i = x; i != 0; i -= Low(i)) {
        sum = (sum + c[i]) % 99999997;
    }

    return sum % 99999997;
}

/*void sort(Node *N,int a,int b) {
    if(a>b) {
        return;
    } else {
        int first = a, last = b;
        Node n = N[first];

        while (first < last) {
            while (first < last && !cmp(N[last], n)) {
                last--;
            }

            N[first] = N[last];

            while (first < last && cmp(N[last], n)) {
                first++;
            }

            N[last] = N[first];
        }
        N[first] = n;
        sort(N, a, first - 1);
        sort(N, first + 1, b);
    }
    for(int i=a;i<b-1;i++) {
        for(int j=a;j<b-i-1;j++) {
            Node tmp;
            if(cmp(N[j],N[j+1])!=0) {
                tmp=N[j];
                N[j]=N[j+1];
                N[j+1]=tmp;
            }
        }
    }
}*/