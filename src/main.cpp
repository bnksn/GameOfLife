#include "gameOfLife.hpp"

void printRes(const std::vector<std::vector<std::vector<char>>>& res) {
    for (const auto& board : res) {
        for (const auto& row : board) {
            for (const auto cell : row) {
                std::cout << cell;
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
}

int main() {
    auto initial = std::vector<std::vector<char>>{
        {'_', '_', '_', '_', '_', '_', '_'}, {'_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '#', '_', '_', '_'}, {'_', '_', '#', '#', '#', '_', '_'},
        {'_', '_', '_', '#', '_', '_', '_'}, {'_', '_', '_', '_', '_', '_', '_'},
        {'_', '_', '_', '_', '_', '_', '_'}};

    auto gameOfLife = GameOfLife(7, 7);
    auto res = gameOfLife.runSimulation(initial, 10);
    printRes(res);
}