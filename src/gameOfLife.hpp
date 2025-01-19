#include <array>
#include <vector>

struct BoardDimensions {
    int height;
    int width;
};

class GameOfLife {
   private:
    BoardDimensions dim;

    const std::array<std::pair<int, int>, 8> directions{
        std::pair{-1, 1}, {0, 1},  {1, 1},   {1, 0},
        {1, -1},          {0, -1}, {-1, -1}, {-1, 0}};

    [[nodiscard]] std::vector<std::vector<int>> getLiveNeighbourMatrix(
        const std::vector<std::vector<char>>& board) const;

    [[nodiscard]] std::vector<std::vector<char>> getNext(
        std::vector<std::vector<char>>& curr) const;

   public:
    GameOfLife(BoardDimensions);

    [[nodiscard]] std::vector<std::vector<std::vector<char>>> runSimulation(
        const std::vector<std::vector<char>>& initial,
        const int maxIterations) const;
};