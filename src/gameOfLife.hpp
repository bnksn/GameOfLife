#include <array>
#include <vector>

class GameOfLife {
   private:
    int boardSize;

    static constexpr std::array<std::pair<int, int>, 8> directions{
        std::pair{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}};

    [[nodiscard]] std::vector<int> getLiveNeighbours(const std::vector<char>& board) const;

    [[nodiscard]] std::vector<char> getNext(const std::vector<char>& curr) const;

   public:
    GameOfLife(int boardSize);

    [[nodiscard]] std::vector<std::vector<char>> runSimulation(const std::vector<char>& initial,
                                                               const int maxIterations) const;
};