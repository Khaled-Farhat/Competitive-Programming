// Problem: UVA 11792 - Krochanska is Here!
// Tags: Graphs, SSSP, Dijkstra
// Author: Khaled Farhat
// Solution idea:
//      - since the number of important cities is small, we can do a bruteforce over them, and find the average of the
//        shortest paths to other important cities using Dijkstra algorithm.
//      - we want to find the average of the minimum shortest paths and it equals ((sum of shortest paths) / (number of important nodes))
//      - since the number of important nodes is same for all nodes, we can just minimize over the sum of shortest paths
//
// Time complexity: O(k * (V + E) * log(V)) where k is the number of important nodes
//
// Dijkstra algorithm: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

#include <bits/stdc++.h>
using namespace std;

#define     F       first
#define     S       second
typedef pair<int, int>  pi;

const int MAX=1e5+9;
const int OO=1e9+9;
int n, m, dist[MAX], freq[MAX];
vector<int> adj[MAX];
bool vis[MAX];

void initializeDist() {
    for (int i=1; i<=n; ++i) {
        dist[i]=OO;
        vis[i]=0;
    }
}

int dijkstra(int startNode) {
    initializeDist();
    priority_queue<pi> pq;
    pq.push({0, startNode});
    dist[startNode]=0;

    while (!pq.empty()) {
        int curNode=pq.top().S;
        pq.pop();

        if (vis[curNode]) {
            continue;
        }

        vis[curNode]=1;
        for (int i=0; i<adj[curNode].size(); ++i) {
            int child=adj[curNode][i];
            if (dist[curNode]+1<dist[child]) {
                dist[child]=dist[curNode]+1;
                pq.push({-dist[child], child});
            }
        }
    }

    int distSum=0;
    for (int i=1; i<=n; ++i) {
        if (freq[i]>=2) { // if i is an important city
            distSum+=dist[i];
        }
    }

    return distSum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i=1; i<=n; ++i) {
            adj[i].clear();
            freq[i]=0;
        }

        while (m--) {
            int x, y;
            cin >> x >> y;
            ++freq[x];

            while (y) {
                adj[x].push_back(y);
                adj[y].push_back(x);
                ++freq[y];

                x=y;
                cin >> y;
            }
        }

        int minSum=OO, ans=1;
        for (int i=1; i<=n; ++i) {
            if (freq[i]>=2) { // if i is an important node
                int sum=dijkstra(i);

                if (sum<minSum) {
                    minSum=sum;
                    ans=i;
                }
            }
        }

        cout << "Krochanska is in: " << ans << "\n";
    }

    return 0;
}
