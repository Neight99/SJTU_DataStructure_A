#include <cstring>
#include <iostream>

using namespace std;

const int aMax = 1e7 + 100;
const int bMax = 1e6 + 100;

char A[aMax] = {0}, B[bMax] = {0};
int bNext[aMax] = {0};

void makeNext(char *, int *);

int kmp(char *, char *, int *);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int ans;
    cin >> A >> B;

    ans = kmp(A, B, bNext);

    cout << ans;

    return 0;
}

int kmp(char *A, char *B, int *bNext) {
    int lenA, lenB;

    lenA = strlen(A);
    lenB = strlen(B);

    makeNext(B, bNext);

    for (int i = 0, j = 0; i < lenA; i++) {
        while (j > 0 && B[j] != A[i]) {
            j = bNext[j - 1];
        }
        if (B[j] == A[i]) {
            j++;
        }
        if (j == lenB) {
            return i - lenB + 1;
        }
    }
    return -1;
}

void makeNext(char *B, int *bNext) {
    int lenB = strlen(B);
    bNext[0] = 0;

    for (int i = 1, j = 0; i < lenB; i++) {
        while (j > 0 && B[i] != B[j]) {
            j = bNext[j - 1];
        }
        if (B[i] == B[j]) {
            j++;
        }
        bNext[i] = j;
    }
}