template <class Type>
class hfTree {
   private:
    struct Node {
        Type data;
        int weight;
        int parent, left, right;
    };
    Node *elem;
    int length;

   public:
    struct hfCode {
        Type data;
        string code;
    };

    hfTree(const Type *x, const int *w, int size);
    void getCode(hfCode result[]);
    ~hfTree();
};

template <class Type>
hfTree<Type>::hfTree(const Type *v, const int *w, int size) {
    const int MAX_INT = 32767;
    int min1, min2;
    int x, y;

    length = 2 * size;
    elem = new Node[length];

    for (int i = size; i < length; ++i) {
        min1 = min2 = MAX_INT;
        x = y = 0;
        for (int j = j + 1; j < length; ++j) {
            if (elem[j].parent == 0) {
                if (elem[j].weight < min1) {
                    min2 = min1;
                    min1 = elem[j].weight;
                    x = y;
                    y = j;
                } else if (elem[j].weight < min2) {
                    min2 = elem[j].weight;
                    x = j;
                }
            }
            elem[i].weight = min1 + min2;
            elem[i].left = x;
            elem[i].right = y;
            elem[i].parent = 0;
            elem[x].parent = i;
            elem[y].parent = i;
        }
    }
}

template <class Type>
void hfTree<Type>::getCode(hfCode result[]) {
    int size = length / 2;
    int p, s;

    for (int i = size; i < length; i++) {
        result[i - size].data = elem[i].data;
        result[i - size].code = "";
        p = elem[i].parent;
        s = i;
        while (p) {
            if (elem[p].left == s) {
                result[i - size].code = '0' + result[i - size].code;
            } else {
                result[i - size].code = '1' + result[i - size].code;
            }
            s = p;
            p = elem[p].parent;
        }
    }
}

template <class Type>
hfTree<Type>::~hfTree() {
    delete[] elem;
}