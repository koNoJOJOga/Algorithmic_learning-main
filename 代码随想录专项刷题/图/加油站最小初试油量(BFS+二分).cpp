#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Node { int x, y, fuel; };

int directions[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string dims;
    while(getline(cin, dims)){
        if(dims.empty()) continue;

        for(auto &c : dims) if(c == ',') c = ' ';
        int m, n;
        stringstream ss(dims);
        ss >> m >> n;

        vector<vector<int>> grid(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i){
            string line;
            getline(cin, line);
            if(line.empty()){ --i; continue; }
            for(auto &c : line) if(c == ',') c = ' ';
            stringstream ls(line);
            for (int j = 0; j < n; ++j) ls >> grid[i][j];
        }

        if(grid[0][0] == 0 || grid[m-1][n-1] == 0){ cout << -1 << "\n"; continue; }

        int ansFuel = -1;
        bool found = false;
        int lower = (grid[0][0] == -1 ? 0 : grid[0][0]);
        for (int init = lower; init <= 100; ++init){
            vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(101, false)));
            queue<Node> q; int startFuel;
            if(grid[0][0] == -1) startFuel = 100;
            else startFuel = init - grid[0][0];  
            if(startFuel < 0) continue;
            visited[0][0][startFuel] = true;
            q.push({0, 0, startFuel});
            
            bool reached = false;
            while(!q.empty()){
                Node cur = q.front();
                q.pop();
                if(cur.x == m - 1 && cur.y == n - 1){ reached = true; break; }
                for (int d = 0; d < 4; ++d){
                    int nx = cur.x + directions[d][0];
                    int ny = cur.y + directions[d][1];
                    if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
                    if(grid[nx][ny] == 0) continue;
                    int nf;
                    if(grid[nx][ny] == -1) nf = 100;   
                    else nf = cur.fuel - grid[nx][ny];
                    if(nf < 0) continue;
                    if(nf > 100) nf = 100; // 油箱容量上限
                    if(!visited[nx][ny][nf]){
                        visited[nx][ny][nf] = true;
                        q.push({nx, ny, nf});
                    }
                }
            }
            if(reached){ ansFuel = init; found = true; break; }
        }
        cout << ansFuel << "\n";
    }
    return 0;
}
