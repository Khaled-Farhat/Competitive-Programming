// Problem: LightOJ 1059 - Air Ports
// Tags: Graphs, MST, Kruskal
// Author: Khaled Farhat
// Solution idea:
//      - First of all we will consider that there is an airport in each city
//      - Iterate over roads, for road i lets say that its cost is w, and this road connects cities x and y
//        we will build this road if (x and y are not connected to the same airport) and (w < a)
//        this means that linking city x to city y has cost less than building airport in x
//
// Kruskal algorithm: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm

#include <bits/stdc++.h>
using namespace std;


#define     F       first
#define     S       second

typedef pair<int, int>  pi;



int n, par[10009], r[10009];
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
    for (int i=1; i<=n; i++)
        par[i]=i, r[i]=1;
}

int main()
{
    int t;
    scanf("%d", &t);
    for (int id=1; id<=t; id++)
    {
        int m, a;
        cin >> n >> m >> a;

        initialize();

        while (m--)
        {
            int x, y, w;
            cin >> x >> y >> w;
            edges.push_back({w, {x, y}});
        }

        sort(edges.begin(), edges.end());

        int forests=n,
            sum=0;
        for (int i=0; i<edges.size(); i++)
        {
            int x=edges[i].S.F,
                y=edges[i].S.S,
                w=edges[i].F;

            if (w<a  &&  link(x, y))
            {
                forests--;
                sum+=w;
            }
        }

        sum+=forests*a;

        printf("Case %d: %d %d\n", id, sum, forests);
    }

    return 0;
}
