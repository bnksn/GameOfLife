#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

constexpr static auto directions = std::array<std::pair<int, int>, 8>{
    std::pair{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}};

[[nodiscard]]
std::vector<std::vector<bool>> createInitialBoard(const std::vector<std::vector<bool>>& centre,
                                                  const int boardSize) {
    auto initial = std::vector<std::vector<bool>>(boardSize, std::vector<bool>(boardSize));

    const auto topLeftIndex = (boardSize - centre.size()) / 2;
    for (auto i = 0; i < centre.size(); ++i) {
        for (auto j = 0; j < centre.size(); ++j) {
            initial[topLeftIndex + i][topLeftIndex + j] = centre[i][j];
        }
    }

    return initial;
}

[[nodiscard]]
std::pair<int, int> getWrappedCoordinates(int i, int j, const int boardSize) {
    if (i < 0) {
        i += boardSize;
    }
    i %= boardSize;

    if (j < 0) {
        j += boardSize;
    }
    j %= boardSize;

    return {i, j};
}

[[nodiscard]] std::vector<std::vector<int>> getLiveNeighbours(
    const std::vector<std::vector<bool>>& board) {
    const auto size = static_cast<int>(board.size());
    auto liveNeighbourMatrix = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));

    for (auto i = 0; i < size; ++i) {
        for (auto j = 0; j < size; ++j) {
            for (const auto& [di, dj] : directions) {
                const auto& [ni, nj] = getWrappedCoordinates(i + di, j + dj, size);
                if (ni >= 0 && ni < size && nj >= 0 && nj < size && board[ni][nj]) {
                    ++liveNeighbourMatrix[i][j];
                }
            }
        }
    }

    return liveNeighbourMatrix;
}

void updateBoard(std::vector<std::vector<bool>>& board) {
    const auto liveNeighbours = getLiveNeighbours(board);

    for (auto i = 0; i < board.size(); ++i) {
        for (auto j = 0; j < board.size(); ++j) {
            const auto numLiveNeighbours = liveNeighbours[i][j];
            const auto isAlive = board[i][j];
            board[i][j] = isAlive && 2 <= numLiveNeighbours && numLiveNeighbours <= 3 ||
                          !isAlive && numLiveNeighbours == 3;
        }
    }
}

void printBoard(const std::vector<std::vector<bool>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            std::cout << (cell ? '#' : '_') << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#elif __linux__ || __unix__
    std::system("clear");
#else
    throw std::runtime_error("Cannot clear screen. OS not recognised.");
#endif
}

int main() {
    constexpr auto boardSize = 35;
    constexpr auto delayMilliseconds = 400;
    const auto centre = std::vector<std::vector<bool>>{{false, true, true, true},
                                                       {true, false, false, false},
                                                       {false, true, true, true},
                                                       {false, false, false, false}};
    auto board = createInitialBoard(centre, boardSize);

    while (true) {
        clearScreen();
        printBoard(board);
        updateBoard(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
    }
}