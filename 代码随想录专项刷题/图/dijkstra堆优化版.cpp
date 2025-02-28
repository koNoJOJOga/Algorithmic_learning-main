# include <iostream>
# include <vector>
# include <queue>
# include <climits>
# include <list>
using namespace std;
using P = pair<int, int>;

class mycomparison {
public:
    bool operator() (const P& lhs, const P& rhs) const {
        return lhs.second > rhs.second;
    }
};

struct Edge {
    int to, val;
    Edge(int t, int w) : to(t), val(w) {}
};

int main () {
    int n, m, p1, p2, val;
    cin >> n >> m;
    vector<list<Edge>> adj(n + 1);
    for (int i = 0; i < m; ++ i ) {
        cin >> p1 >> p2 >> val;
        adj[p1].push_back(Edge(p2, val));
    }

    int start = 1;
    int end = n;
    vector<int> minDist(n + 1, INT_MAX);
    vector<bool> visited(n + 1, false);
    priority_queue<P, vector<P>, mycomparison> pq;  // 这句话的原理是优先队列默认是大根堆，所以我们要自定义比较函数，使其变成小根堆
    pq.push(P(start, 0));
    minDist[start] = 0;
    while (!pq.empty()) {
        P cur = pq.top();
        pq.pop();
        if (visited[cur.first]) continue;
        visited[cur.first] = true;
        for (Edge edge : adj[cur.first]) {
            if (!visited[edge.to] && minDist[cur.first] + edge.val < minDist[edge.to]) {
                minDist[edge.to] = minDist[cur.first] + edge.val;
                pq.push(P(edge.to, minDist[edge.to]));
            }
        }
    }
    if (minDist[end] == INT_MAX)
        cout << -1 << endl;
    else 
        cout << minDist[end] << endl;
    return 0;
}