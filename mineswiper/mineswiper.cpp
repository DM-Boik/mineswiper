#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <string>

/*надо сделать выведение всего пустого пространства при его большом количестве*/

using namespace std;

int mine = 10;

bool blast = false;
int flags_true = mine;

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
static WORD defaultAttr = 0;

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

void initConsoleColor() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        defaultAttr = csbi.wAttributes;
    }
    else {
        defaultAttr = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }
}

void setColor(WORD attr) {
    SetConsoleTextAttribute(hConsole, attr);
}

void printColored(const std::string& s, WORD color) {
    setColor(color);
    std::cout << s;
    setColor(defaultAttr);
}

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
    std::cout << flags_true << std::endl;
    for (int i = 0; i < 10; i++) {
        for (int o = 0; o < 10; o++) {
            if (field_flags[i][o] == 0) {
                printColored(" - ", defaultAttr);
            }
            else if (field_flags[i][o] == 1) {
                printColored(" F ", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else if (field_flags[i][o] == 2) {
                if (field[i][o] != 9) {
                    if (field[i][o] != 0) {
                        WORD col;
                        switch (field[i][o]) {
                        case 1: col = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
                        case 2: col = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
                        case 3: col = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
                        case 4: col = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
                        case 5: col = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;

                        default: col = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
                        }
                        printColored(" " + to_string(field[i][o]) + " ", col);
                    }
                    else {
                        // пустое открытое —  серое
                        printColored(" # ", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    }
                }
                else {
                    // мина красная
                    printColored(" * ", FOREGROUND_RED | FOREGROUND_INTENSITY);
                    blast = true;
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void game_process() {
    int x, y;
    string op;
    while (blast != true && flags_true != 0) {
        cin >> x >> y >> op;
        x--;
        y--;
        if (x >= 1 && x <= 10 && y >= 1 && y <= 10) {
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
        else {
			cout << "wrong coordinates" << endl << "try again" << endl;
        }
    }
}

int main() {
    initConsoleColor();
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