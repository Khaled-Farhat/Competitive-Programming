// Problem: UVA 11792 - Krochanska is Here!
// Tags: Graphs, SSSP, BFS
// Author: Khaled Farhat
// Solution idea:
//      - since the number of important cities is small, we can do a bruteforce over them, and find the average of the
//        shortest paths to other important cities using Breadth First Search algorithm (BFS)
//      - we want to find the average of the minimum shortest paths and it equals ((sum of shortest paths) / (number of important nodes))
//      - since the number of important nodes is same for all nodes, we can just minimize over the sum of shortest paths
//
// Time complexity: O(k * (V + E)) where k is the number of important nodes
//
// Breadth First Search: https://en.wikipedia.org/wiki/Breadth-first_search

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

int bfs(int startNode) {
    for (int i=1; i<=n; ++i) {
        vis[i]=0;
    }

    queue<int> q;
    q.push(startNode);
    dist[startNode]=0;
    vis[startNode]=1;

    while (!q.empty()) {
        int curNode=q.front();
        q.pop();

        for (int i=0; i<adj[curNode].size(); ++i) {
            int child=adj[curNode][i];

            if (!vis[child]) {
                vis[child]=1;
                dist[child]=dist[curNode]+1;
                q.push(child);
            }
        }
    }

    int distSum=0;
    for (int i=1; i<=n; ++i) {
        if (freq[i]>=2) {
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
                int sum=bfs(i);

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
