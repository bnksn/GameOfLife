<img src="https://github.com/bnksn/GameOfLife/blob/main/gallery/demo.gif" width="500" height="500">

## How to run

- Download GameOfLife and initialBoard.txt from the releases section.
- Modify initialBoard.txt to your liking. See the "examples" directory for inspiration.
- Run GameOfLife with arguments *pathToInitialBoard* *numIterations* *delayInMs*, i.e. "./GameOfLife initialBoard.txt 100 20". You might need to do "chmod +x GameOfLife" beforehand.

## How to compile

- cd into the root directory.
- "cmake -B ./build -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake".
- "cmake --build ./build/".
