## To Do

- gif

## How to run

- cd into the root directory
- "cmake -B ./build -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
- "cmake --build ./build/"
- "./build/GameOfLife ../initialBoard.txt _numIterations_ _delayInMs_"
