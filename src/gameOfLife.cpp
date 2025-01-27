#include "gameOfLife.hpp"

GameOfLife::GameOfLife(const int boardSize) : boardSize(boardSize) {}

[[nodiscard]] std::vector<int> GameOfLife::getLiveNeighbours(const std::vector<char>& board) const {
    auto liveNeighbourMatrix =
        std::vector<int>(static_cast<long>(this->boardSize) * this->boardSize);

    for (auto i = 0; i < this->boardSize; ++i) {
        for (auto j = 0; j < this->boardSize; ++j) {
            for (const auto& [di, dj] : directions) {
                const int ni = i + di;
                const int nj = j + dj;

                if (ni < 0 || ni == this->boardSize || nj < 0 || nj == this->boardSize) {
                    continue;
                }

                if (board[ni * this->boardSize + nj] == '#') {
                    ++liveNeighbourMatrix[i * this->boardSize + j];
                }
            }
        }
    }

    return liveNeighbourMatrix;
}

[[nodiscard]] std::vector<char> GameOfLife::getNext(const std::vector<char>& curr) const {
    const auto liveNeighbours = getLiveNeighbours(curr);
    auto next = std::vector<char>(static_cast<long>(this->boardSize) * this->boardSize, '_');

    for (auto index = 0; index < this->boardSize * this->boardSize; ++index) {
        const auto numLiveNeighbours = liveNeighbours[index];
        const auto alive = curr[index] == '#';

        if (alive && 2 <= numLiveNeighbours && numLiveNeighbours <= 3 ||
            !alive && numLiveNeighbours == 3) {
            next[index] = '#';
        }
    }

    return next;
}

[[nodiscard]] std::vector<std::vector<char>> GameOfLife::runSimulation(
    const std::vector<char>& initial, const int maxIterations) const {
    std::vector<std::vector<char>> res{initial};

    for (auto i = 0; i < maxIterations; ++i) {
        res.push_back(getNext(res.back()));
    }

    return res;
}