#include "gameOfLife.hpp"

GameOfLife::GameOfLife(const int boardSize) : boardSize(boardSize) {}

[[nodiscard]] std::vector<std::vector<int>>
GameOfLife::getLiveNeighbourMatrix(
    const std::vector<std::vector<char>>& board) const {
    auto liveNeighbourMatrix = std::vector<std::vector<int>>(
        this->boardSize, std::vector<int>(this->boardSize));

    for (auto i = 0; i < this->boardSize; ++i) {
        for (auto j = 0; j < this->boardSize; ++j) {
            for (const auto [di, dj] : this->directions) {
                const auto ni = i + di;
                const auto nj = j + dj;
                if (ni >= 0 && ni < this->boardSize && nj >= 0 &&
                    nj < this->boardSize && board[ni][nj] == '#') {
                    ++liveNeighbourMatrix[i][j];
                }
            }
        }
    }

    return liveNeighbourMatrix;
}

[[nodiscard]] std::vector<std::vector<char>> GameOfLife::getNext(
    std::vector<std::vector<char>>& curr) const {
    const auto liveNeighbourMatrix = getLiveNeighbourMatrix(curr);
    auto next = std::vector<std::vector<char>>(
        this->boardSize, std::vector<char>(this->boardSize, '_'));

    for (auto i = 0; i < this->boardSize; ++i) {
        for (auto j = 0; j < this->boardSize; ++j) {
            const auto liveNeighbours = liveNeighbourMatrix[i][j];
            const auto alive = curr[i][j] == '#';
            if (alive && 2 <= liveNeighbours && liveNeighbours <= 3 ||
                !alive && liveNeighbours == 3) {
                next[i][j] = '#';
            }
        }
    }

    return next;
}

[[nodiscard]] std::vector<std::vector<std::vector<char>>>
GameOfLife::runSimulation(
    const std::vector<std::vector<char>>& initial,
    const int maxIterations) const {
    auto res = std::vector<std::vector<std::vector<char>>>{initial};

    for (auto i = 0; i < maxIterations; ++i) {
        res.push_back(getNext(res.back()));
    }

    return res;
}