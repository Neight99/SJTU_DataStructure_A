#include <cstring>
#include <iostream>

using namespace std;

int main() {
    char a[110], b[110], c[220] = {'\0'}, cha, chb;
    int aLen, bLen, Len, temp, carry = 0;

    cin >> a >> b;
    aLen = strlen(a);
    bLen = strlen(b);
    if (aLen > bLen) {
        Len = aLen;
    } else {
        Len = bLen;
    }

    for (int i = 0; i < Len + 1; i++) {
        if (i < aLen) {
            cha = a[aLen - 1 - i];
        } else {
            cha = 'a';
        }

        if (i < bLen) {
            chb = b[bLen - 1 - i];
        } else {
            chb = 'a';
        }

        temp = cha - 'a' + chb - 'a' + carry;
        carry = 0;

        if (temp >= 26) {
            carry += 1;
            temp -= 26;
        }

        c[Len - i] = temp + 'a';
    }
    c[Len + 1] = '\0';

    if (c[0] == 'a') {
        cout << c + 1;
    } else {
        cout << c;
    }

    return 0;
}