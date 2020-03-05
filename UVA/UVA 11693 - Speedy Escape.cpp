// Problem: UVA 11693 - Speedy Escape
// Tags: Graphs, SSSP, Dijkstra
// Author: Khaled Farhat
// Solution idea:
//      - Binary search over the speed, to check that a speed is valid we run Dijkstra's algorithm from b but
//        with small modification in the relaxation, we will not visit a city if it was visited by the police car before.
//
// Time Complexity: log(k) * (E + V) * log(V) where k is the range of the binary search
//
// Dijkstra's algorithm: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

#include <bits/stdc++.h>
using namespace std;

const int MAX=109;
const double OO=1e9;
int n, m, e, p, b, dist[MAX][2];
bool vis[MAX];
vector< pair<int, int> > adj[MAX];
vector<int> can;

void dijkstra(int startNode, int id, bool checkForSpeed=0, double speed=-1) {
    for (int i=1; i<=n; ++i) {
        dist[i][id]=OO;
        vis[i]=0;
    }

    priority_queue< pair<int, int> > pq;
    pq.push({0, startNode});
    dist[startNode][id]=0;

    while (!pq.empty()) {
        int cur=pq.top().second;
        pq.pop();

        if (vis[cur]) {
            continue;
        }

        vis[cur]=1;
        for (int i=0; i<adj[cur].size(); ++i) {
            int child=adj[cur][i].first,
                cost=adj[cur][i].second;

            if (dist[cur][id]+cost<dist[child][id]) {
                if (checkForSpeed && (double)(dist[cur][id]+cost)/speed>dist[child][1-id]/160.0) {
                    continue; // if police car has reached this city before
                }

                dist[child][id]=dist[cur][id]+cost;
                pq.push({-dist[child][id], child});
            }
        }
    }
}

bool check(double speed) {
    dijkstra(b, 1, 1, speed);
    for (int i=0; i<e; ++i) {
        if (dist[can[i]][1]!=OO && (double)dist[can[i]][1]/speed<(double)dist[can[i]][0]/160.0) {
            return 1;
        }
    }

    return 0;
}

void BSFind(double low, double high) {
    for (int i=0; i<200; ++i) {
        double mid=(low+high)/2.0;

        if (check(mid)) {
            high=mid;
        }
        else {
            low=mid;
        }
    }

    if (check(high)) {
        cout << fixed << setprecision(7) << high << "\n";
    }
    else {
        cout << "IMPOSSIBLE\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> e;
        for (int i=1; i<=n; ++i) {
            adj[i].clear();
        }

        for (int i=0; i<m; ++i) {
            int x, y, l;
            cin >> x >> y >> l;
            adj[x].push_back({y, l});
            adj[y].push_back({x, l});
        }

        can.clear();
        for (int i=0; i<e; ++i) {
            int x;
            cin >> x;
            can.push_back(x);
        }

        cin >> b >> p;
        dijkstra(p, 0);
        dijkstra(b, 1);
        BSFind(0, 1e15+9);
    }

    return 0;
}
