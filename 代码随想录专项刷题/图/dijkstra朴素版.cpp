# include <iostream>
# include <vector>
# include <climits>
using namespace std;

int main () {
    int n, m, s, e, v;
    cin >> n >> m;
    vector<vector<int>> grid(n + 1, vector<int>(n + 1, INT_MAX));
    for (int i = 0; i < m; ++ i ) {
        cin >> s >> e >> v;
        grid[s][e] = v;
    }
    
    int start = 1;
    int end = n;
    
    vector<int> minDist(n + 1, INT_MAX);
    vector<bool> visited(n + 1, false);
    
    minDist[start] = 0;
    
    for (int i = 1; i <= n; ++ i ) {
        int minVal = INT_MAX;
        int cur = 1;
        
        for (int j = 1; j <= n; ++ j ) {
            if (!visited[j] && minDist[j] < minVal) {
                minVal = minDist[j];
                cur = j;
            }
        }
        
        visited[cur] = true;
        
        for (int j = 1; j <= n; ++ j ) 
            if (!visited[j] && grid[cur][j] != INT_MAX && minDist[cur] + grid[cur][j] < minDist[j])
                minDist[j] = minDist[cur] + grid[cur][j];
    }
    if (minDist[end] == INT_MAX)
        cout << -1 << endl;
    else 
        cout << minDist[end] << endl;
    return 0;
}