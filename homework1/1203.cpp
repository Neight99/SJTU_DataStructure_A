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
seqList<T> seqList<T>::operator+(seqList<T> &right) {
    seqList<T> tmp(this->length() + right.length());

    for (int i = 0; i < this->length(); i++) {
        tmp.add(data[i]);
    }

    for (int i = 0; i < right.length(); i++) {
        tmp.add(right[i]);
    }

    return tmp;
}

template <class T>
T &seqList<T>::operator[](int x) {
    return data[x];
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
    char type[50];
    int l1, l2;
    cin >> type >> l1 >> l2;

    if (strcmp(type, "int") == 0) {
        seqList<int> vec1, vec2, vec3;
        int tmp;

        for (int i = 0; i < l1; ++i) {
            cin >> tmp;
            vec1.add(tmp);
        }

        for (int i = 0; i < l2; ++i) {
            cin >> tmp;
            vec2.add(tmp);
        }

        vec3 = vec1 + vec2;
        vec3.traverse();
    }

    if (strcmp(type, "double") == 0) {
        seqList<double> vec1, vec2, vec3;
        double tmp;

        for (int i = 0; i < l1; ++i) {
            cin >> tmp;
            vec1.add(tmp);
        }

        for (int i = 0; i < l2; ++i) {
            cin >> tmp;
            vec2.add(tmp);
        }

        vec3 = vec1 + vec2;
        vec3.traverse();
    }

    if (strcmp(type, "char") == 0) {
        seqList<char> vec1, vec2, vec3;
        char tmp;

        for (int i = 0; i < l1; ++i) {
            cin >> tmp;
            vec1.add(tmp);
        }

        for (int i = 0; i < l2; ++i) {
            cin >> tmp;
            vec2.add(tmp);
        }

        vec3 = vec1 + vec2;
        vec3.traverse();
    }

    return 0;
}