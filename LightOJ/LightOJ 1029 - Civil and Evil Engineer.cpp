// Problem: LightOJ 1029 - Civil and Evil Engineer
// Tags: Graphs, MST, Kruskal
// Author: Khaled Farhat
// Solution idea:
//      1. Build the Minimum Spanning Tree, let sum_min equals the sum of its edges.
//      2. Build the Maximum Spanning Tree, let sum_max equals the sum of its edges.
//      3. The average now is ( sum_min +sum_max ) / 2
//
// Kruskal algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm

#include <bits/stdc++.h>
using namespace std;


#define     F       first
#define     S       second

typedef pair<int, int>  pi;



int n, par[109], r[109];
vector< pair<int, pi> > edges;



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
    for (int i=0; i<=n; i++)
        par[i]=i, r[i]=1;
}

int main()
{
    int t;
    scanf("%d", &t);
    for (int id=1; id<=t; id++)
    {
        int m;
        cin >> n;

        initialize();

        int x, y, w;
        do
        {
            cin >> x >> y >> w;
            edges.push_back({w, {x, y}});
        }
        while(x+y+w);

        sort(edges.begin(), edges.end());

        int sum_min=0;
        for (int i=0; i<edges.size(); i++)
        {
            int x=edges[i].S.F,
                y=edges[i].S.S,
                w=edges[i].F;

            if (link(x, y))
                sum_min+=w;
        }

        for (int i=0; i<=n; i++)
            par[i]=i, r[i]=1;

        int sum_max=0;
        for (int i=(int)edges.size()-1; i>=0; i--)
        {
            int x=edges[i].S.F,
                y=edges[i].S.S,
                w=edges[i].F;

            if (link(x, y))
                sum_max+=w;
        }

        printf("Case %d: ", id);

        if ((sum_min+sum_max)%2==0)
            printf("%d\n", (sum_min+sum_max)/2);

        else
            printf("%d/2\n", sum_min+sum_max);
    }

    return 0;
}
