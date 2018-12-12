#include <cstring>
#include <iostream>

using namespace std;

class String {
   private:
    struct Node {
        char data;
        Node *prev, *next;

        Node(const int &x = 0, Node *p = NULL, Node *q = NULL)
            : data(x), next(q), prev(p) {}

        ~Node() {}
    };

    Node *head, *tail;
    int Length;

    Node *move(int) const;

   public:
    String();

    String(const char *);

    String(const String &);

    ~String() {
        clear();
        delete head;
        delete tail;
        head = NULL;
        tail = NULL;
    }

    void clear();

    int length() const { return Length; }

    void insert(int, const char &);

    char visit(int) const;

    char *travel() const;

    void remove(int);

    void plus(String, String);

    String operator=(const String &);
};

String::Node *String::move(int i) const {
    Node *p = head;
    --i;
    while (i >= 0) {
        p = p->next;
        --i;
    }
    return p;
}

String::String() {
    head = new Node();
    head->next = tail = new Node();
    tail->prev = head;
    head->prev = NULL;
    tail->next = NULL;
    Length = 0;
}

String::String(const char *str) : String() {
    int len = strlen(str);

    for (int i = len - 1; i >= 0; i--) {
        this->insert(1, str[i] - '0');
    }
}

String::String(const String &right) : String() {
    if (this->head != NULL) {
        // clear();
    }
    Node *q = right.tail->prev;
    while (q->prev != NULL) {
        this->insert(1, q->data);
        q = q->prev;
    }
}

String String::operator=(const String &right) {
    if (this != &right) {
        // clear();
        Node *q = right.head->next;
        while (q->prev != NULL) {
            this->insert(1, q->data);
            q = q->prev;
        }
    }
    return *this;
}

void String::remove(int i) {
    Node *p;
    p = move(i);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --Length;
}

char *String::travel() const {
    char *str;
    int i = 0;
    str = new char[Length];
    Node *p = head->next;
    while (p->next != NULL) {
        str[i] = (p->data) + '0';
        i++;
        p = p->next;
    }
    str[i] = '\0';

    return str;
}

char String::visit(int x) const { return move(x)->data; }

void String::clear() {
    Node *p = head->next, *q;
    head->next = tail;
    tail->prev = head;
    while (p != tail) {
        q = p->next;
        delete p;
        p = q;
    }
    p = NULL;
    q = NULL;

    Length = 0;
}

void String::insert(int i, const char &x) {
    Node *pos, *tmp;
    pos = move(i);
    tmp = new Node(x, pos->prev, pos);
    pos->prev->next = tmp;
    pos->prev = tmp;
    Length++;
    pos = NULL;
    tmp = NULL;
}

void String::plus(String b1, String b2) {
    this->clear();
    int carry = 0, temp = 0;
    Node *p = b1.tail->prev, *q = b2.tail->prev;

    while (p->prev != NULL && q->prev != NULL) {
        temp = p->data + q->data + carry;
        carry = temp / 10;
        temp %= 10;
        this->insert(1, temp);
        temp = 0;
        p = p->prev;
        q = q->prev;
    }

    if (p->prev == NULL) {
        while (q->prev != NULL) {
            temp = q->data + carry;
            carry = temp / 10;
            temp %= 10;
            this->insert(1, temp);
            temp = 0;
            q = q->prev;
        }
    }

    if (q->prev == NULL) {
        while (p->prev != NULL) {
            temp = p->data + carry;
            carry = temp / 10;
            temp %= 10;
            this->insert(1, temp);
            temp = 0;
            p = p->prev;
        }
    }

    if (carry != 0) {
        this->insert(1, carry);
        carry = 0;
    }
}

void input(char *);

int main() {
    char str1[100001] = {'\0'}, str2[100001] = {'\0'}, *str3;
    input(str1);
    input(str2);
    String num1(str1), num2(str2), num3;
    num3.plus(num1, num2);
    str3 = num3.travel();
    cout << str3;
}

void input(char *num) {
    char ch;
    int i = 0;
    cin.get(ch);
    while (ch != '\n' && i != 100000) {
        num[i] = ch;
        i++;
        cin.get(ch);
    }
}