#pragma once

#include <vector>
#include <utility> 
#include <queue>


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
        void findPath(std::vector<int>& currPos, std::vector<int>& goal, std::vector<std::pair<int, int>>& plannedPath,
              std::vector<std::vector<int>>& maze) override {

            int srcRow = currPos[0], srcCol = currPos[1];
            int distRow = goal[0], distCol = goal[1];
            int n = maze.size(), m = maze[0].size();

            std::vector<std::pair<int, int>> dirs = { // Delebritely pushing diagonals in top to explore diagonals first
                {-1, -1}, {-1, 1},
                {1, -1},  {1, 1},
                {-1, 0}, {0, -1}, {0, 1}, {1, 0}
            };

            std::queue<std::array<int, 3>> q;
            q.push({srcRow, srcCol, 0});

            std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
            visited[srcRow][srcCol] = true;

            // parent map to reconstruct path
            std::map<std::pair<int,int>, std::pair<int,int>> parent;

            while(!q.empty()) {
                auto node = q.front();
                q.pop();

                int r = node[0], c = node[1], dist = node[2];

                if (r == distRow && c == distCol) {
                    // reconstruct path
                    std::vector<std::pair<int,int>> path;
                    std::pair<int,int> curr = {distRow, distCol};
                    while (curr != std::make_pair(srcRow, srcCol)) {
                        path.push_back(curr);
                        curr = parent[curr];
                    }
                    path.push_back({srcRow, srcCol});
                    std::reverse(path.begin(), path.end());
                    plannedPath = path;
                    return;
                }

                for (auto [dr, dc] : dirs) {
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                        !visited[nr][nc] && maze[nr][nc] != -1) {

                        visited[nr][nc] = true;
                        parent[{nr, nc}] = {r, c};
                        q.push({nr, nc, dist + 1});
                    }
                }
            }
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