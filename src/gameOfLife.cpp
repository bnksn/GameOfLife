#include "gameOfLife.hpp"

GameOfLife::GameOfLife(const std::filesystem::path& initialBoardFile, const int delayMilliseconds)
    : _initialBoardFile(std::move(initialBoardFile)), _delayMilliseconds(delayMilliseconds) {}

constexpr std::pair<int, int> GameOfLife::getWrappedCoordinates(const int i, const int j,
                                                                const int numRows,
                                                                const int numCols) {
    return {(i + numRows) % numRows, (j + numCols) % numCols};
}

void GameOfLife::runSimulation() {
    auto board = readInitialBoard();

    auto currBoard = 1;
    while (true) {
        clearScreen();
        std::cout << "board: " << currBoard++ << '\n';
        printBoard(board);
        updateBoard(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(_delayMilliseconds));
    }
}

[[nodiscard]] std::vector<std::vector<int>> GameOfLife::getLiveNeighbours(
    const std::vector<std::vector<bool>>& board) {
    const auto numRows = static_cast<int>(board.size());
    const auto numCols = static_cast<int>(board[0].size());

    auto liveNeighbourMatrix = std::vector<std::vector<int>>(numRows, std::vector<int>(numCols, 0));

    constexpr auto directions = std::array<std::pair<int, int>, 8>{
        std::pair{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}};
    for (auto i = 0; i < numRows; ++i) {
        for (auto j = 0; j < numCols; ++j) {
            for (const auto& [di, dj] : directions) {
                const auto [ni, nj] = getWrappedCoordinates(i + di, j + dj, numRows, numCols);
                if (board[ni][nj]) {
                    ++liveNeighbourMatrix[i][j];
                }
            }
        }
    }

    return liveNeighbourMatrix;
}

void GameOfLife::updateBoard(std::vector<std::vector<bool>>& board) {
    const auto liveNeighbours = getLiveNeighbours(board);

    for (auto i = 0; i < board.size(); ++i) {
        for (auto j = 0; j < board[0].size(); ++j) {
            const auto numLiveNeighbours = liveNeighbours[i][j];
            const auto isAlive = board[i][j];
            board[i][j] = isAlive && 2 <= numLiveNeighbours && numLiveNeighbours <= 3 ||
                          !isAlive && numLiveNeighbours == 3;
        }
    }
}

void GameOfLife::printBoard(const std::vector<std::vector<bool>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            std::cout << (cell ? '#' : '_') << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void GameOfLife::clearScreen() {
#ifdef _WIN32
    std::system("cls");
#elif __linux__ || __unix__
    std::system("clear");
#else
    throw std::runtime_error("Cannot clear screen. OS not recognised.");
#endif
}

[[nodiscard]]
std::vector<std::vector<bool>> GameOfLife::readInitialBoard() {
    std::vector<std::vector<bool>> board;
    auto file = std::ifstream(_initialBoardFile);

    if (file.is_open()) {
        for (auto line = std::string(); std::getline(file, line);) {
            auto row = std::vector<bool>();
            auto ss = std::istringstream(line);
            for (auto symbol = ' '; ss >> symbol;) {
                row.push_back(symbol == '#');
            }

            board.push_back(row);
        }

        file.close();
    } else {
        throw std::runtime_error("Failed to open initial board file: " +
                                 _initialBoardFile.string());
    }

    return board;
}
