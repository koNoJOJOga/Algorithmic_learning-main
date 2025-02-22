# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

struct Edge {
    int l, r, val;
};

int n = 10001;
vector<int> father(n, -1);

void init () {
    for (int i = 0; i < n; ++ i )
        father[i] = i;
    return ;
}

int find (int u) {
    return u == father[u] ? u : father[u] = find(father[u]);
}

void merge (int u, int v) {
    v = find(v);
    u = find(u);
    if (u == v) return ;
    father[v] = u;
    return ;
}

int main () {
    int v, e, v1, v2, val;
    vector<Edge> edges;
    int result_val = 0;
    cin >> v >> e;
    while (e -- ) {
        cin >> v1 >> v2 >> val;
        edges.push_back({v1, v2, val});
    }

    // kruskal
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.val < b.val;
    });

    init();

    for (Edge edge : edges) {
        int x = find(edge.l);
        int y = find(edge.r);

        if (x != y) {
            result_val += edge.val;
            merge(x, y);
        }
    }
    cout << result_val << endl;
    return 0;
}