#include <fstream>
#include <string>

#include "../src/gameOfLife.hpp"
#include "gtest/gtest.h"

namespace TestHelpers {
std::filesystem::path createTempFile(const std::string& initialBoard) {
    const auto tempFile = std::filesystem::temp_directory_path() / "test_board.txt";
    std::ofstream(tempFile) << initialBoard;

    return tempFile;
}
}  // namespace TestHelpers

class GameOfLifeTestFixture : public ::testing::Test {
   protected:
    void TearDown() override {
        if (std::filesystem::exists(_tempFile)) {
            std::filesystem::remove(_tempFile);
        }
    }

    std::filesystem::path _tempFile;
};

TEST_F(GameOfLifeTestFixture, RunSimulation_Wrap_Stuck) {
    const auto initialBoard = "# _ # \n_ _ _ \n# _ # \n";  // Wrapping logic means this won't evolve
    _tempFile = TestHelpers::createTempFile(initialBoard);

    auto gameOfLife = GameOfLife(10);
    gameOfLife.readInitialBoard(_tempFile);
    gameOfLife.runSimulation(2);

    const auto expectedBoard = "# _ # \n_ _ _ \n# _ # \n";

    EXPECT_EQ(gameOfLife.getBoardAsString(), expectedBoard);
}

TEST_F(GameOfLifeTestFixture, RunSimulation_EmptyBoard) {
    const auto initialBoard = "_ _ _ \n_ _ _ \n_ _ _ \n";
    _tempFile = TestHelpers::createTempFile(initialBoard);

    auto gameOfLife = GameOfLife(10);
    gameOfLife.readInitialBoard(_tempFile);
    gameOfLife.runSimulation(5);

    const auto expectedBoard = "_ _ _ \n_ _ _ \n_ _ _ \n";

    EXPECT_EQ(gameOfLife.getBoardAsString(), expectedBoard);
}

TEST_F(GameOfLifeTestFixture, RunSimulation_ZeroIterations) {
    const auto initialBoard = "# # _ \n_ _ # \n# # # \n";
    _tempFile = TestHelpers::createTempFile(initialBoard);

    auto gameOfLife = GameOfLife(10);
    gameOfLife.readInitialBoard(_tempFile);
    gameOfLife.runSimulation(0);

    const auto expectedBoard = "# # _ \n_ _ # \n# # # \n";

    EXPECT_EQ(gameOfLife.getBoardAsString(), expectedBoard);
}

TEST_F(GameOfLifeTestFixture, BlinkerPattern) {
    const auto initialBoard = "_ _ _ _ \n_ # # # \n_ _ _ _ \n_ _ _ _ \n";
    _tempFile = TestHelpers::createTempFile(initialBoard);

    auto gameOfLife = GameOfLife(10);
    gameOfLife.readInitialBoard(_tempFile);
    gameOfLife.runSimulation(2);

    const auto expectedBoard = "_ _ _ _ \n_ # # # \n_ _ _ _ \n_ _ _ _ \n";

    EXPECT_EQ(gameOfLife.getBoardAsString(), expectedBoard);
}

TEST(GameOfLifeTest, RunSimulation_InvalidFile) {
    const auto invalidFile = std::filesystem::path("nonexistent_file.txt");

    ASSERT_THROW(GameOfLife(10).readInitialBoard(invalidFile), std::runtime_error);
}