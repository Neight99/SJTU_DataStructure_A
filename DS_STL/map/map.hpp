/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <cstddef>
#include <functional>
#include "exceptions.hpp"
#include "utility.hpp"

typedef unsigned long long ull;

namespace sjtu {
class _Random {
   private:
    ull hashKey;

   public:
    _Random(ull key = 990716) : hashKey(key) {}
    ull hash() {
        hashKey *= 133ULL;
        hashKey += 10205ULL;
        return hashKey;
    }
};

_Random genHash;

template <class Key, class T, class Compare = std::less<Key> >
class map {
   public:
    /**
     * the internal type of data.
     * it should have a default constructor, a copy constructor.
     * You can use sjtu::map as value_type by typedef.
     */
    typedef pair<const Key, T> value_type;

   private:
    struct Node {
        value_type *data;
        ull randomKey;
        Node *left, *right;
        Node *prev, *next;

        Node()
            : data(0),
              left(0),
              right(0),
              prev(0),
              next(0),
              randomKey(genHash.hash()) {}
        Node(const Node &other)
            : left(0), right(0), prev(0), next(0), randomKey(other.randomKey) {
            data = new value_type(*other.data);
        }
        Node(const value_type &val, const ull key = genHash.hash())
            : left(0), right(0), prev(0), next(0), randomKey(key) {
            data = new value_type(val);
        }

        Node &operator=(const Node &right1) {
            if (&right != this) {
                left = 0;
                right = 0;
                next = 0;
                prev = 0;
                randomKey = genHash.hash();
                if (!data) {
                    delete data;
                }
                data = new value_type(*right1.data);
            }
            return *this;
        }

        ~Node() {
            if (data) {
                delete data;
            }
        }
    };

   public:
    /**
     * see BidirectionalIterator at CppReference for help.
     *
     * if there is anything wrong throw invalid_iterator.
     *     like it = map.begin(); --it;
     *       or it = map.end(); ++end();
     */
    class const_iterator;
    class iterator {
        friend class map;
        friend class const_iterator;

       private:
        /**
         * TODO add data members
         *   just add whatever you want.
         */
        Node *node;
        const map *m;

       public:
        iterator(Node *n = 0, const map *m1 = 0) : node(n), m(m1) {
            // TODO
        }
        iterator(const iterator &other) : node(other.node), m(other.m) {
            // TODO
        }
        iterator(const const_iterator &other) : node(other.node), m(other.m) {
            // TODO
        }

        iterator &operator=(const iterator &right) {
            if (&right != this) {
                node = right.node;
                m = right.m;
            }
            return *this;
        }
        /**
         * return a new iterator which pointer n-next elements
         *   even if there are not enough elements, just return the answer.
         * as well as operator-
         */
        /**
         * TODO iter++
         */
        iterator operator++(int) {
            iterator ans(*this);
            ++(*this);
            return ans;
        }
        /**
         * TODO ++iter
         */
        iterator &operator++() {
            if (!node) {
                throw invalid_iterator();
            }
            node = node->next;
            if (!node) {
                throw invalid_iterator();
            }
            return *this;
        }
        /**
         * TODO iter--
         */
        iterator operator--(int) {
            iterator ans(*this);
            --(*this);
            return ans;
        }
        /**
         * TODO --iter
         */
        iterator &operator--() {
            if (!node) {
                throw invalid_iterator();
            }
            node = node->prev;
            if (!node) {
                throw invalid_iterator();
            }
            return *this;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the
         * same memory).
         */
        value_type &operator*() const { return *(node->data); }
        bool operator==(const iterator &rhs) const { return node == rhs.node; }
        bool operator==(const const_iterator &rhs) const {
            return node == rhs.node;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const { return node != rhs.node; }
        bool operator!=(const const_iterator &rhs) const {
            return node != rhs.node;
        }

        /**
         * for the support of it->first.
         * See
         * <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/>
         * for help.
         */
        value_type *operator->() const noexcept { return node->data; }
    };
    class const_iterator {
        // it should has similar member method as iterator.
        //  and it should be able to construct from an iterator.
        friend class map;
        friend class iterator;

       private:
        // data members.
        Node *node;
        const map *m;

       public:
        const_iterator(Node *n = 0, const map *m1 = 0) : node(n), m(m1) {
            // TODO
        }
        const_iterator(const const_iterator &other)
            : node(other.node), m(other.m) {
            // TODO
        }
        const_iterator(const iterator &other) : node(other.node), m(other.m) {
            // TODO
        }
        // And other methods in iterator.
        const_iterator &operator=(const const_iterator &right) {
            if (&right != this) {
                node = right.node;
                m = right.m;
            }
            return *this;
        }
        /**
         * return a new iterator which pointer n-next elements
         *   even if there are not enough elements, just return the answer.
         * as well as operator-
         */
        /**
         * TODO iter++
         */
        // And other methods in iterator.
        const_iterator operator++(int) {
            const_iterator ans(*this);
            ++(*this);
            return ans;
        }
        /**
         * TODO ++iter
         */
        const_iterator &operator++() {
            if (!node) {
                throw invalid_iterator();
            }
            node = node->next;
            if (!node) {
                throw invalid_iterator();
            }
            return *this;
        }
        // And other methods in iterator.
        /**
         * TODO iter--
         */
        const_iterator operator--(int) {
            iterator ans(*this);
            --(*this);
            return ans;
        }
        /**
         * TODO --iter
         */
        const_iterator &operator--() {
            if (!node) {
                throw invalid_iterator();
            }
            node = node->prev;
            if (!node) {
                throw invalid_iterator();
            }
            return *this;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the
         * same memory).
         */
        const value_type &operator*() const { return *(node->data); }
        bool operator==(const iterator &rhs) const { return node == rhs.node; }
        bool operator==(const const_iterator &rhs) const {
            return node == rhs.node;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const { return node != rhs.node; }
        bool operator!=(const const_iterator &rhs) const {
            return node != rhs.node;
        }

        /**
         * for the support of it->first.
         * See
         * <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/>
         * for help.
         */
        const value_type *operator->() const noexcept { return node->data; }
    };
    /**
     * TODO two constructors
     */
    map() : root(0), head(0), Size(0), tail(0) { head = tail = new Node; }
    map(const map &other) : Size(other.Size), root(0), tail(0), head(0) {
        if (!other.root) {
            head = tail = new Node;
        } else {
            root = new Node(*other.root);
            tail = new Node;
            copy(root, other.root);
            Node *temp = 0;
            nxtprv(root, temp);
            temp->next = tail;
            tail->prev = temp;
        }
    }
    /**
     * TODO assignment operator
     */
    map &operator=(const map &other) {
        if (&other != this) {
            clear();
            Size = other.Size;
            if (other.root) {
                root = new Node(*other.root);
                copy(root, other.root);
                Node *temp = 0;
                nxtprv(root, temp);
                temp->next = tail;
                tail->prev = temp;
            }
        }
        return *this;
    }
    /**
     * TODO Destructors
     */
    ~map() {
        clear();
        delete head;
    }
    /**
     * TODO
     * access specified element with bounds checking
     * Returns a reference to the mapped value of the element with key
     * equivalent to key. If no such element exists, an exception of type
     * `index_out_of_bound'
     */
    T &at(const Key &key) {
        Node *ans = find(root, key);
        if (!ans) {
            throw index_out_of_bound();
        }
        return (ans->data->second);
    }
    const T &at(const Key &key) const {
        Node *ans = find(root, key);
        if (!ans) {
            throw index_out_of_bound();
        }
        return (ans->data->second);
    }
    /**
     * TODO
     * access specified element
     * Returns a reference to the value that is mapped to a key equivalent to
     * key, performing an insertion if such key does not already exist.
     */
    T &operator[](const Key &key) {
        Node *ans = insert(pair<Key, T>(key, T())).first.node;
        return (ans->data->second);
    }
    /**
     * behave like at() throw index_out_of_bound if such key does not exist.
     */
    const T &operator[](const Key &key) const {
        Node *ans = find(root, key);
        if (!ans) {
            throw index_out_of_bound();
        }
        return (ans->data->second);
    }
    /**
     * return a iterator to the beginning
     */
    iterator begin() { return iterator(head, this); }
    const_iterator cbegin() const { return const_iterator(head, this); }
    /**
     * return a iterator to the end
     * in fact, it returns past-the-end.
     */
    iterator end() { return iterator(tail, this); }
    const_iterator cend() const { return iterator(tail, this); }
    /**
     * checks whether the container is empty
     * return true if empty, otherwise false.
     */
    bool empty() const { return !root; }
    /**
     * returns the number of elements.
     */
    size_t size() const { return Size; }
    /**
     * clears the contents
     */
    void clear() {
        clear(root);
        delete tail;
        head = tail = new Node;
        root = 0;
        Size = 0;
    }
    /**
     * insert an element.
     * return a pair, the first of the pair is
     *   the iterator to the new element (or the element that prevented the
     * insertion), the second one is true if insert successfully, or false.
     */
    pair<iterator, bool> insert(const value_type &value) {
        Node *node = find(root, value.first);
        if (node) {
            return pair<iterator, bool>(iterator(node, this), 0);
        }
        node = insert(root, value);
        Size++;
        return pair<iterator, bool>(iterator(node, this), 1);
    }
    /**
     * erase the element at pos.
     *
     * throw if pos pointed to a bad element (pos == this->end() || pos points
     * an element out of this)
     */
    void erase(iterator pos) {
        if (pos.m != this || !pos.node || !pos.node->data) {
            throw invalid_iterator();
        }

        Size--;
        remove(root, pos.node->data->first);
    }
    /**
     * Returns the number of elements with key
     *   that compares equivalent to the specified argument,
     *   which is either 1 or 0
     *     since this container does not allow duplicates.
     * The default method of check the equivalence is !(a < b || b > a)
     */
    size_t count(const Key &key) const {
        if (!find(root, key)) {
            return 0;
        } else {
            return 1;
        }
    }
    /**
     * Finds an element with key equivalent to key.
     * key value of the element to search for.
     * Iterator to an element with key equivalent to key.
     *   If no such element is found, past-the-end (see end()) iterator is
     * returned.
     */
    iterator find(const Key &key) {
        Node *ans = find(root, key);

        if (ans == 0) {
            return end();
        }

        return iterator(ans, this);
    }
    const_iterator find(const Key &key) const {
        Node *ans = find(root, key);

        if (ans == 0) {
            return cend();
        }

        return const_iterator(ans, this);
    }

   private:
    Node *head, *tail, *root;
    Compare cmp;
    size_t Size;

    void copy(Node *curr, Node *other) {
        if (other->left) {
            curr->left = new Node(*(other->left));
            copy(curr->left, other->left);
        }
        if (other->right) {
            curr->right = new Node(*(other->right));
            copy(curr->right, other->right);
        }
    }

    void nxtprv(Node *node, Node *&temp) {
        //中序遍历
        if (node->left) {
            nxtprv(node->left, temp);
        }
        if (!temp) {
            head = node;
        }
        node->prev = temp;
        if (temp) {
            temp->next = node;
        }
        temp = node;
        if (node->right) {
            nxtprv(node->right, temp);
        }
    }

    void clear(Node *node) {
        if (!node) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node *find(Node *node, const Key &key) const {
        if (!node) {
            return 0;
        }

        if (cmp(node->data->first, key)) {
            return find(node->right, key);
        } else if (cmp(key, node->data->first)) {
            return find(node->left, key);
        } else {
            return node;
        }
    }

    Node *insert(Node *&node, const value_type &value) {
        Node *temp;
        bool isLeft;
        if (!root) {
            root = new Node(value);
            head = root;
            head->next = tail;
            tail->prev = head;
            return root;
        }
        if (!node) {
            node = new Node(value);
            return node;
        } else if (cmp(value.first, node->data->first)) {
            isLeft = (!node->left);
            temp = insert(node->left, value);
            if (isLeft) {
                temp->next = node;
                temp->prev = node->prev;
                node->prev = temp;
                if (temp->prev) {
                    temp->prev->next = temp;
                } else {
                    head = temp;
                }
            }
            if (node->left->randomKey < node->randomKey) {
                RR(node);
            }
            return temp;
        } else {
            isLeft = (!node->right) ? 0 : 1;
            temp = insert(node->right, value);
            if (!isLeft) {
                temp->prev = node;
                temp->next = node->next;
                node->next = temp;
                temp->next->prev = temp;
            }
            if (node->right->randomKey < node->randomKey) {
                LL(node);
            }
            return temp;
        }
    }

    inline void LL(Node *&node) {
        Node *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        node = temp;
    }

    inline void RR(Node *&node) {
        Node *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        node = temp;
    }

    void remove(Node *&node, const Key &key) {
        if (node) {
            if (cmp(node->data->first, key)) {
                remove(node->right, key);
            } else if (cmp(key, node->data->first)) {
                remove(node->left, key);
            } else {
                if (node->left && node->right) {
                    if (node->left->randomKey < node->right->randomKey) {
                        RR(node);
                        remove(node->right, key);
                    } else {
                        LL(node);
                        remove(node->left, key);
                    }
                } else {
                    Node *temp = node;
                    if (node == head) {
                        head = head->next;
                        head->prev = 0;
                    } else {
                        node->prev->next = node->next;
                        node->next->prev = node->prev;
                    }
                    if (!node->left) {
                        node = node->right;
                    } else {
                        node = node->left;
                    }

                    delete temp;
                }
            }
        }
    }
};

}  // namespace sjtu

#endif
