#include "gameOfLife.hpp"

GameOfLife::GameOfLife(BoardDimensions dim) : dim(dim) {}

[[nodiscard]] std::vector<std::vector<int>> GameOfLife::getLiveNeighbourMatrix(
    const std::vector<std::vector<char>>& board) const {
    auto liveNeighbourMatrix = std::vector<std::vector<int>>(
        this->dim.height, std::vector<int>(this->dim.width));

    for (auto i = 0; i < this->dim.height; ++i) {
        for (auto j = 0; j < this->dim.width; ++j) {
            auto count = 0;
            for (const auto [di, dj] : this->directions) {
                const auto ni = i + di;
                const auto nj = j + dj;
                if (ni >= 0 && ni < dim.height && nj >= 0 && nj < dim.width &&
                    board[ni][nj] == '#') {
                    ++count;
                }
            }
            liveNeighbourMatrix[i][j] = count;
        }
    }

    return liveNeighbourMatrix;
}

[[nodiscard]] std::vector<std::vector<char>> GameOfLife::getNext(
    std::vector<std::vector<char>>& curr) const {
    const auto liveNeighbourMatrix = getLiveNeighbourMatrix(curr);
    auto next = std::vector<std::vector<char>>(
        dim.height, std::vector<char>(dim.width, '_'));

    for (auto i = 0; i < dim.height; ++i) {
        for (auto j = 0; j < dim.width; ++j) {
            const auto liveCount = liveNeighbourMatrix[i][j];
            const auto alive = curr[i][j] == '#';
            if (alive && 2 <= liveCount && liveCount <= 3 ||
                !alive && liveCount == 3) {
                next[i][j] = '#';
            }
        }
    }

    return next;
}

[[nodiscard]] std::vector<std::vector<std::vector<char>>>
GameOfLife::runSimulation(const std::vector<std::vector<char>>& initial,
                          const int maxIterations) const {
    auto res = std::vector<std::vector<std::vector<char>>>{initial};

    for (auto i = 0; i < maxIterations; ++i) {
        res.push_back(getNext(res.back()));
    }

    return res;
}