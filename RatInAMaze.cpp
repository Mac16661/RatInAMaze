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

void runBot(vector<vector<int>>& tasks, Maze* openMaze, int id) {
    // creating robot units
    Unitv1 a1 = Unitv1(openMaze, id, "");
    a1.runBot(tasks);
}

int main() {
    Maze* openMaze = new OpenMaze(10, 50);

    std::thread worker(printLoop, openMaze);  

    vector<vector<int>> tasks1 = {{0,3}, {1,7}, {0,8}, {2,1}};
    for(auto task: tasks1) openMaze->setGrid(task);

    vector<vector<int>> tasks2 = {{1,3}, {2,8}, {8,8}, {5,1}};
    for(auto task: tasks2) openMaze->setGrid(task);
    
    std::thread u1(runBot, ref(tasks1), openMaze, 9);
    std::thread u2(runBot, ref(tasks2), openMaze, 8);
    u2.join();
    u1.join();

    std::this_thread::sleep_for(std::chrono::seconds(3)); 
    keepRunning = false;
    worker.join();   // wait for it to exit

    delete openMaze;
    openMaze == nullptr;
    return 0;
}
