#include <array>
#include <iostream>
#include <vector>

class GameOfLife {
   private:
    int m;
    int n;

    const std::array<std::pair<int, int>, 8> directions{
        std::pair{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}};

    [[nodiscard]] int getLiveNeighbourCount(const std::vector<std::vector<char>>& board,
                                            const int i, const int j) const;

    [[nodiscard]] std::vector<std::vector<char>> updateBoard(
        std::vector<std::vector<char>>& curr) const;

   public:
    GameOfLife(int m, int n);

    [[nodiscard]] std::vector<std::vector<std::vector<char>>> runSimulation(
        const std::vector<std::vector<char>>& initial, const int maxIterations) const;
};