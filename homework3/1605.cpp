#include <iostream>

using namespace std;

char input1[1001000], save[1001000];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, choice, inputCount = 0, saveCount = 0, wrong = 0;
    char ch;

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> choice;

        if (choice == 1) {
            cin >> ch;
            input1[++inputCount] = ch;
            if (wrong) {  //如果已经有问题就直接跳过下面的部分
                continue;
            } else if (ch == ')' || ch == ']' || ch == '}') {
                if ((saveCount == 0) || (ch == ')' && save[saveCount] != '(') ||
                    (ch == ']' && save[saveCount] != '[') ||
                    (ch == '}' && save[saveCount] != '{')) {
                    wrong = inputCount;  //记录下有问题的位置
                } else {  //如果新输入的和之前的左括号配对了，就直接把第二个栈的左括号删去
                    saveCount--;
                }
            } else {  //如果输入进来的是左括号，就直接将其存入第二个栈
                save[++saveCount] = ch;
            }
        } else if (choice == 2) {
            if (inputCount) {
                if (wrong) {
                    inputCount--;
                    if (wrong >
                        inputCount) {  //如果有问题的部分已经被pop，则直接重置错误位置
                        wrong = 0;
                    }
                } else {
                    if (input1[inputCount] == '(' ||
                        input1[inputCount] == '[' ||
                        input1[inputCount] == '{') {
                        saveCount--;
                    } else if (input1[inputCount] == ')') {
                        save[++saveCount] = '(';
                    } else if (input1[inputCount] == ']') {
                        save[++saveCount] = '[';
                    } else if (input1[inputCount] == '}') {
                        save[++saveCount] = '{';
                    }
                    inputCount--;
                }
            }
        } else if (choice == 3) {
            if (inputCount) {
                cout << input1[inputCount] << '\n';
            }
        } else if (choice == 4) {
            if (wrong == 0 &&
                saveCount == 0) {  //没有错误同时第二个栈没东西了才输出YES
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}