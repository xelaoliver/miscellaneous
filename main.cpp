#include <iostream>
#include <map>
using namespace std;

// Alex Oliver, 2025

int intInArray(int intArgument, int * array, int length) {
    // returns true if int is in array, if else, returns false
    for (int n = 0; n < length; n ++) {
        if (array[n] == intArgument) {
            return true;
        }
    }

    return false;
}

void printGame(int * code, bool reveal, int round, int log[10][4], int mark[10][2], string information[5]) {
    cout << "+---------+-----+" << endl << "|  MASTER MIND  |" << endl;

    // reveal code if reveal is true
    if (reveal) {
        cout << "| ";
        for (int p = 0; p < 4; p ++) {
            cout << code[p] << " ";
        }
        cout << "| \e[0;32mX\033[0m \e[0;33mX\033[0m |" << endl;
    } else {
        cout << "| ? ? ? ? | \e[0;32mX\033[0m \e[0;33mX\033[0m |" << endl;
    }

    cout << "+---------+-----+" << endl;

    for (int p = 9; p >= 0; p --) {
        if (p <= round) {
            cout << "| ";
            for (int pp = 0; pp < 4; pp ++) {
                cout << log[p][pp] << " ";
            }
            cout << "|";
        } else {
            cout << "| ' ' ' ' |";
        }

        if (mark[p][0] != 0) {
            cout << " \e[0;32m" << mark[p][0] << "\033[0m";
        } else {
            cout << "  ";
        }
        if (mark[p][1] != 0) {
            cout << " \e[0;33m" << mark[p][1] << "\033[0m";
        } else {
            cout << "  ";
        }
        cout << " |";

        cout << "\t" << information[9-p] << endl;
    }

    cout << "+---------+-----+" << endl;
}


int main() {
    srand(time(NULL));

    // randomly generate code for user to crack
    int code[4] = {
        0, 0, 0, 0
    };

    int randomInt; // ensure that no number is generated twice

    for (int i = 0; i < 4; i ++) {
        randomInt = 0;
        while (intInArray(randomInt, code, 4)) {
            randomInt = rand()%6;
        }

        code[i] = randomInt;
    }

    /* print out code
    cout << "code = {";
    for (int i = 0; i < 3; i ++) {
        cout << code[i] << " ";
    }
    cout << code[3] << "}" << endl;
    */

    string information[10] = {
        "Input 0/1/2/3/4/5, they correlate to colours",
        "",
        "\e[0;32mX\033[0m - Correct",
        "\e[0;33mX\033[0m - Wrong position",
        "", "", "", "", "",
        "MASTERMIND Program by Alex Oliver, 2025"
    };

    // main game

    // initialise variables
    string guessString;
    int log[10][4]; // store previous guesses
    int mark[10][2]; // store previous correct/not guesses
    for (int i = 0; i < 10; i ++) {
        mark[i][0] = 0;
        mark[i][1] = 0;
    }
    int guess[4]; // store guess for 1 round
    int correct; // total number of correct numbers
    int position; // total number of correct numbers, but in the wrong position
    bool codeUsed[4];
    bool guessUsed[4];

    for (int g = 0; g < 10; g ++) {
        guessString = "";
        while (guessString.length() != 7) {
            cout << "Your guess: ";
            cin >> guessString;
        }

        for (int k = 0; k < 4; k ++) {
            guess[k] = guessString[k*2]-'0';
            log[g][k] = guessString[k*2]-'0';
        }

        codeUsed[0] = false; codeUsed[1] = false; codeUsed[2] = false; codeUsed[3] = false;
        guessUsed[0] = false; guessUsed[1] = false; guessUsed[2] = false; guessUsed[3] = false;
        position = 0; correct = 0;
        // correct position
        for (int i = 0; i < 4; i++) {
            if (guess[i] == code[i]) {
                correct ++;
                codeUsed[i] = true;
                guessUsed[i] = true;
            }
        }

        // wrong position
        for (int i = 0; i < 4; i++) {
            if (guessUsed[i]) continue;

            for (int j = 0; j < 4; j++) {
                if (!codeUsed[j] && guess[i] == code[j]) {
                    position ++;
                    codeUsed[j] = true;

                    break;
                }
            }
        }


        mark[g][0] = correct;
        mark[g][1] = position;

        if (correct == 4) {
            printGame(code, true, g, log, mark, information);

            cout << "Well done.";

            return 0;
        } else {
            if (g == 9) {
                printGame(code, true, g, log, mark, information);
            } else {
                printGame(code, false, g, log, mark, information);
            }
        }
    }

    cout << "Too bad.";

    return 0;
}