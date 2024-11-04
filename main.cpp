#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int ROWS = 11;
const int COLS = 11;
const int EMPTY = 0;

// Punctaje pentru formațiuni
const int SCORE_LINE_3 = 5;
const int SCORE_LINE_4 = 10;
const int SCORE_LINE_5 = 50;
const int SCORE_L = 20;
const int SCORE_T = 30;

// Generare matrice aleatoare
void initializeBoard(std::vector<std::vector<int>>& board) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = rand() % 5; // 0-4
        }
    }
}

// Verificarea formațiunilor
int checkForMatches(std::vector<std::vector<int>>& board) {
    int score = 0;
    bool matched[ROWS][COLS] = {false};

    // Verificare linii orizontale și verticale
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int current = board[i][j];
            if (current != EMPTY) {
                // Verificare orizontală
                int count = 1;
                for (int k = 1; j + k < COLS && board[i][j + k] == current; k++) {
                    count++;
                }
                if (count >= 3) {
                    score += (count == 3) ? SCORE_LINE_3 :
                             (count == 4) ? SCORE_LINE_4 : SCORE_LINE_5;
                    for (int k = 0; k < count; k++) {
                        matched[i][j + k] = true;
                    }
                }

                // Verificare verticală
                count = 1;
                for (int k = 1; i + k < ROWS && board[i + k][j] == current; k++) {
                    count++;
                }
                if (count >= 3) {
                    score += (count == 3) ? SCORE_LINE_3 :
                             (count == 4) ? SCORE_LINE_4 : SCORE_LINE_5;
                    for (int k = 0; k < count; k++) {
                        matched[i + k][j] = true;
                    }
                }
            }
        }
    }

    // Verificare L-uri
    for (int i = 0; i < ROWS - 2; i++) {
        for (int j = 0; j < COLS - 2; j++) {
            if (board[i][j] != EMPTY) {
                int current = board[i][j];
                // L normal
                if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] &&
                    board[i][j + 1] == current) {
                    score += SCORE_L;
                    matched[i][j] = matched[i + 1][j] = matched[i + 2][j] = matched[i][j + 1] = true;
                }
                // L rotit
                if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] &&
                    board[i + 1][j + 2] == current) {
                    score += SCORE_L;
                    matched[i][j] = matched[i][j + 1] = matched[i][j + 2] = matched[i + 1][j + 2] = true;
                }
            }
        }
    }

    // Verificare T-uri
    for (int i = 0; i < ROWS - 2; i++) {
        for (int j = 0; j < COLS - 2; j++) {
            if (board[i][j] != EMPTY) {
                int current = board[i][j];
                // T normal
                if (board[i][j] == board[i + 1][j] && board[i + 2][j] == current &&
                    board[i + 1][j + 1] == current) {
                    score += SCORE_T;
                    matched[i][j] = matched[i + 1][j] = matched[i + 2][j] = matched[i + 1][j + 1] = true;
                }
                // T rotit
                if (board[i][j] == board[i][j + 1] && board[i][j + 2] == current &&
                    board[i + 1][j + 1] == current) {
                    score += SCORE_T;
                    matched[i][j] = matched[i][j + 1] = matched[i][j + 2] = matched[i + 1][j + 1] = true;
                }
            }
        }
    }

    // Dispar bomboanele identificate
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matched[i][j]) {
                board[i][j] = EMPTY;
            }
        }
    }

    return score;
}

// Actualizarea matricei după dispariția bomboanelor
void updateBoard(std::vector<std::vector<int>>& board) {
    for (int j = 0; j < COLS; j++) {
        for (int i = ROWS - 1; i >= 0; i--) {
            if (board[i][j] == EMPTY) {
                for (int k = i - 1; k >= 0; k--) {
                    if (board[k][j] != EMPTY) {
                        board[i][j] = board[k][j];
                        board[k][j] = EMPTY;
                        break;
                    }
                }
            }
        }
    }
}

// Funcția principală pentru a rula jocul
int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::vector<std::vector<int>> board(ROWS, std::vector<int>(COLS));
    int totalScore = 0;
    int jocuriJucate = 100;

    for (int joc = 0; joc < jocuriJucate; joc++) {
        initializeBoard(board);
        int scor = 0;
        bool gasitForma;

        do {
            gasitForma = false;
            int scorFormatii = checkForMatches(board);
            if (scorFormatii > 0) {
                scor += scorFormatii;
                gasitForma = true;
                updateBoard(board);
            }
        } while (gasitForma && scor < 10000);

        totalScore += scor;
        std::cout << "Joc " << joc + 1 << ": Scor = " << scor << std::endl;
    }

    std::cout << "Scor total = " << totalScore << std::endl;
    std::cout << "Scor mediu = " << static_cast<double>(totalScore) / jocuriJucate << std::endl;

    return 0;
}















