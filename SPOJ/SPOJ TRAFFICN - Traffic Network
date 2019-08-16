// SPOJ TRAFFICN - Traffic Network
// topic: graphs, shortest paths, dijkstra
// Author: Khaled Farhat
//
// main idea:
//     1. run dijkstra to find the distance between node (s) and any node
//     2. run dijkstra to find the distance between and node and node (d)
//     3. using bruteforce, try to take each edge from the proposed list and choose the minimum cost

#include <bits/stdc++.h>
using namespace std;


#define     F       first
#define     S       second

typedef pair<int, int>  pi;



const int OO=1e9;
int n, dist[2][10009];
bool vis[10009];
vector<pi> adj[2][10009];



void dijkstra(int src, int id)
{
    for (int i=0; i<=n; i++)
        vis[i]=0;

        priority_queue<pi> pq;
        pq.push({0, src});
        dist[id][src]=0;

        while (!pq.empty())
        {
            int cur=pq.top().S;
            pq.pop();


            if (vis[cur])
                continue;

            vis[cur]=1;


            for (int i=0; i<adj[id][cur].size(); i++)
            {
                int child=adj[id][cur][i].F,
                    edge=adj[id][cur][i].S,
                    can=dist[id][cur]+edge;

                if (can<dist[id][child])
                {
                    dist[id][child]=can;
                    pq.push({-can, child});
                }
            }
        }
}

void initialize()
{
    for (int i=0; i<=n; i++)
        dist[0][i]=dist[1][i]=OO, adj[0][i].clear(), adj[1][i].clear();
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int m, k, s, d;
        cin >> n >> m >> k >> s >> d;

        initialize();

        for (int i=0; i<m; i++)
        {
            int x, y, w;
            cin >> x >> y >> w;

            adj[0][x].push_back({y, w});
            adj[1][y].push_back({x, w});
        }

        dijkstra(s, 0);
        dijkstra(d, 1);

        // brute force
        int ans=dist[0][d];
        for (int i=0; i<k; i++)
        {
            int x, y, w;
            cin >> x >> y >> w;

            ans=min(ans, dist[0][x]+w+dist[1][y]); // s -> x -> y -> d
            ans=min(ans, dist[0][y]+w+dist[1][x]); // s -> y -> x -> d
        }

        if (ans==OO)        cout << -1 << "\n";
        else                cout << ans << "\n";
    }

    return 0;
}
