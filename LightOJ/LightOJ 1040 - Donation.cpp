// Problem: LightOJ 1040 - Donation
// Tags: Graphs, MST, Kruskal
// Author: Khaled Farhat
// Solution idea:
//      - Build MST and count the number of forests
//      - if the number of forests at end is not equals 1, then the graph is not a tree so print -1
//      - else the graph is tree, print the sum of edges that is not included int MST
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
    for (int i=0; i<n; i++)
        par[i]=i, r[i]=1;
}

int main()
{
    int t;
    scanf("%d", &t);
    for (int id=1; id<=t; id++)
    {
        cin >> n;

        initialize();

        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
            {
                int w;
                cin >> w;

                if (w)
                    edges.push_back({w, {i, j}});
            }

        sort(edges.begin(), edges.end());

        int forests=n,
            ans=0;
        for (int i=0; i<edges.size(); i++)
        {
            int x=edges[i].S.F,
                y=edges[i].S.S,
                w=edges[i].F;

            if (link(x, y))         forests--;
            else                    ans+=w;
        }

        if (forests!=1)
            ans=-1;

        printf("Case %d: %d\n", id, ans);
    }

    return 0;
}
