#include<iostream>
#include<vector>
#include <cstdlib>

/*надо сделать выведение всего пустого пространства при его большом количестве*/

using namespace std;

int mine = 15;

bool blast = false;

int flags_true = mine;

vector<vector<int>> field = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                              { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

vector<vector<int>> field_flags = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };



int random(int min, int max) {
    int rN = rand() % (max - min + 1) + min;
    return rN;
}

void fill_mine() {
    int j = random(0, 9), h = random(0, 9);
    for (int i = 0; i < mine; i++) {
        while (field[j][h] != 0) {
            j = random(0, 9);
            h = random(0, 9);
        }
        field[j][h] = 9;
    }
}

void fill_num() {
    int count = 0;
    for (int i = 0; i < 10; i++) {
        for (int o = 0; o < 10; o++) {
            count = 0;
            if (field[i][o] != 9) {
                for (int q = i - 1; q <= i + 1; q++) {
                    for (int w = o - 1; w <= o + 1; w++) {
                        if (q >= 0 && q < 10 && w >= 0 && w < 10) {
                            if (field[q][w] == 9) {
                                count++;
                            }
                        }
                    }
                }
                field[i][o] = count;
            }

        }
    }
}

void print_debug() {
    for (int q = 0; q < 10; q++) {
        for (int w = 0; w < 10; w++) {
            cout << field[q][w] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void print() {
    cout << flags_true << endl;
    for (int i = 0; i < 10; i++) {
        for (int o = 0; o < 10; o++) {
            if (field_flags[i][o] == 0) {
                cout << " - ";
            }
            else if (field_flags[i][o] == 1) {
                cout << " F ";
            }
            else if (field_flags[i][o] == 2) {
                if (field[i][o] != 9) {
                    if(field[i][o] != 0) {
                        cout << " " << field[i][o] << " ";
                    }
                    else {
                        cout << " # ";
                    }
                }
                else {
                    cout << " * ";
                    blast = true;
                }
            }
        }
        cout << endl;
    }
    cout << endl;

}

void game_process() {
    int x, y;
    string op;
    while (blast == false || flags_true != 0) {
        cin >> x >> y >> op;
        if (op == "f") {
            field_flags[x][y] = 1;
            if (field[x][y] == 9) {
                flags_true--;
            }
        }
        else if (op == "o") {
            field_flags[x][y] = 2;
        }
        print();
    }
}

int main() {
    string pasw;
    srand(static_cast<unsigned int>(time(nullptr)));
    fill_mine();
    fill_num();
    cout << "enter something" << endl;
    cin >> pasw;
    if (pasw == "DB") {
        print_debug();
    }
    print();
    game_process();
}