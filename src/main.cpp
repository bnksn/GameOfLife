#include <chrono>
#include <iostream>
#include <thread>

#include "gameOfLife.hpp"

[[nodiscard]]
std::vector<std::vector<char>> createInitialBoard(const std::vector<std::vector<char>>& centre,
                                                  const int boardSize) {
    auto initial = std::vector<std::vector<char>>(boardSize, std::vector<char>(boardSize, '_'));

    const auto centreSize = centre.size();
    const auto topLeftIndex = (boardSize - centreSize) / 2;

    for (auto i = 0; i < centreSize; ++i) {
        for (auto j = 0; j < centreSize; ++j) {
            initial[topLeftIndex + i][topLeftIndex + j] = centre[i][j];
        }
    }

    return initial;
}

template <typename T>
[[nodiscard]]
std::vector<T> flatten2dVector(const std::vector<std::vector<T>>& input) noexcept {
    auto output = std::vector<T>();

    for (const auto& vec : input) {
        output.insert(output.end(), vec.begin(), vec.end());
    }

    return output;
}

int main() {
    constexpr auto boardSize = 160;
    constexpr auto numIterations = 4000;

    const auto centre = std::vector<std::vector<char>>{
        {'_', '#', '#', '#'}, {'#', '_', '_', '_'}, {'_', '#', '#', '#'}, {'_', '_', '_', '_'}};
    const auto initial = createInitialBoard(centre, boardSize);

    const auto gameOfLife = GameOfLife(boardSize);

    const auto start = std::chrono::high_resolution_clock::now();
    const auto boards = gameOfLife.runSimulation(flatten2dVector(initial), numIterations);
    const auto end = std::chrono::high_resolution_clock::now();

    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Cells per millisecond "
              << boardSize * boardSize * numIterations / static_cast<double>(duration.count())
              << '\n';
}