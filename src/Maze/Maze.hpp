#pragma once

#include <vector>
#include <mutex>
#include <thread>   // for sleep_for


// ANSI escape codes
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

using namespace std;

class Maze {
public:
    Maze() {}
    virtual ~Maze() = default;
    virtual std::vector<std::vector<int>>& getMaze() = 0;
    virtual void updateMaze(std::vector<int>& prevCord, std::vector<int>& newCord, int id) = 0;
    virtual void lockPath(std::vector<std::pair<int,int>>& path) = 0;
    virtual void unlockPath(std::pair<int,int> coord) = 0;
    virtual void showGrid() = 0;
    virtual void setGrid(vector<int>& coord) = 0;
    virtual std::pair<int,int> getMazeSize() = 0;
};

class OpenMaze : public Maze {
private:
    int n,m;
    std::vector<std::vector<int>> maze;
    std::mutex mtx;  // protect updates
public:
    OpenMaze(int n, int m): n(n), m(m) {
        maze = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));
    }

    std::vector<std::vector<int>>& getMaze() override {
        return maze;
    }

    void updateMaze(std::vector<int>& prevCord, std::vector<int>& newCord, int id) override {
        int prevX = prevCord[0];
        int prevY = prevCord[1];
        // TODO: must unlock this coordinate by calling unlock path (using prev coord)
        int newX = newCord[0];
        int newY = newCord[1];
        std::lock_guard<std::mutex> lock(mtx);
        maze[prevX][prevY] = 0;
        maze[newX][newY] = id;
    }

    void lockPath(std::vector<std::pair<int,int>>& path) override {
        // TODO: lock this path for a unit
    }

    void unlockPath(std::pair<int,int> coord) override {
        // TODO: unlock this coordinate
    }

    void showGrid() override {
        cout<<"-----------------------------------------"<<endl;
        for(int i=0; i<maze.size(); i++) {
            for(int j=0; j<maze[0].size(); j++) {
                if(maze[i][j] == 1) cout << "| " << GREEN << BOLD << maze[i][j] << RESET << " ";
                else if(maze[i][j] != 0) cout << "| " << RED << BOLD << maze[i][j] << RESET << " ";
                else cout<<"| "<< maze[i][j]<<" ";
            }
            cout<<"|"<<endl;
            cout<<"-----------------------------------------"<<endl;
        }
    }

    void setGrid(vector<int>& coord) override {
        maze[coord[0]][coord[1]] = 1;
    }

    std::pair<int,int> getMazeSize() override {
        return make_pair(n,m);
    }
};
