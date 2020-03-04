#include <iomanip>
#include <iostream>

using namespace std;

class MyComplex {
   private:
    double x, y;

   public:
    MyComplex(int a = 0, int b = 0) : x(a), y(b) {}
    MyComplex operator+(const MyComplex &) const;
    MyComplex operator-(const MyComplex &) const;
    MyComplex operator*(const MyComplex &)const;
    MyComplex operator/(const MyComplex &) const;
    MyComplex &operator+=(const MyComplex &);
    MyComplex &operator-=(const MyComplex &);
    MyComplex &operator*=(const MyComplex &);
    MyComplex &operator/=(const MyComplex &);
    friend istream &operator>>(istream &, MyComplex &);
    friend ostream &operator<<(ostream &, const MyComplex &);
};

MyComplex MyComplex::operator+(const MyComplex &right) const {
    MyComplex tmp;
    tmp.x = x + right.x;
    tmp.y = y + right.y;
    return tmp;
}

MyComplex MyComplex::operator-(const MyComplex &right) const {
    MyComplex tmp;
    tmp.x = x - right.x;
    tmp.y = y - right.y;
    return tmp;
}

MyComplex MyComplex::operator*(const MyComplex &right) const {
    MyComplex tmp;
    tmp.x = x * right.x - y * right.y;
    tmp.y = x * right.y + y * right.x;
    return tmp;
}

MyComplex MyComplex::operator/(const MyComplex &right) const {
    MyComplex tmp;
    tmp.x =
        (x * right.x + y * right.y) / (right.x * right.x + right.y * right.y);
    tmp.y =
        (y * right.x - x * right.y) / (right.x * right.x + right.y * right.y);
    return tmp;
}

MyComplex &MyComplex::operator+=(const MyComplex &right) {
    (*this) = (*this) + right;
    return *this;
}

MyComplex &MyComplex::operator-=(const MyComplex &right) {
    (*this) = (*this) - right;
    return *this;
}

MyComplex &MyComplex::operator*=(const MyComplex &right) {
    (*this) = (*this) * right;
    return *this;
}

MyComplex &MyComplex::operator/=(const MyComplex &right) {
    (*this) = (*this) / right;
    return *this;
}

istream &operator>>(istream &is, MyComplex &right) {
    is >> right.x >> right.y;
    return is;
}

ostream &operator<<(ostream &os, const MyComplex &right) {
    os << setiosflags(ios::fixed) << setprecision(2) << right.x << ' '
       << right.y;
    return os;
}

int main() {
    MyComplex z1;
    MyComplex z2;

    cin >> z1 >> z2;

    cout << z1 + z2 << endl;
    cout << z1 - z2 << endl;
    cout << z1 * z2 << endl;
    cout << z1 / z2 << endl;
    cout << (z1 += z2) << endl;
    cout << (z1 -= z2) << endl;
    cout << (z1 *= z2) << endl;
    cout << (z1 /= z2) << endl;

    return 0;
}