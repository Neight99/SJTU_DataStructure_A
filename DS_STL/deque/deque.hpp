#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include <cstddef>
#include <iostream>
#include "exceptions.hpp"

namespace sjtu {

const int Size = 1e3;

template <class T>
class deque {
   public:
    class Node;

    class const_iterator;
    class iterator {
        friend class sjtu::deque<T>;
        friend class sjtu::deque<T>::const_iterator;
        friend class sjtu::deque<T>::Node;

       private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        const sjtu::deque<T> *que;
        Node *node;
        int pos;

       public:
        /**
         * return a new iterator which pointer n-next elements
         *   even if there are not enough elements, the behaviour is
         * **undefined**. as well as operator-
         */
        iterator(const deque *q = NULL, Node *n = NULL, int p = 0)
            : que(q), node(n), pos(p) {}

        iterator(const iterator &rhs)
            : que(rhs.que), node(rhs.node), pos(rhs.pos) {}
        iterator operator+(const int &n) const {
            // TODO
            iterator ans(*this);
            if (n < 0) {
                int dis = -n;
                while (ans.node->prev != NULL && ans.pos < dis) {
                    dis -= ans.pos + 1;
                    ans.node = ans.node->prev;
                    ans.pos = ans.node->inside - 1;
                }
                if (ans.pos < dis && ans.node->prev == NULL) {
                    throw index_out_of_bound();
                }
                ans.pos -= dis;
            } else if (n > 0) {
                int dis = n;
                while (ans.node->next != ans.que->tail &&
                       (ans.pos >= ans.node->inside - dis)) {
                    dis -= ans.node->inside - ans.pos;
                    ans.pos = 0;
                    ans.node = ans.node->next;
                }
                if (ans.node->next == NULL) {
                    throw index_out_of_bound();
                }
                ans.pos += dis;
            }
            return ans;
        }
        iterator operator-(const int &n) const {
            // TODO
            return operator+(-n);
        }
        // return th distance between two iterator,
        // if these two iterators points to different vectors, throw
        // invaild_iterator.
        int operator-(const iterator &rhs) const {
            // TODO
            if (que != rhs.que) {
                throw invalid_iterator();
            } else if (node == rhs.node) {
                return pos - rhs.pos;
            } else {
                int ans = rhs.node->inside - rhs.pos;
                Node *p = rhs.node->next;
                while (p != NULL && p != node) {
                    ans += p->inside;
                    p = p->next;
                }
                if (p != NULL) {
                    return ans + pos;
                } else {
                    p = node->next;
                    ans = node->inside - pos;
                    while (p != NULL && p != rhs.node) {
                        ans += p->inside;
                        p = p->next;
                    }
                    if (p != NULL) {
                        return -(ans + rhs.pos);
                    } else {
                        throw runtime_error();
                    }
                }
            }
        }
        iterator operator+=(const int &n) {
            // TODO
            *this = (*this) + n;
            return *this;
        }
        iterator operator-=(const int &n) {
            // TODO
            *this = (*this) - n;
            return *this;
        }
        /**
         * TODO iter++
         */
        iterator operator++(int) {
            iterator ans(*this);
            if (pos == node->inside - 1) {
                pos = 0;
                if (node->next == NULL) {
                    throw index_out_of_bound();
                } else {
                    node = node->next;
                }
            } else {
                pos++;
            }
            return ans;
        }
        /**
         * TODO ++iter
         */
        iterator &operator++() {
            (*this)++;
            return *this;
        }
        /**
         * TODO iter--
         */
        iterator operator--(int) {
            iterator ans(*this);
            if (pos == 0) {
                if (node->prev == NULL) {
                    throw index_out_of_bound();
                } else {
                    node = node->prev;
                    pos = node->inside - 1;
                }
            } else {
                pos--;
            }
            return ans;
        }
        /**
         * TODO --iter
         */
        iterator &operator--() {
            (*this)--;
            return *this;
        }
        /**
         * TODO *it
         */
        T &operator*() const { return node->at(pos); }
        /**
         * TODO it->field
         */
        T *operator->() const noexcept { return node->data[pos]; }
        /**
         * a operator to check whether two iterators are same (pointing to
         * the same memory).
         */
        bool operator==(const iterator &rhs) const {
            return (node == rhs.node && pos == rhs.pos) ||
                   (node->next == NULL && rhs.node->next == node &&
                    rhs.pos == rhs.node->inside) ||
                   (rhs.node->next == NULL && node->next == rhs.node &&
                    pos == node->inside);
        }
        bool operator==(const const_iterator &rhs) const {
            return (node == rhs.node && pos == rhs.pos) ||
                   (node->next == NULL && rhs.node->next == node &&
                    rhs.pos == rhs.node->inside) ||
                   (rhs.node->next == NULL && node->next == rhs.node &&
                    pos == node->inside);
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const { return !(*this == rhs); }
        bool operator!=(const const_iterator &rhs) const {
            return !(*this == rhs);
        }
    };
    class const_iterator {
        // it should has similar member method as iterator.
        //  and it should be able to construct from an iterator.
        friend class sjtu::deque<T>;
        friend class sjtu::deque<T>::iterator;
        friend class sjtu::deque<T>::Node;

       private:
        // data members.
        const sjtu::deque<T> *que;
        Node *node;
        int pos;

       public:
        const_iterator(const deque *q = NULL, Node *n = NULL, int p = 0)
            : que(q), node(n), pos(p) {}

        const_iterator(const iterator &rhs)
            : que(rhs.que), node(rhs.node), pos(rhs.pos) {}

        const_iterator(const const_iterator &rhs)
            : que(rhs.que), node(rhs.node), pos(rhs.pos) {}

        // And other methods in iterator.
        const_iterator operator+(const int &n) const {
            // TODO
            const_iterator ans(*this);
            if (n < 0) {
                int dis = -n;
                while (ans.node->prev != NULL && ans.pos < dis) {
                    dis -= ans.pos + 1;
                    ans.node = ans.node->prev;
                    ans.pos = ans.node->inside - 1;
                }
                if (ans.pos < dis && ans.node->prev == NULL) {
                    throw index_out_of_bound();
                }
                ans.pos -= dis;
            } else if (n > 0) {
                int dis = n;
                while (ans.node->next != ans.que->tail &&
                       (ans.pos >= ans.node->inside - dis)) {
                    dis -= ans.node->inside - ans.pos;
                    ans.pos = 0;
                    ans.node = ans.node->next;
                }
                if (ans.node->next == NULL) {
                    throw index_out_of_bound();
                }
                ans.pos += dis;
            }
            return ans;
        }
        const_iterator operator-(const int &n) const {
            // TODO
            return operator+(-n);
        }
        // And other methods in iterator.
        int operator-(const const_iterator &rhs) const {
            // TODO
            if (que != rhs.que) {
                throw invalid_iterator();
            } else if (node == rhs.node) {
                return pos - rhs.pos;
            } else {
                Node *p = node->next;
                int ans = node->inside - pos;
                while (p != NULL && p != rhs.node) {
                    ans += p->inside;
                    p = p->next;
                }
                if (p != NULL) {
                    return -(ans + rhs.pos);
                } else {
                    ans = rhs.node->inside - rhs.pos;
                    p = rhs.node->next;
                    while (p != NULL && p != node) {
                        ans += p->inside;
                        p = p->next;
                    }
                    if (p != NULL) {
                        return ans + pos;
                    } else {
                        throw runtime_error();
                    }
                }
            }
        }
        const_iterator operator+=(const int &n) {
            // TODO
            *this = (*this) + n;
            return *this;
        }
        const_iterator operator-=(const int &n) {
            // TODO
            *this = (*this) - n;
            return *this;
        }
        /**
         * TODO iter++
         */
        const_iterator operator++(int) {
            const_iterator ans(*this);
            if (pos == node->inside - 1) {
                pos = 0;
                if (node->next == NULL) {
                    throw index_out_of_bound();
                } else {
                    node = node->next;
                }
            } else {
                pos++;
            }
            return ans;
        }
        /**
         * TODO ++iter
         */
        const_iterator &operator++() {
            (*this)++;
            return *this;
        }
        /**
         * TODO iter--
         */
        const_iterator operator--(int) {
            const_iterator ans(*this);
            if (pos == 0) {
                if (node->prev == NULL) {
                    throw index_out_of_bound();
                } else {
                    node = node->prev;
                    pos = node->inside - 1;
                }
            } else {
                pos--;
            }
            return ans;
        }
        /**
         * TODO --iter
         */
        const_iterator &operator--() {
            (*this)--;
            return *this;
        }
        /**
         * TODO *it
         */
        T operator*() const { return node->at(pos); }
        /**
         * TODO it->field
         */
        T *operator->() const noexcept { return node->data[pos]; }
        /**
         * a operator to check whether two iterators are same (pointing to
         * the same memory).
         */
        bool operator==(const iterator &rhs) const {
            return (node == rhs.node && pos == rhs.pos) ||
                   (node->next == NULL && rhs.node->next == node &&
                    rhs.pos == rhs.node->inside) ||
                   (rhs.node->next == NULL && node->next == rhs.node &&
                    pos == node->inside);
        }
        bool operator==(const const_iterator &rhs) const {
            return (node == rhs.node && pos == rhs.pos) ||
                   (node->next == NULL && rhs.node->next == node &&
                    rhs.pos == rhs.node->inside) ||
                   (rhs.node->next == NULL && node->next == rhs.node &&
                    pos == node->inside);
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const { return !(*this == rhs); }
        bool operator!=(const const_iterator &rhs) const {
            return !(*this == rhs);
        }
    };

    class Node {
        friend class sjtu::deque<T>;
        friend class sjtu::deque<T>::iterator;
        friend class sjtu::deque<T>::const_iterator;

       public:
        Node(int i = Size)
            : chunkSize(i), inside(0), next(NULL), prev(NULL), data(NULL) {
            data = new T *[chunkSize];
        }

        Node(const Node &rhs)
            : chunkSize(rhs.chunkSize),
              inside(rhs.inside),
              next(NULL),
              prev(NULL),
              data(NULL) {
            data = new T *[chunkSize];
            for (int i = 0; i < rhs.inside; i++) {
                data[i] = new T(*rhs.data[i]);
            }
        }

        ~Node() { clear(); }

        Node &operator=(const Node &rhs) {
            if (&rhs != this) {
                clear();
                chunkSize = rhs.chunkSize;
                inside = rhs.inside;
                data = new T *[chunkSize];

                for (int i = 0; i < rhs.inside; i++) {
                    data[i] = new T(*rhs.data[i]);
                }
            }
            return *this;
        }

        void clear() {
            for (int i = 0; i < inside; i++) {
                delete data[i];
            }
            delete[] data;
            inside = 0;
        }

        T &at(int index) {
            if (index < 0 || index >= inside) {
                throw index_out_of_bound();
            }
            return *(data[index]);
        }

        T &operator[](int index) {
            if (index < 0 || index >= inside) {
                throw index_out_of_bound();
            }
            return *(data[index]);
        }

        void insert(int index, const T &value) {
            for (int i = inside; i > index; i--) {
                data[i] = data[i - 1];
            }
            data[index] = new T(value);
            inside++;
        }

        void erase(int index) {
            delete data[index];

            for (int i = index; i < inside - 1; i++) {
                data[i] = data[i + 1];
            }
            inside--;
        }

       private:
        int inside;
        int chunkSize;
        T **data;
        Node *next;
        Node *prev;
    };
    /**
     * TODO Constructors
     */
    deque() : chunkSize(Size), inside(0), head(NULL), tail(NULL) {
        head = new Node(chunkSize);
        tail = new Node(1);
        head->next = tail;
        tail->prev = head;
    }
    deque(const deque &other)
        : chunkSize(other.chunkSize),
          inside(other.inside),
          head(NULL),
          tail(NULL) {
        head = new Node(*other.head);
        tail = new Node(1);
        Node *p = head, *q = other.head->next;

        for (; q != other.tail; q = q->next) {
            p->next = new Node(*q);
            p->next->prev = p;
            p = p->next;
        }

        p->next = tail;
        tail->prev = p;
    }
    /**
     * TODO Deconstructor
     */
    ~deque() {
        clear();
        delete head;
        delete tail;
    }
    /**
     * TODO assignment operator
     */
    deque &operator=(const deque &other) {
        if (&other != this) {
            clear();
            inside = other.inside;
            delete head;
            head = new Node(*other.head);
            Node *p = head, *q = other.head->next;

            for (; q != other.tail; q = q->next) {
                p->next = new Node(*q);
                p->next->prev = p;
                p = p->next;
            }

            p->next = tail;
            tail->prev = p;
        }

        return *this;
    }
    /**
     * access specified element with bounds checking
     * throw index_out_of_bound if out of bound.
     */
    T &at(const size_t &pos) {
        Node *p = head;
        int n = pos;

        while (p != tail && n >= p->inside) {
            n -= p->inside;
            p = p->next;
        }

        if (p == tail) {
            throw index_out_of_bound();
        }

        return p->at(n);
    }
    const T &at(const size_t &pos) const {
        Node *p = head;
        int n = pos;

        while (p != tail && n >= p->inside) {
            n -= p->inside;
            p = p->next;
        }

        if (p == tail) {
            throw index_out_of_bound();
        }

        return p->at(n);
    }
    T &operator[](const size_t &pos) { return at(pos); }
    const T &operator[](const size_t &pos) const { return at(pos); }
    /**
     * access the first element
     * throw container_is_empty when the container is empty.
     */
    const T &front() const {
        if (inside == 0) {
            throw container_is_empty();
        } else {
            return head->at(0);
        }
    }
    /**
     * access the last element
     * throw container_is_empty when the container is empty.
     */
    const T &back() const {
        if (inside == 0) {
            throw container_is_empty();
        } else {
            return tail->prev->at(tail->prev->inside - 1);
        }
    }
    /**
     * returns an iterator to the beginning.
     */
    iterator begin() {
        if (inside == 0) {
            return iterator(this, tail, 0);
        } else {
            return iterator(this, head, 0);
        }
    }
    const_iterator cbegin() const {
        if (inside == 0) {
            return const_iterator(this, tail, 0);
        } else {
            return const_iterator(this, head, 0);
        }
    }
    /**
     * returns an iterator to the end.
     */
    iterator end() { return iterator(this, tail, 0); }
    const_iterator cend() const { return const_iterator(this, tail, 0); }
    /**
     * checks whether the container is empty.
     */
    bool empty() const { return inside == 0; }
    /**
     * returns the number of elements
     */
    size_t size() const { return inside; }
    /**
     * clears the contents
     */
    void clear() {
        Node *p = head->next, *q;
        delete head;
        head = new Node(Size);
        head->next = tail;
        tail->prev = head;
        while (p->next != NULL) {
            q = p->next;
            delete p;
            p = q;
        }
        inside = 0;
    }
    /**
     * inserts elements at the specified locat on in the container.
     * inserts value before pos
     * returns an iterator pointing to the inserted value
     *     throw if the iterator is invalid or it point to a wrong place.
     */
    iterator insert(iterator pos, const T &value) {
        if (this != pos.que) {
            throw invalid_iterator();
        } else if (pos.pos == 0 && pos.node->prev != NULL) {
            pos = iterator(this, pos.node->prev, pos.node->prev->inside);
        }
        inside++;
        adjust(pos.node);

        while (pos.node->next != NULL && pos.pos > pos.node->inside) {
            pos.pos -= pos.node->inside;
            pos.node = pos.node->next;
        }

        if (pos.node->next == NULL) {
            throw index_out_of_bound();
        }

        pos.node->insert(pos.pos, value);
        return pos;
    }
    /**
     * removes specified element at pos.
     * removes the element at pos.
     * returns an iterator pointing to the following element, if pos
     * pointing to the last element, end() will be returned. throw if the
     * container is empty, the iterator is invalid or it points to a wrong
     * place.
     */
    iterator erase(iterator pos) {
        if (this != pos.que) {
            throw invalid_iterator();
        } else if (pos.node == tail) {
            throw invalid_iterator();
        }
        inside--;
        while (pos.pos < 0) {
            pos.node = pos.node->prev;
            pos.pos += pos.node->inside;
        }
        if (pos.pos == pos.node->inside) {
            pos.pos = 0;
            pos.node = pos.node->next;
        }

        adjust(pos.node);

        while (pos.node->next != NULL && pos.pos >= pos.node->inside) {
            pos.pos -= pos.node->inside;
            pos.node = pos.node->next;
        }
        if (pos.node->next == NULL) {
            throw index_out_of_bound();
        } else {
            pos.node->erase(pos.pos);
            if (pos.pos == pos.node->inside) {
                pos.pos = 0;
                pos.node = pos.node->next;
            }
            return pos;
        }
    }
    /**
     * adds an element to the end
     */
    void push_back(const T &value) {
        insert(iterator(this, tail->prev, tail->prev->inside), value);
    }
    /**
     * removes the last element
     *     throw when the container is empty.
     */
    void pop_back() {
        if (inside == 0) {
            throw container_is_empty();
        } else {
            erase(iterator(this, tail->prev, tail->prev->inside - 1));
        }
    }
    /**
     * inserts an element to the beginning.
     */
    void push_front(const T &value) { insert(begin(), value); }
    /**
     * removes the first element.
     *     throw when the container is empty.
     */
    void pop_front() {
        if (inside == 0) {
            throw container_is_empty();
        } else {
            erase(begin());
        }
    }

   private:
    int chunkSize;
    Node *head;
    Node *tail;
    int inside;

    void adjust(Node *&node);
    void merge(Node *&node);
    void binary(Node *&node);
};

template <class T>
void sjtu::deque<T>::adjust(Node *&node) {
    if (node == tail) {
        return;
    }
    if (node->inside < chunkSize / 2) {
        binary(node);
    }
    if (node->inside >= chunkSize) {
        merge(node);
    }
}

template <class T>
void sjtu::deque<T>::merge(Node *&node) {
    Node *p = new Node(node->chunkSize);
    p->prev = node;
    p->next = node->next;
    node->next->prev = p;
    node->next = p;

    int temp = node->inside / 2;
    for (int i = temp; i < node->inside; i++) {
        p->data[i - temp] = node->data[i];
    }
    p->inside = node->inside - temp;
    node->inside = temp;
}

template <class T>
void sjtu::deque<T>::binary(Node *&node) {
    while (node->next->next != NULL &&
           node->inside + node->next->inside <= chunkSize) {
        while (node->next->next != NULL && node->inside == 0) {
            Node *p = node;
            node = node->next;
            delete p;
        }

        Node *p = node->next;
        for (int i = node->inside; i < node->inside + p->inside; i++) {
            node->data[i] = p->data[i - node->inside];
        }
        node->inside += p->inside;
        p->inside = 0;
        node->next = p->next;
        node->next->prev = node;
        delete p;
    }

    if (node->next->next != NULL && node->inside < chunkSize / 2) {
        Node *p = node->next;
        int temp = ((chunkSize / 2) - node->inside > p->inside)
                       ? p->inside
                       : (chunkSize / 2) - node->inside;

        for (int i = 0; i < temp; i++) {
            node->data[node->inside + i] = node->next->data[i];
        }

        node->inside += temp;
        int temp2 = p->inside - temp;
        if (temp2 == 0) {
            node->next = p->next;
            node->next->prev = node;
            delete p;
        } else {
            for (int i = 0; i < temp2; i++) {
                p->data[i] = p->data[i + temp];
            }
            p->inside -= temp;
        }
    }
}

}  // namespace sjtu

#endif
