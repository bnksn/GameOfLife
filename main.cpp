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
                                            const int i, const int j) const {
        auto count = 0;

        for (const auto [di, dj] : directions) {
            const auto ni = i + di;
            const auto nj = j + dj;
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && board[ni][nj] == '#') {
                ++count;
            }
        }

        return count;
    }

    [[nodiscard]] std::vector<std::vector<char>> updateBoard(
        std::vector<std::vector<char>>& curr) const {
        std::vector<std::vector<char>> next(m,
                                            std::vector<char>(n, '_'));  // Create a temporary board

        for (auto i = 0; i < m; ++i) {
            for (auto j = 0; j < n; ++j) {
                const auto liveCount = getLiveNeighbourCount(curr, i, j);
                const auto alive = curr[i][j] == '#';

                if (alive) {
                    next[i][j] = liveCount < 2 || liveCount > 3 ? '_' : '#';
                } else {  // dead
                    next[i][j] = liveCount == 3 ? '#' : '_';
                }
            }
        }

        return next;
    }

   public:
    GameOfLife(int m, int n) : m(m), n(n) {}

    [[nodiscard]] std::vector<std::vector<std::vector<char>>> runSimulation(
        const std::vector<std::vector<char>>& initial, const int maxIterations) const {
        auto res = std::vector<std::vector<std::vector<char>>>();

        auto curr = initial;

        auto iteration = 0;
        while (iteration++ < maxIterations) {
            res.push_back(curr);
            const auto next = updateBoard(curr);
            if (curr == next) {
                break;
            }
            curr = next;
        }

        return res;
    }
};

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