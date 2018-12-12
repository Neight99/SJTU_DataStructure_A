#include <iostream>

using namespace std;

template <class T>
class seqStack {
   private:
    T* data;
    int nowSize;
    int maxSize;
    // void doublespace();
   public:
    seqStack(int initSize = 10);
    seqStack(const seqStack<T>&);
    ~seqStack();
    int size() const;
    void push(T);
    T top();
    T pop();
    bool isEmpty();
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

template <class T>
int seqStack<T>::size() const {
    return nowSize;
}

template <class T>
void seqStack<T>::push(T x) {
    if (nowSize == maxSize) {
        // doublespace();
        return;
    }
    data[nowSize++] = x;
}

template <class T>
T seqStack<T>::top() {
    if (nowSize != 0) {
        return data[nowSize - 1];
    } else {
        return -1;
    }
}

template <class T>
T seqStack<T>::pop() {
    if (nowSize != 0) {
        return data[--nowSize];
    } else {
        return -1;
    }
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

int main() {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int N, M, h = 0, *out, temp;
        bool key = 1;
        cin >> N >> M;

        seqStack<int> Station(M + 1);
        out = new int[N];

        for (int i = 0; i < N; i++) {
            cin >> out[i];
        }

        /*for(int i=0;i<N;i++){
            bool go=0;
            while(i==out[h]||Station.top()==out[h]){
                if(i==out[h] && go==0){
                    h++;
                    go=1;
                }
                if(Station.top()==out[h]){
                    temp=Station.pop();
                    h++;
                }
            }
            if(Station.size()==M){
                cout<<"NO"<<'\n';
                key=0;
                break;
            } else if (Station.size()<M && go==0){
                Station.push(i);
            }
        }*/
        for (int i = 0; i < N; i++) {
            if (Station.size() == M + 1) {
                key = 0;
                break;
            }
            Station.push(i);
            while (Station.top() == out[h]) {
                Station.pop();
                h++;
            }
        }

        if (Station.size() != 0) {
            key = 0;
        }

        if (key == 1) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }

        delete[] out;
    }

    return 0;
}