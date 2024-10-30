#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

const int SIZE = 4;

void initializeBoard(std::vector<std::vector<int>>& board);
void drawBoard(const std::vector<std::vector<int>>& board);
bool addRandomTile(std::vector<std::vector<int>>& board);
bool moveLeft(std::vector<std::vector<int>>& board);
bool moveRight(std::vector<std::vector<int>>& board);
bool moveUp(std::vector<std::vector<int>>& board);
bool moveDown(std::vector<std::vector<int>>& board);
bool canMove(const std::vector<std::vector<int>>& board);
bool gameWon(const std::vector<std::vector<int>>& board);

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::vector<std::vector<int>> board(SIZE, std::vector<int>(SIZE, 0));
    initializeBoard(board);

    char input;
    bool moved, addedTile;

    while (true) {
        drawBoard(board);

        if (gameWon(board)) {
            std::cout << "Congratulations! You've reached 2048!\n";
            break;
        }

        if (!canMove(board)) {
            std::cout << "Game Over! No more moves possible.\n";
            break;
        }

        std::cout << "Enter move (w = up, s = down, a = left, d = right, q = quit): ";
        std::cin >> input;

        moved = false;
        switch (input) {
            case 'w': moved = moveUp(board); break;
            case 's': moved = moveDown(board); break;
            case 'a': moved = moveLeft(board); break;
            case 'd': moved = moveRight(board); break;
            case 'q': return 0;
            default: std::cout << "Invalid input!\n"; continue;
        }

        if (moved) {
            addedTile = addRandomTile(board);
            if (!addedTile) {
                std::cout << "Error: No empty space to add a tile!\n";
                break;
            }
        }
    }

    return 0;
}

void initializeBoard(std::vector<std::vector<int>>& board) {
    addRandomTile(board);
    addRandomTile(board);
}

void drawBoard(const std::vector<std::vector<int>>& board) {
    std::system("clear"); // or "cls" for Windows
    for (const auto& row : board) {
        for (const auto& tile : row) {
            std::cout << std::setw(5) << tile;
        }
        std::cout << "\n";
    }
}

bool addRandomTile(std::vector<std::vector<int>>& board) {
    std::vector<std::pair<int, int>> emptyTiles;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                emptyTiles.emplace_back(i, j);
            }
        }
    }

    if (emptyTiles.empty()) {
        return false;
    }

    int index = rand() % emptyTiles.size();
    int value = (rand() % 10 == 0) ? 4 : 2;
    board[emptyTiles[index].first][emptyTiles[index].second] = value;

    return true;
}

bool moveLeft(std::vector<std::vector<int>>& board) {
    bool moved = false;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 1; j < SIZE; ++j) {
            if (board[i][j] != 0) {
                int k = j;
                while (k > 0 && board[i][k - 1] == 0) {
                    board[i][k - 1] = board[i][k];
                    board[i][k] = 0;
                    k--;
                    moved = true;
                }
                if (k > 0 && board[i][k - 1] == board[i][k]) {
                    board[i][k - 1] *= 2;
                    board[i][k] = 0;
                    moved = true;
                }
            }
        }
    }
    return moved;
}

bool moveRight(std::vector<std::vector<int>>& board) {
    bool moved = false;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = SIZE - 2; j >= 0; --j) {
            if (board[i][j] != 0) {
                int k = j;
                while (k < SIZE - 1 && board[i][k + 1] == 0) {
                    board[i][k + 1] = board[i][k];
                    board[i][k] = 0;
                    k++;
                    moved = true;
                }
                if (k < SIZE - 1 && board[i][k + 1] == board[i][k]) {
                    board[i][k + 1] *= 2;
                    board[i][k] = 0;
                    moved = true;
                }
            }
        }
    }
    return moved;
}

bool moveUp(std::vector<std::vector<int>>& board) {
    bool moved = false;
    for (int j = 0; j < SIZE; ++j) {
        for (int i = 1; i < SIZE; ++i) {
            if (board[i][j] != 0) {
                int k = i;
                while (k > 0 && board[k - 1][j] == 0) {
                    board[k - 1][j] = board[k][j];
                    board[k][j] = 0;
                    k--;
                    moved = true;
                }
                if (k > 0 && board[k - 1][j] == board[k][j]) {
                    board[k - 1][j] *= 2;
                    board[k][j] = 0;
                    moved = true;
                }
            }
        }
    }
    return moved;
}

bool moveDown(std::vector<std::vector<int>>& board) {
    bool moved = false;
    for (int j = 0; j < SIZE; ++j) {
        for (int i = SIZE - 2; i >= 0; --i) {
            if (board[i][j] != 0) {
                int k = i;
                while (k < SIZE - 1 && board[k + 1][j] == 0) {
                    board[k + 1][j] = board[k][j];
                    board[k][j] = 0;
                    k++;
                    moved = true;
                }
                if (k < SIZE - 1 && board[k + 1][j] == board[k][j]) {
                    board[k + 1][j] *= 2;
                    board[k][j] = 0;
                    moved = true;
                }
            }
        }
    }
    return moved;
}

bool canMove(const std::vector<std::vector<int>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) return true;
            if (i > 0 && board[i][j] == board[i - 1][j]) return true;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return true;
            if (j > 0 && board[i][j] == board[i][j - 1]) return true;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return true;
        }
    }
    return false;
}

bool gameWon(const std::vector<std::vector<int>>& board) {
    for (const auto& row : board) {
        for (const auto& tile : row) {
            if (tile == 2048) {
                return true;
            }
        }
    }
    return false;
}
