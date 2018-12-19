class bigint {
   private:
    static const int base = 1e8, pow = 8;
    long long data[1000];
    int length;

   public:
    bigint();
    bigint(const char *);
    bigint(const bigint &);
    bigint &operator+=(const long long &);
    bigint operator+(const bigint &) const;
    bigint &operator+=(const bigint &);
    bigint operator-(const bigint &) const;
    bigint &operator-=(const bigint &);
    bigint &operator*=(const bigint &);
    bigint operator*(const bigint &)const;
    bigint &operator*=(const long long &);
    bigint operator*(const long long &)const;
    bigint &operator/=(const long long &);
    bigint operator/(const long long &) const;
    bigint &operator/=(const bigint &);
    bigint operator/(const bigint &) const;
    bigint operator=(const bigint &);
    bool operator<(const bigint &) const;
    bool operator<=(const bigint &) const;
    bool operator==(const bigint &) const;
    bool operator>(const bigint &) const;
    bool operator>=(const bigint &) const;
    void output() const;
};

bigint::bigint() : length(0) { memset(data, 0, sizeof(data)); }

bigint::bigint(const char *str) {
    memset(data, 0, sizeof(data));
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        data[(len - i - 1) / 8] = data[(len - i - 1) / 8] * 10 + str[i] - '0';
    }
    length = (len - 1) / 8 + 1;
}

bigint::bigint(const bigint &right) {
    if (this != &right) {
        memset(data, 0, sizeof(data));
        length = right.length;
        for (int i = 0; i < length; i++) {
            data[i] = right.data[i];
        }
    }
}

bigint bigint::operator=(const bigint &right) {
    if (this != &right) {
        memset(data, 0, sizeof(data));
        length = right.length;
        for (int i = 0; i < length; i++) {
            data[i] = right.data[i];
        }
    }

    return *this;
}

bigint &bigint::operator+=(const long long &right) {
    data[0] += right;
    for (int i = 0; i < length; i++) {
        data[i + 1] += data[i] / base;
        data[i] %= base;
    }
    while (data[length] > 0) {
        length++;
    }

    return *this;
}

bigint &bigint::operator+=(const bigint &right) {
    length = (length > right.length) ? length : right.length;
    for (int i = 0; i < length; i++) {
        data[i] += right.data[i];
        data[i + 1] += data[i] / base;
        data[i] %= base;
    }

    while (data[length] > 0) {
        length++;
    }
    return *this;
}

bigint bigint::operator+(const bigint &right) const {
    bigint temp = *this;
    temp += right;

    return temp;
}

bigint &bigint::operator-=(const bigint &right) {
    for (int i = 0; i < length; i++) {
        data[i] -= right.data[i];
        while (data[i] < 0) {
            data[i] += base;
            data[i + 1]--;
        }
    }

    while (data[length - 1] <= 0 && length > 0) {
        --length;
    }

    return *this;
}

bigint bigint::operator-(const bigint &right) const {
    bigint temp = *this;
    temp -= right;
    return temp;
}

bigint bigint::operator*(const bigint &right) const {
    bigint temp;
    temp.length = length + right.length - 1;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < right.length; j++) {
            temp.data[i + j] += data[i] * right.data[j];
        }
    }
    for (int i = 0; i < temp.length; i++) {
        temp.data[i + 1] += temp.data[i] / base;
        temp.data[i] %= base;
    }

    while (temp.data[temp.length] > 0) {
        temp.length++;
        temp.data[temp.length] += temp.data[temp.length - 1] / base;
        temp.data[temp.length - 1] %= base;
    }

    return temp;
}

bigint &bigint::operator*=(const bigint &right) {
    bigint temp = *this;
    temp = temp * right;
    *this = temp;
    return *this;
}

bigint &bigint::operator*=(const long long &right) {
    for (int i = 0; i < length; i++) {
        data[i] *= right;
    }
    for (int i = 1; i < length; i++) {
        data[i + 1] += data[i] / base;
        data[i] %= base;
    }
    return *this;
}

bigint bigint::operator*(const long long &right) const {
    bigint temp = *this;
    temp *= right;
    return temp;
}

bigint &bigint::operator/=(const long long &right) {
    bigint base1("100000000");
    for (int i = length - 1; i > 0; i--) {
        data[i - 1] += (data[i] % right * base);
        data[i] /= right;
    }
    data[0] /= right;

    while (length > 0 && data[length - 1] <= 0) {
        length--;
    }
    return *this;
}

bigint bigint::operator/(const long long &right) const {
    bigint temp = *this;
    temp /= right;

    return temp;
}

bigint &bigint::operator/=(const bigint &right) {
    bigint b1, b2, b3 = *this, one("1");
    b1.length = 1;

    while (b1 < b3) {
        b2 = (b1 + b3 + one) / 2;
        if (*this < (right * b2)) {
            b3 = b2 - one;
        } else {
            b1 = b2;
        }
    }
    *this = b1;

    return *this;
}

bigint bigint::operator/(const bigint &right) const {
    bigint temp = *this;
    temp /= right;
    return temp;
}

bool bigint::operator<(const bigint &right) const {
    if (length != right.length) {
        return length < right.length;
    }

    for (int i = length - 1; i >= 0; i--) {
        if (data[i] != right.data[i]) {
            return data[i] < right.data[i];
        }
    }
    return 0;
}

bool bigint::operator<=(const bigint &right) const {
    return (*this < right) || (*this == right);
}

bool bigint::operator==(const bigint &right) const {
    if (length != right.length) {
        return 0;
    } else {
        for (int i = 0; i < length; i++) {
            if (data[i] != right.data[i]) {
                return 0;
            }
        }
        return 1;
    }
}

bool bigint::operator>(const bigint &right) const {
    return (!(*this < right)) && (!(*this == right));
}

bool bigint::operator>=(const bigint &right) const { return !(*this < right); }

void bigint::output() const {
    printf("%lld", data[length - 1]);
    for (int i = length - 2; i >= 0; i--) {
        printf("%08lld", data[i]);
    }
}