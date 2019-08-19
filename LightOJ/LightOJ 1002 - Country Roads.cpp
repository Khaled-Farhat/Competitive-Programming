// Problem: Light OJ 1002 - Country Roads
// Tags: Graphs, MST, Kruskal
// Author: Khaled Farhat
// Solution idea:
//      1. Build the Minimum Spanning Tree (you can use kruskal or prim).
//      2. You can now find the maximum edge on the path from any node to node (t),
//         you can do this using dfs, bfs, dijkstra...
// 
// Kruskal algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm

#include <bits/stdc++.h>
using namespace std;


#define     F       first
#define     S       second

typedef pair<int, int>  pi;



int n, par[509], r[509], ans[509];
bool vis[509];
vector< pair<int, pi> > edges;
vector< vector<pi> > adj(509);



void dfs(int node, int max_edge)
{
    vis[node]=1;
    ans[node]=max_edge;

    for (int i=0; i<adj[node].size(); i++)
    {
        int child=adj[node][i].F,
            cost=adj[node][i].S;

        if (!vis[child])
            dfs(child, max(cost, max_edge));
    }
}

int findSet(int u)
{
    if (u==par[u])
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
    for (int i=0; i<n; i++)
    {
        adj[i].clear();
        ans[i]=-1;
        par[i]=i;
        vis[i]=0;
        r[i]=1;
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    for (int id=1; id<=t; id++)
    {
        int m;
        cin >> n >> m;

        initialize();

        while (m--)
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

        int t;
        scanf("%d", &t);
        dfs(t, 0);

        printf("Case %d:\n", id);
        for (int i=0; i<n; i++)
        {
            if (ans[i]==-1)     printf("Impossible\n");
            else                printf("%d\n", ans[i]);
        }
    }

    return 0;
}
