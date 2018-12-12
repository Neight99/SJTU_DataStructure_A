#include <cstring>
#include <iostream>

using namespace std;

const int maxN = 5e6 + 10;

int inputLen = 0, outputLen = 0;
char input[maxN] = {0}, output[2 * maxN] = {0};

template <class T>
class seqStack {
   private:
    T* data;
    int nowSize;
    int maxSize;
    // void doublespace();

   public:
    seqStack(int initSize = maxN);
    seqStack(const seqStack<T>&);
    ~seqStack();
    int size() const;
    void push(T);
    T top();
    T pop();
    bool isEmpty();
    T find(T) const;
    seqStack<T>& operator=(const seqStack<T>&);
    T& operator[](int);
};

template <class T>
seqStack<T>::seqStack(int initSize) {
    data = new T[initSize];
    nowSize = 0;
    maxSize = initSize;
}

template <class T>
seqStack<T>::seqStack(const seqStack<T>& right) {
    nowSize = right.nowSize;
    maxSize = right.maxSize;
    data = new T[maxSize];
    for (int i = 0; i < nowSize; i++) {
        data[i] = right.data[i];
    }
}

template <class T>
seqStack<T>::~seqStack() {
    delete[] data;
    data = NULL;
}

/*template <class T>
void seqStack<T>::doublespace() {
    maxSize *= 2;
    T* tmp;
    tmp = new T[maxSize];

    for (int i = 0; i < nowSize; i++) {
        tmp[i] = data[i];
    }

    delete[] data;
    data = tmp;

    tmp = NULL;
}*/

template <class T>
int seqStack<T>::size() const {
    return nowSize;
}

template <class T>
void seqStack<T>::push(T x) {
    /*if (nowSize == maxSize) {
        doublespace();
    }*/
    data[nowSize++] = x;
}

template <class T>
T seqStack<T>::top() {
    if (nowSize > 0) {
        return data[nowSize - 1];
    } else {
        return 0;
    }
}

template <class T>
T seqStack<T>::pop() {
    if (nowSize > 0) {
        return data[--nowSize];
    } else {
        return 0;
    }
}

template <class T>
bool seqStack<T>::isEmpty() {
    return (nowSize == 0);
}

template <class T>
T seqStack<T>::find(T x) const {
    for (int i = 0; i < nowSize; i++) {
        if (data[i] == x) {
            return x;
        }
    }
    return -1;
}

template <class T>
seqStack<T>& seqStack<T>::operator=(const seqStack<T>& right) {
    if (this != &right) {
        delete[] data;

        nowSize = right.nowSize;
        maxSize = right.maxSize;
        data = new T[maxSize];
        for (int i = 0; i < nowSize; i++) {
            data[i] = right.data[i];
        }
    }

    return *this;
}

template <class T>
T& seqStack<T>::operator[](int x) {
    return data[nowSize - x - 1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int ans, temp = 0, temp1, temp2, temp3;
    seqStack<char> mark;
    seqStack<int> num;
    bool flag = 0;
    char ch;

    ch = cin.get();
    while (ch != -1) {
        if (ch != ' ' && ch != '\n') {
            input[inputLen++] = ch;
        }
        ch = cin.get();
    }
    input[inputLen] = 0;

    for (int i = inputLen - 1; i >= 0; i--) {
        switch (input[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (!flag) {
                    output[outputLen++] = ' ';
                }
                flag = 1;
                output[outputLen++] = input[i];
                break;
            case ')':
                flag = 0;
                mark.push(input[i]);
                break;
            case '+':
            case '-':
                flag = 0;
                if (mark.isEmpty() || mark.top() == ')' || mark.top() == '+' ||
                    mark.top() == '-') {
                    mark.push(input[i]);
                } else if (!mark.isEmpty()) {
                    output[outputLen++] = ' ';
                    output[outputLen++] = mark.pop();
                    i++;
                }
                break;
            case '*':
            case '/':
                flag = 0;
                if (mark.isEmpty() || mark.top() == ')' || mark.top() == '+' ||
                    mark.top() == '-' || mark.top() == '*' ||
                    mark.top() == '/') {
                    mark.push(input[i]);
                } else if (!mark.isEmpty()) {
                    output[outputLen++] = ' ';
                    output[outputLen++] = mark.pop();
                    i++;
                }
                break;
            case '(':
                flag = 0;
                while (!mark.isEmpty() && mark.top() != ')') {
                    output[outputLen++] = ' ';
                    output[outputLen++] = mark.pop();
                }
                if (!mark.isEmpty() && mark.top() == ')') {
                    mark.pop();
                }
                break;
        }
    }
    while (!mark.isEmpty()) {
        output[outputLen++] = ' ';
        output[outputLen++] = mark.pop();
    }
    output[outputLen] = 0;

    flag = 0;
    for (int i = outputLen - 1; i >= 0; i--) {
        if (!flag && output[i] == ' ') {
            continue;
        } else {
            flag = 1;
            cout << output[i];
        }
    }
    cout << '\n';

    for (int i = 0; i < outputLen; i++) {
        switch (output[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                int j = i;
                temp = 0;
                while (output[j] != ' ' && j < outputLen) {
                    j++;
                }
                for (int k = j - 1; k >= i; k--) {
                    temp *= 10;
                    temp += output[k] - '0';
                }
                i = j;
                num.push(temp);
                break;
            }
            case ' ':
                break;
            case '+':
                if (!num.isEmpty()) temp1 = num.pop();
                if (!num.isEmpty()) temp2 = num.pop();
                temp1 += temp2;
                num.push(temp1);
                break;
            case '-':
                if (!num.isEmpty()) temp1 = num.pop();
                if (!num.isEmpty()) temp2 = num.pop();
                temp1 -= temp2;
                num.push(temp1);
                break;
            case '*':
                if (!num.isEmpty()) temp1 = num.pop();
                if (!num.isEmpty()) temp2 = num.pop();
                temp1 *= temp2;
                num.push(temp1);
                break;
            case '/':
                if (!num.isEmpty()) temp1 = num.pop();
                if (!num.isEmpty()) temp2 = num.pop();
                temp1 /= temp2;
                num.push(temp1);
                break;
        }
    }
    if (!num.isEmpty()) ans = num.pop();
    cout << ans;

    return 0;
}