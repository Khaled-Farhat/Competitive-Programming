// Problem: UVA 10842 - Traffic Flow
// Tags: MST, Kruskal
// Author: Khaled Farhat
// Main idea:
//      - We need to link all nodes in such that the minimum edge in maximum possible
//      - To do this, we should find the Maximum Spanning Tree, and print the minimum edge in it

#include <bits/stdc++.h>
using namespace std;


#define     F       first
#define     S       second

typedef pair<int, int>  pi;



int n, par[109], r[109];
vector< pair<int, pi> > edges;



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

bool cmp(const pair<int, pi> &p1, const pair<int, pi> &p2)
{
    return p1.F>p2.F;
}

void initialize()
{
    edges.clear();

    for (int i=0; i<=n; i++)
        par[i]=i, r[i]=1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
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

        sort(edges.begin(), edges.end(), cmp);

        int ans=-1;
        for (int i=0; i<edges.size(); i++)
        {
            int x=edges[i].S.F,
                y=edges[i].S.S,
                w=edges[i].F;

            if (link(x, y))
                ans=w;
        }

        cout << "Case #" << id << ": " << ans << "\n";
    }

    return 0;
}
