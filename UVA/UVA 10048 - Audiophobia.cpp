// Problem: UVA 10048 - Audiophobia
// Tags: Graphs, MST, Kruskal
// Author: Khaled Farhat
// Solution idea:
//      1. Build the Minimum Spanning Tree (you can use kruskal or prim).
//      2. Find minimum maximum edge between any two nodes, is the maximum edge on the path between theese nodes in the MST,
//         you can use dfs, bfs, dijkstra, floyd, bellman ford or any shortest path algorithm to find the maximum minimum edge.
// 
// Kruskal algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm

#include <bits/stdc++.h>
using namespace std;

#define     F       first
#define     S       second

typedef pair<int, int>  pi;



const int OO=1e9;
int c, par[109], r[109], dist[109];
bool vis[109];
vector< pair<int, pi> > edges;
vector< vector<pi> > adj(109);



int dijkstra(int s, int d)
{
    for (int i=0; i<=c; i++)
        vis[i]=0, dist[i]=OO;

    dist[s]=0;
    priority_queue< pair<int, pi> > pq;
    pq.push({0, {s, -1}});

    while (!pq.empty())
    {
        int cur=pq.top().S.F,
            mx=pq.top().S.S;
        pq.pop();

        if (cur==d)
            return mx;

        if (vis[cur])
            continue;

        vis[cur]=1;

        for (int i=0; i<adj[cur].size(); i++)
        {
            int child=adj[cur][i].F,
                cost=adj[cur][i].S,
                can=dist[cur]+cost;

            if (can<dist[child])
            {
                dist[child]=can;
                pq.push({-can, {child, max(mx, cost)}});
            }
        }
    }

    return -1;
}

int findSet(int u)
{
    if (par[u]==u)
        return u;

    return par[u]=findSet(par[u]);
}

bool link(int u, int v)
{
    int parU=findSet(u),
        parV=findSet(v);

    if (parU==parV)
        return 0;

    if (r[parU]>r[parV])        swap(parU, parV);
    else if (r[parU]==r[parV])  r[parV]++;

    par[parU]=parV;

    return 1;
}
void initialize()
{
    edges.clear();

    for (int i=0; i<=c; i++)
        par[i]=i, r[i]=1, adj[i].clear();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t=0, s, q;
    while (cin >> c >> s >> q  &&  (c+s+q))
    {        
        if (t)
            cout << "\n";
        
        initialize();

        while (s--)
        {
            int x, y, w;
            cin >> x >> y >> w;

            edges.push_back({w, {x, y}});
        }

        sort(edges.begin(), edges.end());

        for (int i=0; i<edges.size(); i++)
        {
            int x=edges[i].S.F,
                y=edges[i].S.S,
                w=edges[i].F;

            if (link(x, y))
            {
                adj[x].push_back({y, w});
                adj[y].push_back({x, w});
            }
        }

        cout << "Case #" << ++t << "\n";

        while (q--)
        {
            int from, to;
            cin >> from >> to;

            int ans=dijkstra(from, to);

            if (ans==-1)        cout << "no path\n";
            else                cout << ans << "\n";
        }
    }

    return 0;
}
