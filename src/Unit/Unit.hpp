#pragma once

#include <vector>
#include <utility> 
#include <chrono>   // for seconds

#include "PathWeaver.hpp"

using namespace std;

class Unitv1{
    private:
        int id;
        std::vector<int> prevPos;
        std::vector<int> currPos;
        std::vector<std::pair<int, int>> plannedPath;
        Maze* m; // it is used for move and reserve/lock/book a path
        PathWeaver algo;
    public:
        Unitv1(Maze* mazePtr, int id, const string& algoName): id(id) {
            prevPos = std::vector<int> {-1, -1};
            currPos = std::vector<int> {0, 0};
            m = mazePtr;
            if (algoName == "BFS") {
                algo.setStrategy(make_unique<BFS>());
            } else if (algoName == "DFS") {
                algo.setStrategy(make_unique<DFS>());
            }else{
                algo.setStrategy(make_unique<Loop>());
            }
        }

        void pathFinder(vector<int>& task) {
            // TODO: calls path planning engine sending curr coordinates
            // TODO: call lockPath() to put a mutex lock on planned coordinates

            algo.findPath(currPos, task, plannedPath, m->getMaze());
        }

        void walk() {
            for(auto &[x, y]: plannedPath) {
                prevPos[0] = currPos[0];
                prevPos[1] = currPos[1];
                currPos[0] = x;
                currPos[1] = y;
                // Take 1 second sleep for accurate simulation 
                std::this_thread::sleep_for(std::chrono::seconds(1)); 
                m->updateMaze(prevPos, currPos, id); 
            }
        }

        void runBot(std::vector<std::vector<int>>& tasks) {
            //tasks[0]; // intermidate stop (pick package form this location)
            //tasks[1]; // destination (deliver package to this location)

            for(auto task:tasks){
                while(currPos != task) {
                    pathFinder(task);
                    // for(auto [x,y]: plannedPath) cout<<x<<" "<<y<<endl;
                    walk();
                    plannedPath.clear(); // deletes the planned path
                }
                // cout<<"Unit "<<id<<" reached location successfully"<<endl;
            }
        }
};