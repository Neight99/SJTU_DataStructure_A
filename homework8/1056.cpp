#include <iostream>

using namespace std;

const int maxN = 5e5 + 100;

int box[maxN], sugar[maxN], moveTo[maxN] = {0}, boxNow, N, M;

template <class T>
class AvlTree {
   private:
    struct AvlNode {
        T data;
        AvlNode *left;
        AvlNode *right;
        int height;
        AvlNode(const T &otherdata, AvlNode *l, AvlNode *r)
            : data(otherdata), left(l), right(r), height(1) {}
    };

   public:
    AvlTree(AvlNode *t = 0) : root(t) {}
    ~AvlTree() { makeEmpty(root); }
    bool find(const T &x) const { return find(x, root); }
    void insert(const T &x) { insert(x, root); }
    void remove(const T &x) { remove(x, root); }
    T &findkth(int i) { return findkth(i, root); }

   private:
    AvlNode *root;
    void insert(const T &x, AvlNode *&t);
    void remove(const T &x, AvlNode *&t);
    bool find(const T &x, AvlNode *t) const;
    void makeEmpty(AvlNode *&t);
    T &findkth(int i, AvlNode *&t);
    int height(AvlNode *t) { return t == 0 ? 0 : t->height; }
    void LL(AvlNode *&t);
    void RR(AvlNode *&t);
    void LR(AvlNode *&t);
    void RL(AvlNode *&t);
};

template <class T>
void AvlTree<T>::insert(const T &x, AvlNode *&t) {
    if (t == 0) {
        t = new AvlNode(x, 0, 0);
    } else if (x > t->data) {
        insert(x, t->left);
        if (height(t->left) - height(t->right) == 2) {
            if (x > t->left->data) {
                LL(t);
            } else {
                LR(t);
            }
        }
        t->height = height(t->left) + height(t->right) + 1;
    } else {
        insert(x, t->right);
        if (height(t->right) - height(t->left) == 2) {
            if (x <= t->right->data) {
                RR(t);
            } else {
                RL(t);
            }
        }
        t->height = height(t->left) + height(t->right) + 1;
    }
}

template <class T>
void AvlTree<T>::remove(const T &x, AvlNode *&t) {
    if (t == 0) {
        return;
    }
    if (x > t->data) {
        remove(x, t->left);
        if (height(t->right) - height(t->left) == 2) {
            AvlNode *r = t->right;
            if (height(r->left) > height(r->right)) {
                RL(t);
            } else {
                RR(t);
            }
        }
        t->height = height(t->left) + height(t->right) + 1;
    } else if (x < t->data) {
        remove(x, t->right);
        if (height(t->left) - height(t->right) == 2) {
            AvlNode *r = t->left;
            if (height(r->right) > height(r->left)) {
                LR(t);
            } else {
                LL(t);
            }
        }
        t->height = height(t->left) + height(t->right) + 1;
    } else if (t->left != 0 && t->right != 0) {
        if (height(t->left) <= height(t->right)) {
            AvlNode *tmp = t->right;
            while (tmp->left != 0) {
                tmp = tmp->left;
            }
            t->data = tmp->data;
            remove(t->data, t->right);
            t->height = height(t->left) + height(t->right) + 1;
        } else {
            AvlNode *tmp = t->left;
            while (tmp->right != 0) {
                tmp = tmp->right;
            }
            t->data = tmp->data;
            remove(t->data, t->left);
            t->height = height(t->left) + height(t->right) + 1;
        }
    } else {
        AvlNode *old = t;
        t = (t->left != 0) ? t->left : t->right;
        delete old;
    }
}

template <class T>
bool AvlTree<T>::find(const T &x, AvlNode *t) const {
    if (t == 0) {
        return false;
    }

    if (x > t->data) {
        return find(x, t->left);
    }
    if (x < t->data) {
        return find(x, t->right);
    }

    return true;
}

template <class T>
void AvlTree<T>::makeEmpty(AvlNode *&t) {
    if (t == 0) return;
    AvlNode *tmp = t;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete tmp;
    t = 0;
}

template <class T>
T &AvlTree<T>::findkth(int i, AvlNode *&t) {
    int rs = height(t->left);
    if (rs == i - 1) {
        return t->data;
    }

    if (rs >= i) {
        return findkth(i, t->left);
    } else {
        return findkth(i - rs - 1, t->right);
    }
}

template <class T>
void AvlTree<T>::LL(AvlNode *&t) {
    AvlNode *t1 = t->left;
    t->left = t1->right;
    t1->right = t;
    t->height = height(t->left) + height(t->right) + 1;
    t1->height = height(t1->left) + height(t) + 1;
    t = t1;
}

template <class T>
void AvlTree<T>::RR(AvlNode *&t) {
    AvlNode *t1 = t->right;
    t->right = t1->left;
    t1->left = t;
    t->height = height(t->left) + height(t->right) + 1;
    t1->height = height(t1->right) + height(t) + 1;
    t = t1;
}

template <class T>
void AvlTree<T>::LR(AvlNode *&t) {
    RR(t->left);
    LL(t);
}

template <class T>
void AvlTree<T>::RL(AvlNode *&t) {
    LL(t->right);
    RR(t);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int x, y;
    char order;
    AvlTree<int> bst;

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        box[i] = 1;
        bst.insert(1);
        sugar[i] = i;
    }
    boxNow = N;

    for (int times = 0; times < M; times++) {
        cin >> order;
        switch (order) {
            case 'C':
                cin >> x >> y;
                while (moveTo[sugar[x]] != 0) {
                    sugar[x] = moveTo[sugar[x]];
                }
                while (moveTo[sugar[y]] != 0) {
                    sugar[y] = moveTo[sugar[y]];
                }

                if (sugar[x] != sugar[y] && box[sugar[x]] != 0 &&
                    box[sugar[y]] != 0) {
                    bst.remove(box[sugar[x]]);
                    bst.remove(box[sugar[y]]);

                    box[sugar[x]] += box[sugar[y]];
                    box[sugar[y]] = 0;

                    bst.insert(box[sugar[x]]);

                    moveTo[sugar[y]] = sugar[x];
                    boxNow--;
                }
                break;
            case 'D':
                cin >> x;
                while (moveTo[sugar[x]] != 0) {
                    sugar[x] = moveTo[sugar[x]];
                }
                if (box[sugar[x]] != 0) {
                    bst.remove(box[sugar[x]]);
                    box[sugar[x]] = 0;
                    boxNow--;
                }
                break;
            case 'Q':
                cin >> x;
                if (boxNow < x) {
                    cout << 0 << '\n';
                } else {
                    cout << bst.findkth(x) << '\n';
                }
                break;
        }
    }

    return 0;
}