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
    GameOfLife(const int delayMilliseconds);

    void readInitialBoard(const std::filesystem::path& initialBoardFile);

    void runSimulation(const int numIterations);

    [[nodiscard]]
    std::vector<std::vector<bool>> getBoard() const;

   private:
    int _delayMilliseconds{};

    std::vector<std::vector<bool>> _board;
    int _numRows{};
    int _numCols{};

    [[nodiscard]]
    constexpr std::pair<int, int> getWrappedCoordinates(const int i, const int j) const;

    [[nodiscard]] std::vector<std::vector<int>> getLiveNeighbours() const;

    void updateBoard();

    void clearScreen() const;

    [[nodiscard]]
    std::string getBoardAsString() const;
};
