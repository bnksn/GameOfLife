#include <sstream>
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
    const auto initialBoard =
        "#_#\n___\n#_#\n";  // Due to wrapping logic we expect this not to evolve
    _tempFile = TestHelpers::createTempFile(initialBoard);

    auto gameOfLife = GameOfLife(10);
    gameOfLife.readInitialBoard(_tempFile);
    gameOfLife.runSimulation(2);

    const auto expectedBoard = std::vector<std::vector<bool>>{
        {true, false, true}, {false, false, false}, {true, false, true}};

    EXPECT_EQ(gameOfLife.getBoard(), expectedBoard);
}

TEST_F(GameOfLifeTestFixture, RunSimulation_EmptyBoard) {
    const auto initialBoard = "___\n___\n___\n";
    _tempFile = TestHelpers::createTempFile(initialBoard);

    auto gameOfLife = GameOfLife(10);
    gameOfLife.readInitialBoard(_tempFile);
    gameOfLife.runSimulation(5);

    const auto expectedBoard = std::vector<std::vector<bool>>{
        {false, false, false}, {false, false, false}, {false, false, false}};

    EXPECT_EQ(gameOfLife.getBoard(), expectedBoard);
}

TEST_F(GameOfLifeTestFixture, RunSimulation_ZeroIterations) {
    const auto initialBoard = "##_\n__#\n###\n";
    _tempFile = TestHelpers::createTempFile(initialBoard);

    auto gameOfLife = GameOfLife(10);
    gameOfLife.readInitialBoard(_tempFile);
    gameOfLife.runSimulation(0);

    const auto expectedBoard = std::vector<std::vector<bool>>{
        {true, true, false}, {false, false, true}, {true, true, true}};

    EXPECT_EQ(gameOfLife.getBoard(), expectedBoard);
}

TEST_F(GameOfLifeTestFixture, BlinkerPattern) {
    const auto initialBoard = "____\n_###\n____\n____\n";
    _tempFile = TestHelpers::createTempFile(initialBoard);

    auto gameOfLife = GameOfLife(10);
    gameOfLife.readInitialBoard(_tempFile);
    gameOfLife.runSimulation(2);

    const auto expectedBoard = std::vector<std::vector<bool>>{{false, false, false, false},
                                                              {false, true, true, true},
                                                              {false, false, false, false},
                                                              {false, false, false, false}};

    EXPECT_EQ(gameOfLife.getBoard(), expectedBoard);
}

TEST(GameOfLifeTest, RunSimulation_InvalidFile) {
    const auto invalidFile = std::filesystem::path("nonexistent_file.txt");

    ASSERT_THROW(GameOfLife(10).readInitialBoard(invalidFile), std::runtime_error);
}