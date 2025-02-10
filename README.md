<img src="https://github.com/bnksn/GameOfLife/blob/main/gallery/demo.gif" width="500" height="500">

## How to run

- cd into the root directory
- "cmake -B ./build -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
- "cmake --build ./build/"
- "./build/GameOfLife ../initialBoard.txt _numIterations_ _delayInMs_"
