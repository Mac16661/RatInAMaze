Rat in a Maze – Autonomous warehouse robot simulator integrating PathWeaver, a modular pathfinding engine supporting multiple adaptive algorithms for optimized navigation.

mac@OMEN:~/PathWeaver$ g++ -std=c++17 -I./src/Maze -I./src/Unit -I./src/PathWeaver -I./src/CongestionControl -I./src/DeadlockHandling -o RatInAMaze RatInAMaze.cpp -pthread

mac@OMEN:~/PathWeaver$ ./RatInAMaze 