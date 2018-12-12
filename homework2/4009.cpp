#include <cstring>
#include <iostream>

using namespace std;

template <class T>
class seqList {
   private:
    T *data;
    int Length;
    int maxSize;
    void doubleSpace();

   public:
    seqList(int initSize = 10);
    seqList(const seqList<T> &);
    ~seqList();
    int length() const;
    void add(const T &x);
    void traverse() const;
    void clear();
    seqList<T> operator+(seqList<T> &);
    seqList<T> &operator=(const seqList<T> &);
    T &operator[](int);
};

template <class T>
void seqList<T>::doubleSpace() {
    T *tmp = data;

    maxSize *= 2;

    data = new T[maxSize];
    for (int i = 0; i < Length; ++i) {
        data[i] = tmp[i];
    }

    delete[] tmp;
}

template <class T>
seqList<T>::seqList(int initSize) {
    data = new T[initSize];
    Length = 0;
    maxSize = initSize;
}

template <class T>
seqList<T>::~seqList() {
    delete[] data;
}

template <class T>
int seqList<T>::length() const {
    return Length;
}

template <class T>
void seqList<T>::add(const T &x) {
    if (Length == maxSize) {
        doubleSpace();
    }

    data[Length] = x;
    Length++;
}

template <class T>
void seqList<T>::traverse() const {
    for (int i = 0; i < Length - 1; i++) {
        cout << data[i] << ' ';
    }
    cout << data[Length - 1];
}

template <class T>
T &seqList<T>::operator[](int x) {
    return data[x];
}

template <class T>
void seqList<T>::clear() {
    Length = 0;
}

template <class T>
seqList<T>::seqList(const seqList<T> &right) {
    Length = right.Length;
    maxSize = right.maxSize;
    data = new T[maxSize];
    for (int i = 0; i < maxSize; i++) {
        data[i] = right.data[i];
    }
}

template <class T>
seqList<T> &seqList<T>::operator=(const seqList<T> &right) {
    if (&right != this) {
        delete[] data;

        Length = right.Length;
        maxSize = right.maxSize;
        data = new T[maxSize];
        for (int i = 0; i < Length; i++) {
            data[i] = right.data[i];
        }
    }

    return *this;
}

int main() {
    char ming[110], mi[110];
    int len;
    seqList<int> vec;

    cin >> ming >> mi;

    len = strlen(ming);

    for (int i = 1; (i * i) <= len; i++) {
        if (len % i == 0) {
            vec.add(i);
            if (len != i * i) {
                vec.add(len / i);
            }
        }
    }

    for (int i = 0; i < vec.length() - 1; i++) {
        for (int j = 0; j < vec.length() - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                int tmp;
                tmp = vec[j + 1];
                vec[j + 1] = vec[j];
                vec[j] = tmp;
            }
        }
    }

    for (int i = 0; i < vec.length(); i++) {
        int tmp = vec[i], k = 0;
        char testmi[110] = {0};

        for (int j = 0; j < tmp; j++) {
            for (int l = 0; l < len / tmp; l++) {
                testmi[k] = ming[l * tmp + j];
                k++;
            }
        }

        if (strcmp(testmi, mi) == 0) {
            cout << tmp;
            return 0;
        }
    }

    cout << "No Solution";

    return 0;
}