# include <iostream>
# include <vector>
# include <list>
# include <queue>
# include <climits>
using namespace std;
using P = pair<int, int>;

// 小根堆
class mycomparison {
    public:
        bool operator() (const P& lhs, const P& rhs) {
            return lhs.second > rhs.second;
        }
};

// 带权重的边
struct Edge {
    int to, val;

    Edge(int t, int w): to(t), val(w) {}
};

int main () {
    int n, m, p1, p2, val;
    cin >> n >> m;
    vector<list<Edge>> grid(n + 1);
    for (int i = 0; i < m; ++ i) {
        cin >> p1 >> p2 >> val;
        grid[p1].push_back(Edge(p2, val));
    }

    int start = 1;
    int end = n;

    vector<int> minDist(n + 1, INT_MAX);
    vector<bool> visited(n + 1, false);
    priority_queue<P, vector<P>, mycomparison> pq;

    pq.push(P(start, 0));
    minDist[start] = 0;

    while (!pq.empty()) {
        P cur = pq.top();
        pq.pop();
        if (visited[cur.first]) continue;
        visited[cur.first] = true;

        for (Edge edge : grid[cur.first]) {
            if (!visited[edge.to] && minDist[cur.first] + edge.val < minDist[edge.to]) {
                minDist[edge.to] = minDist[cur.first] + edge.val;
                pq.push(P(edge.to, minDist[edge.to]));
            }
        }
    }
    if (minDist[end] == INT_MAX) cout << -1 << endl;
    else cout << minDist[end] << endl;
    return 0;
}