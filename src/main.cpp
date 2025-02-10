#include <iostream>

#include "gameOfLife.hpp"

int main(int argc, char* argv[]) {
    try {
        const auto args = std::span(argv, argc);
        if (argc != 4) {
            std::cerr
                << "Usage: " << args[0]
                << " <initialBoardFileRelativeToBinary> <numIterations> <delayMilliseconds>\n";
            return 1;
        }

        const auto initialBoardFile = std::filesystem::canonical(args[0]).parent_path() / args[1];
        const auto numIterations = std::atoi(args[2]);
        const auto delayMilliseconds = std::atoi(args[3]);

        auto gameOfLife = GameOfLife(delayMilliseconds);
        gameOfLife.readInitialBoard(initialBoardFile);
        gameOfLife.runSimulation(numIterations);
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
}