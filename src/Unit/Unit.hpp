#pragma once

#include <vector>
#include <utility> 

using namespace std;

class Unit{
    private:
        int id;
        std::vector<int> prevPos;
        std::vector<int> currPos;
        std::vector<std::pair<int, int>> plannedPath;
        Maze* m; // it is used for move and reserve/lock/book a path
    public:
        Unit(Maze* mazePtr, int id): id(id) {
            prevPos = std::vector<int> {-1, -1};
            currPos = std::vector<int> {0, 0};
            m = mazePtr;
        }

        void pathFinder(vector<int>& task) {
            // TODO: calls path planning engine sending curr coordinates
            // TODO: call lockPath() to put a mutex lock on planned coordinates

            //dymmy path ->
            for(int i=0; i<m->getMazeSize().first; i++) {
                for(int j=0; j<m->getMazeSize().second; j++) {
                    plannedPath.push_back({i, j});
                    if(i==task[0] && j==task[1]) {
                        return;
                    }
                }
            }

        }

        void walk() {
            for(auto &[x, y]: plannedPath) {
                prevPos[0] = currPos[0];
                prevPos[1] = currPos[1];
                currPos[0] = x;
                currPos[1] = y;
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
                cout<<"Unit "<<id<<" reached location successfully"<<endl;
            }
            


            // while(currPos != tasks[1]) {
            //     pathFinder(tasks[1]);
            //     walk();
            //     // for(auto [x,y]: plannedPath) cout<<x<<" "<<y<<endl;
            //     plannedPath.clear(); // deletes the planned path
            // }

            // cout<<"Unit "<<id<<" package delivered successfully"<<"  ==============================================  "<<endl;

        }
};