#pragma once

#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

class GameOfLife {
   public:
    GameOfLife(const std::filesystem::path& initialBoardFile, const int delayMilliseconds);

    void runSimulation();

   private:
    std::filesystem::path _initialBoardFile;
    int _delayMilliseconds;

    [[nodiscard]]
    constexpr std::pair<int, int> getWrappedCoordinates(const int i, const int j, const int numRows,
                                                        const int numCols);

    [[nodiscard]] std::vector<std::vector<int>> getLiveNeighbours(
        const std::vector<std::vector<bool>>& board);

    [[nodiscard]]
    std::vector<std::vector<bool>> readInitialBoard();

    void updateBoard(std::vector<std::vector<bool>>& board);

    void printBoard(const std::vector<std::vector<bool>>& board);

    void clearScreen();
};
