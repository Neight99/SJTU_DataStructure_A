#include <cstring>
#include <iostream>

using namespace std;

char tree[100000] = {0}, Left[100000], Middle[100000];

char* subString(char* str, int l, int r) {
    if (r < l) {
        return NULL;
    }
    char* tmp = new char[100000];
    for (int i = l; i <= r; i++) {
        tmp[i - l] = str[i];
    }

    tmp[r + 1] = 0;

    return tmp;
}

void createTree(char* strLeft, char* strMiddle, int n) {
    int i = 0, j = 0;
    char *lltmp, *lmtmp, *rltmp, *rmtmp;
    if (strLeft == NULL) {
        return;
    }

    tree[n] = strLeft[0];

    if (strlen(strLeft) == 1 || strlen(strMiddle) == 1) {
        return;
    }

    for (i = 0; i < strlen(strMiddle); i++) {
        if (strMiddle[i] == strLeft[0]) {
            break;
        }
    }
    j = (i + 1 > strlen(strLeft)) ? (strlen(strLeft) - 1) : (i + 1);

    lltmp = subString(strLeft, 1, j - 1);
    lmtmp = subString(strMiddle, 0, i - 1);
    rltmp = subString(strLeft, j, strlen(strLeft) - 1);
    rmtmp = subString(strMiddle, i + 1, strlen(strMiddle) - 1);

    createTree(lltmp, lmtmp, 2 * n);
    createTree(rltmp, rmtmp, 2 * n + 1);

    delete[] lltmp;
    delete[] lmtmp;
    delete[] rltmp;
    delete[] rmtmp;
}

int main() {
    int i, j = 1, k = 0;
    cin >> Left >> Middle;
    i = strlen(Left);
    createTree(Left, Middle, 1);
    for (; k < i;) {
        if (tree[j] < 'A' || tree[j] > 'Z') {
            cout << "NULL ";
            j++;
        } else {
            cout << tree[j] << " ";
            j++;
            k++;
        }
    }

    return 0;
}