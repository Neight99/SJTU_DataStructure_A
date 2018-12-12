#include <cstring>
#include <iostream>

using namespace std;

void eInOrder(char *, int, int);
void ePreOrder(char *, int, int);
void ePostOrder(char *, int, int);
void dInOrder(char *, int, int);
void dPreOrder(char *, int, int);
void dPostOrder(char *, int, int);

char *ans;
int index1;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, length;
    char order1[10], order2[10], *S;

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> length >> order1 >> order2;

        S = new char[length + 10];
        cin >> S;
        if (strcmp(order1, "INORDER") == 0) {
            if (strcmp(order2, "ENCODE") == 0) {
                eInOrder(S, length, 1);
                cout << '\n';
            } else {
                ans = new char[length + 10];
                index1 = 0;
                dInOrder(S, length, 1);
                ans[length] = 0;
                cout << ans << '\n';
                delete[] ans;
            }
        } else if (strcmp(order1, "PREORDER") == 0) {
            if (strcmp(order2, "ENCODE") == 0) {
                ePreOrder(S, length, 1);
                cout << '\n';
            } else {
                ans = new char[length + 10];
                index1 = 0;
                dPreOrder(S, length, 1);
                ans[length] = 0;
                cout << ans << '\n';
                delete[] ans;
            }
        } else if (strcmp(order1, "POSTORDER") == 0) {
            if (strcmp(order2, "ENCODE") == 0) {
                ePostOrder(S, length, 1);
                cout << '\n';
            } else {
                ans = new char[length + 10];
                index1 = 0;
                dPostOrder(S, length, 1);
                ans[length] = 0;
                cout << ans << '\n';
                delete[] ans;
            }
        }
    }
}

void eInOrder(char *str, int len, int pos) {
    if (pos > len) {
        return;
    }

    eInOrder(str, len, 2 * pos);
    cout << str[pos - 1];
    eInOrder(str, len, 2 * pos + 1);
}

void ePreOrder(char *str, int len, int pos) {
    if (pos > len) {
        return;
    }

    cout << str[pos - 1];
    ePreOrder(str, len, 2 * pos);
    ePreOrder(str, len, 2 * pos + 1);
}

void ePostOrder(char *str, int len, int pos) {
    if (pos > len) {
        return;
    }

    ePostOrder(str, len, 2 * pos);
    ePostOrder(str, len, 2 * pos + 1);
    cout << str[pos - 1];
}

void dInOrder(char *str, int len, int pos) {
    if (pos > len) {
        return;
    }

    dInOrder(str, len, 2 * pos);
    ans[pos - 1] = str[index1];
    index1++;
    dInOrder(str, len, 2 * pos + 1);
}

void dPreOrder(char *str, int len, int pos) {
    if (pos > len) {
        return;
    }

    ans[pos - 1] = str[index1];
    index1++;
    dPreOrder(str, len, 2 * pos);
    dPreOrder(str, len, 2 * pos + 1);
}

void dPostOrder(char *str, int len, int pos) {
    if (pos > len) {
        return;
    }

    dPostOrder(str, len, 2 * pos);
    dPostOrder(str, len, 2 * pos + 1);
    ans[pos - 1] = str[index1];
    index1++;
}