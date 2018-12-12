#include <iostream>

using namespace std;

class sudoku {
   private:
    int **storage;

   public:
    sudoku();
    ~sudoku();
    bool checkline();
    bool checkcolumn();
    bool checknine();
    friend istream &operator>>(istream &, sudoku &);
};

sudoku::sudoku() {
    storage = new int *[9];
    for (int i = 0; i < 9; i++) {
        storage[i] = new int[9];
        for (int j = 0; j < 9; j++) {
            storage[i][j] = 0;
        }
    }
}

sudoku::~sudoku() {
    for (int i = 0; i < 9; i++) {
        delete[] storage[i];
    }
    delete[] storage;
    storage = NULL;
}

bool sudoku::checkline() {
    bool line[9][9] = {0};
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int tmp = storage[i][j];
            if (line[i][tmp - 1] == 0) {
                line[i][tmp - 1] = 1;
            } else {
                return 0;
            }
        }
    }
    return 1;
}

bool sudoku::checkcolumn() {
    bool line[9][9] = {0};
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            int tmp = storage[i][j];
            if (line[tmp - 1][j] == 0) {
                line[tmp - 1][j] = 1;
            } else {
                return 0;
            }
        }
    }
    return 1;
}

bool sudoku::checknine() {
    bool line[9][9] = {0};
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int tmp = storage[i][j];
            if (line[(i / 3) * 3 + j / 3][tmp - 1] == 0) {
                line[(i / 3) * 3 + j / 3][tmp - 1] = 1;
            } else {
                return 0;
            }
        }
    }
    return 1;
}

istream &operator>>(istream &is, sudoku &s) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            is >> s.storage[i][j];
        }
    }
    return is;
}

int main() {
    int n;
    sudoku *su;

    cin >> n;
    su = new sudoku[n];
    for (int i = 0; i < n; i++) {
        cin >> su[i];
    }

    for (int i = 0; i < n; i++) {
        bool check =
            (su[i].checkline() && su[i].checkcolumn() && su[i].checknine());
        if (check == 1) {
            cout << "Right" << endl;
        } else {
            cout << "Wrong" << endl;
        }
    }

    return 0;
}