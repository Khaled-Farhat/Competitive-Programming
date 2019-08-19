// Problem: UVA 11747 - Heavy Cycle Edges
// Tags: Graphs, MST, Kruskal
// Author: Khaled Farhat
// Solution idea:
//      - Build MST and print the weight of each edge that is not included in MST
//
// Kruskal algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
// The problem can also be solved by Prim algorithm

#include <bits/stdc++.h>
using namespace std;


#define     F       first
#define     S       second

typedef pair<int, int>  pi;



int n, par[1009], r[1009];
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
    else if (r[parU]==r[parV])       r[parV]++;

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
    int m;
    while (cin >> n >> m  &&  (n+m))
    {
        initialize();

        while (m--)
        {
            int x, y, w;
            cin >> x >> y >> w;
            edges.push_back({w, {x, y}});
        }

        sort(edges.begin(), edges.end());

        vector<int> ans;
        for (int i=0; i<edges.size(); i++)
        {
            int x=edges[i].S.F,
                y=edges[i].S.S,
                w=edges[i].F;

            if (!link(x, y))
                ans.push_back(w);
        }

        if (ans.size())
        {
            cout << ans[0];
            for (int i=1; i<ans.size(); i++)
                cout << " " << ans[i];
                
            cout << "\n";
        }

        else
            cout << "forest\n";
    }

    return 0;
}
