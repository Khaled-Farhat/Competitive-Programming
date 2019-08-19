// Problem: UVA 11631 - Dark roads
// Tags: Graphs, MST, Kruskal
// Author: Khaled Farhat
// Solution idea:
//      - Find the Minimum Spanning tree, the answer is the sum of all edges that are not included in the MST
//      - So the answer is: (total edges sum - MST edges sum)
// 
// Kruskal algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
// The problem can also be solved by Prim algorithm

#include <bits/stdc++.h>
using namespace std;


#define     F       first
#define     S       second

typedef pair<int, int>  pi;



int m, par[200009], r[200009];
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
    for (int i=0; i<m; i++)
        par[i]=i, r[i]=1;
}

int main()
{
    int n;
    while (cin >> m >> n  &&  (n+m))
    {
        initialize();

        int sum=0;
        while (n--)
        {
            int x, y, z;
            cin >> x >> y >> z;

            sum+=z;
            edges.push_back({z, {x, y}});
        }

        sort(edges.begin(), edges.end());

        for (int i=0; i<edges.size(); i++)
        {
            int x=edges[i].S.F,
                y=edges[i].S.S,
                z=edges[i].F;

            if (link(x, y))
                sum-=z;
        }

        cout << sum << "\n";
    }

    return 0;
}
