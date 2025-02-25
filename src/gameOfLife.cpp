#include "gameOfLife.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <print>
#include <thread>

GameOfLife::GameOfLife(const int delayMilliseconds) : _delayMilliseconds(delayMilliseconds) {}

void GameOfLife::readInitialBoard(const std::filesystem::path& initialBoardFile) {
    auto board = std::vector<std::vector<bool>>();
    auto file = std::ifstream(initialBoardFile);

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
        throw std::runtime_error("Failed to open initial board file: " + initialBoardFile.string());
    }

    _numRows = static_cast<int>(board.size());
    _numCols = static_cast<int>(board[0].size());

    _board = board;
    _nextBoard = board;
}

void GameOfLife::runSimulation(const int numIterations) {
    auto totalBoardUpdateTimeNs = 0l;

    for (auto i = 1; i <= numIterations; ++i) {
        const auto currBoardAsString = getBoardAsString();
        clearScreen();
        std::print("Iteration: {}\n{}", i, currBoardAsString);

        const auto start = std::chrono::high_resolution_clock::now();
        updateBoard();
        const auto end = std::chrono::high_resolution_clock::now();
        totalBoardUpdateTimeNs +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        std::this_thread::sleep_for(std::chrono::milliseconds(_delayMilliseconds));
    }

    std::println("Average time per board update (ns): {}",
                 static_cast<double>(totalBoardUpdateTimeNs) / numIterations);
}

[[nodiscard]]
std::string GameOfLife::getBoardAsString() const {
    auto ss = std::stringstream();
    for (const auto& row : _board) {
        for (const auto& cell : row) {
            ss << (cell ? '#' : '_') << ' ';
        }
        ss << '\n';
    }

    return ss.str();
}

[[nodiscard]]
constexpr std::pair<int, int> GameOfLife::getWrappedCoordinates(const int i, const int j) const {
    return {(i + _numRows) % _numRows, (j + _numCols) % _numCols};
}

[[nodiscard]]
int GameOfLife::countLiveNeighbours(const int i, const int j) const {
    auto liveNeighbours = 0;
    for (const auto& [di, dj] : _directions) {
        const auto [ni, nj] = getWrappedCoordinates(i + di, j + dj);
        if (_board[ni][nj]) {
            ++liveNeighbours;
        }
    }

    return liveNeighbours;
}

void GameOfLife::updateBoard() {
    for (auto i = 0; i < _numRows; ++i) {
        for (auto j = 0; j < _numCols; ++j) {
            const auto liveNeighbours = countLiveNeighbours(i, j);
            _nextBoard[i][j] = _board[i][j] && (liveNeighbours == 2 || liveNeighbours == 3) ||
                               !_board[i][j] && liveNeighbours == 3;
        }
    }

    std::swap(_board, _nextBoard);
}

void GameOfLife::clearScreen() const {
#ifdef _WIN32
    std::system("cls");
#elif __linux__ || __unix__
    std::system("clear");
#else
    throw std::runtime_error("Cannot clear screen. OS not recognised.");
#endif
}
