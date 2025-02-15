#pragma once

#include <array>
#include <filesystem>
#include <vector>

class GameOfLife {
   public:
    GameOfLife(const int delayMilliseconds);

    void readInitialBoard(const std::filesystem::path& initialBoardFile);

    void runSimulation(const int numIterations);

    [[nodiscard]]
    std::string getBoardAsString() const;

   private:
    int _delayMilliseconds{};

    std::vector<std::vector<bool>> _board;
    std::vector<std::vector<bool>> _nextBoard;
    int _numRows{};
    int _numCols{};

    static constexpr std::array<std::pair<int, int>, 8> _directions = {
        std::pair{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}};

    [[nodiscard]]
    constexpr std::pair<int, int> getWrappedCoordinates(const int i, const int j) const;

    [[nodiscard]]
    int countLiveNeighbours(const int i, const int j) const;

    void updateBoard();

    void clearScreen() const;
};
