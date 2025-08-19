#include <bits/stdc++.h>
#include <thread>   // for sleep_for
#include <chrono>   // for seconds
#include <cstdlib>  // for system()

#include "Maze.hpp"
#include "Unit.hpp"

using namespace std;

atomic<bool> keepRunning(true);

// TODO: Should print the maze in 1/30 freq
void printLoop(Maze* openMaze) {
    while (keepRunning) {
        system("clear");  
        openMaze->showGrid();
        std::this_thread::sleep_for(std::chrono::milliseconds(33)); 
    }
}

int main() {
    Maze* openMaze = new OpenMaze(10, 10);

    std::thread worker(printLoop, openMaze);  

    vector<vector<int>> tasks = {{0,3}, {1,7}, {0,8}, {2,1}};
    for(auto task: tasks) openMaze->setGrid(task);
    
    // creating robot units
    Unitv1 a1 = Unitv1(openMaze, 5, "");
    a1.runBot(tasks);
    
    keepRunning = false;
    worker.join();   // wait for it to exit

    delete openMaze;
    openMaze == nullptr;
    return 0;
}
