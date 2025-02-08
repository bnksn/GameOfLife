#include "gameOfLife.hpp"

int main(int argc, char* argv[]) {
    try {
        const auto args = std::span(argv, argc);
        if (argc != 3) {
            std::cerr << "Usage: " << args[0]
                      << " <initialBoardFileRelativeToBinary> <delayMilliseconds>\n";
            return 1;
        }

        const auto initialBoardFile = std::filesystem::canonical(args[0]).parent_path() / args[1];
        const auto delayMilliseconds = std::atoi(args[2]);

        auto gameOfLife = GameOfLife(initialBoardFile, delayMilliseconds);
        gameOfLife.runSimulation();
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
}