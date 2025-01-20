#include <chrono>
#include <iostream>
#include <thread>

#include "gameOfLife.hpp"

void printResults(
    const std::vector<std::vector<std::vector<char>>>& results) {
    for (const auto& board : results) {
        for (const auto& row : board) {
            for (const auto cell : row) {
                std::cout << cell;
            }
            std::cout << '\n';
        }
        std::cout << '\n';

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

[[nodiscard]]
std::vector<std::vector<char>> createInitialBoard(
    std::vector<std::vector<char>> centre, const int boardSize) {
    auto initial = std::vector<std::vector<char>>(
        boardSize, std::vector<char>(boardSize, '_'));

    const auto centreSize = centre.size();
    const auto topLeftIndex = (boardSize - centreSize) / 2;

    for (auto i = 0; i < centreSize; ++i) {
        for (auto j = 0; j < centreSize; ++j) {
            initial[topLeftIndex + i][topLeftIndex + j] =
                centre[i][j];
        }
    }

    return initial;
}

int main() {
    constexpr auto boardSize = 50;
    constexpr auto numIterations = 70;
    const auto initial = createInitialBoard({{'_', '#', '#', '#'},
                                             {'#', '_', '_', '_'},
                                             {'_', '#', '#', '#'},
                                             {'_', '_', '_', '_'}},
                                            boardSize);

    const auto res =
        GameOfLife(boardSize).runSimulation(initial, numIterations);
    printResults(res);
}