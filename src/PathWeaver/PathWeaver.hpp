#pragma once

#include <vector>
#include <utility> 


class PathFinder{
    public:
        virtual void findPath(std::vector<int>& currPos, std::vector<int>& goal, std::vector<std::pair<int, int>>& plannedPath, std::vector<std::vector<int>>& maze)=0;
        virtual ~PathFinder() {};
};

class Loop: public PathFinder {
    public:
        void findPath(std::vector<int>& currPos, std::vector<int>& goal, std::vector<std::pair<int, int>>& plannedPath, std::vector<std::vector<int>>& maze) override {
            
            int x = currPos[0];
            int y = currPos[1];
            int gx = goal[0];
            int gy = goal[1];

            // First, move along rows (x direction)
            if (x <= gx) {
                for (int i = x; i <= gx; i++) {
                    plannedPath.push_back({i, y});
                }
            } else {
                for (int i = x; i >= gx; i--) {
                    plannedPath.push_back({i, y});
                }
            }

            // Then, move along columns (y direction)
            if (y <= gy) {
                for (int j = y + 1; j <= gy; j++) { // start from y+1 (already added y)
                    plannedPath.push_back({gx, j});
                }
            } else {
                for (int j = y - 1; j >= gy; j--) {
                    plannedPath.push_back({gx, j});
                }
            }
        }

        ~Loop() override = default;
};

class BFS: public PathFinder {
    public:
        void findPath(std::vector<int>& currPos, std::vector<int>& goal, std::vector<std::pair<int, int>>& plannedPath, std::vector<std::vector<int>>& maze) override {
            
        }

        ~BFS() override = default;
};

class DFS: public PathFinder {
    public:
        void findPath(std::vector<int>& currPos, std::vector<int>& goal, std::vector<std::pair<int, int>>& plannedPath, std::vector<std::vector<int>>& maze) override {

        }

        ~DFS() override = default;
};

class PathWeaver{
    unique_ptr<PathFinder> strategy;

    public:
        PathWeaver() = default;

        void setStrategy(unique_ptr<PathFinder> s) {
            strategy = std::move(s);
        }

        void findPath(std::vector<int>& currPos, std::vector<int>& goal, std::vector<std::pair<int, int>>& plannedPath, std::vector<std::vector<int>>& maze) {
            if (strategy)
                strategy->findPath(currPos, goal, plannedPath, maze);
            else
                cout << "No algo specified to PathWeaver Engine" << endl;
        }
};