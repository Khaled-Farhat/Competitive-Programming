// Problem: LightOJ 1041 - Road Construction
// Tags: Graphs, MST, Kruskal
// Author: Khaled Farhat
// Solution idea:
//      1. We will build the Minimum Spanning Tree, first we will include all non-damaged roads, because their costs is 0
//      2. after building the MST, check if the tree is connected (check if there is one forest)
//
// Kruskal algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm

#include <bits/stdc++.h>
using namespace std;


#define     F       first
#define     S       second

typedef pair<int, int>  pi;



int n, par[109], r[109];
vector< pair<int, pi> > edges;
map<string, int> decode;



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
    n=0;
    decode.clear();
    edges.clear();

    for (int i=0; i<=50; i++)
        par[i]=i, r[i]=1;
}

int main()
{
    int t;
    scanf("%d", &t);
    for (int id=1; id<=t; id++)
    {
        int m;
        cin >> m;

        initialize();

        for (int i=0; i<m; i++)
        {
            string s, t;
            int w;

            cin >> s >> t >> w;

            if (decode.find(s)==decode.end())       decode[s]=++n;
            if (decode.find(t)==decode.end())       decode[t]=++n;

            int u=decode[s],
                v=decode[t];

           edges.push_back({w, {u, v}});
        }

        sort(edges.begin(), edges.end());

        int forests=n,
            sum=0;
        for (int i=0; i<edges.size(); i++)
        {
            int x=edges[i].S.F,
                y=edges[i].S.S,
                w=edges[i].F;

            if (link(x, y))
            {
                forests--;
                sum+=w;
            }
        }

        if (forests==1)         printf("Case %d: %d\n", id, sum);
        else                    printf("Case %d: Impossible\n", id);
    }

    return 0;
}
