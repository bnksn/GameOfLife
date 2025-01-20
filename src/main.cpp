#include <chrono>
#include <iostream>
#include <thread>

#include "gameOfLife.hpp"

void printBoard(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto cell : row) {
            std::cout << cell;
        }
        std::cout << '\n';
    }
}

void printRes(
    const std::vector<std::vector<std::vector<char>>>& res) {
    for (const auto& board : res) {
        printBoard(board);
        std::cout << '\n';

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void insertCentre(std::vector<std::vector<char>>& initial,
                  const std::vector<std::vector<char>>& centre,
                  const int boardSize) {
    const auto centreSize = centre.size();
    const auto topLeftIndex = (boardSize - centreSize) / 2;

    for (auto i = 0; i < centreSize; ++i) {
        for (auto j = 0; j < centreSize; ++j) {
            initial[topLeftIndex + i][topLeftIndex + j] =
                centre[i][j];
        }
    }
}

int main() {
    constexpr auto boardSize = 20;
    auto initial = std::vector<std::vector<char>>(
        boardSize, std::vector<char>(boardSize, '_'));

    const auto centre =
        std::vector<std::vector<char>>{{'_', '#', '_', '_'},
                                       {'#', '#', '#', '_'},
                                       {'_', '#', '_', '_'},
                                       {'_', '_', '_', '_'}};

    insertCentre(initial, centre, boardSize);

    const auto gameOfLife = GameOfLife(boardSize);
    constexpr auto numIterations = 50;
    const auto res = gameOfLife.runSimulation(initial, numIterations);
    printRes(res);
}