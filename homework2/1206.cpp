#include <cstring>
#include <iostream>

using namespace std;

template <class T>
class seqStack {
   private:
    T* data;
    int nowSize;
    int maxSize;
    void doublespace();

   public:
    seqStack(int initSize = 10);
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
void seqStack<T>::doublespace() {
    T* tmp;
    maxSize *= 2;
    tmp = new T[maxSize];
    for (int i = 0; i < nowSize; i++) {
        tmp[i] = data[i];
    }
    delete[] data;
    data = tmp;
    tmp = NULL;
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

template <class T>
int seqStack<T>::size() const {
    return nowSize;
}

template <class T>
void seqStack<T>::push(T x) {
    if (nowSize == maxSize) {
        doublespace();
        // return;
    }
    data[nowSize++] = x;
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
T seqStack<T>::top() {
    return data[nowSize - 1];
}

template <class T>
T seqStack<T>::pop() {
    if (nowSize != 0) {
        return data[--nowSize];
    }
    return -1;
}

template <class T>
bool seqStack<T>::isEmpty() {
    return (nowSize == 0);
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

class check {
   private:
    char* data;
    int pair;
    seqStack<int> vec1;
    seqStack<int> vec2;

   public:
    check(char[]);
    ~check();
    int checkWord(char*);
    bool checkIssue(int);
    bool checkAll();
};

check::check(char words[]) : pair(0) { data = words; }

check::~check() { data = NULL; }

int check::checkWord(char* ch) {
    if (strcmp(ch, "begin") == 0) {
        return 1;
    } else if (strcmp(ch, "end") == 0) {
        return 2;
    } else if (strcmp(ch, "if") == 0) {
        return 3;
    } else if (strcmp(ch, "then") == 0) {
        return 4;
    } else if (strcmp(ch, "else") == 0) {
        return 5;
    } else {
        return 0;
    }
}

bool check::checkIssue(int i) {
    if (i == 1) {
        if (vec1.top() == 3) {
            return 0;
        } else {
            vec1.push(1);
            vec2.push(0);
        }
    } else if (i == 2) {
        if (vec1.isEmpty() || vec1.top() != 1) {
            return 0;
        } else {
            vec1.pop();
            vec2.pop();
        }
    } else if (i == 3) {
        if (vec1.top() == 3) {
            return 0;
        } else {
            vec1.push(3);
        }
    } else if (i == 4) {
        if (vec1.isEmpty() || vec1.top() != 3) {
            return 0;
        } else {
            vec1.pop();
            if (vec2.isEmpty()) {
                ++pair;
            } else {
                return 0;
            }
        }
    } else if (i == 5) {
        if (vec2.isEmpty()) {
            if (pair) {
                --pair;
            } else {
                return 0;
            }
        } else {
            if (vec2.top()) {
                int temp = vec2.pop();
                vec2.push(temp - 1);
            } else {
                return 0;
            }
        }
    }
    return 1;
}

bool check::checkAll() {
    if (data == NULL) {
        return 0;
    } else {
        char* p = data;
        char tmp[100] = {'\0'};
        int type, last = 0;
        while (1) {
            int pos = 0;
            while (*p == ' ') {
                p++;
            }
            while (*p && *p != ' ') {
                tmp[pos++] = *p;
                p++;
            }
            tmp[pos++] = 0;
            type = checkWord(tmp);
            checkIssue(type);
            if (*p == 0) {
                break;
            }
        }
        while (vec1.isEmpty() == 0) {
            int tmp = vec1.pop();
            if (tmp == 1) {
                return 0;
            } else if (tmp == 3 && last != 4) {
                return 0;
            }
            last = type;
        }
        return 1;
    }
}

int main() {
    int pair, pos = 0;
    bool flag = 1;
    char words[50000], ch;

    ch = getchar();
    while (ch != EOF) {
        if (ch == '\n') {
            ch = ' ';
        }
        words[pos++] = ch;
        ch = getchar();
    }
    words[pos] = 0;

    check che(words);
    if (che.checkAll()) {
        cout << "Match!" << endl;
    } else {
        cout << "Error!" << endl;
    }

    return 0;
}