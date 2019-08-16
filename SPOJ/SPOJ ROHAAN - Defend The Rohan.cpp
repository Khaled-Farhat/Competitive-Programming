// SPOJ ROHAAN - Defend The Rohan
// Topic: graphs, all pairs shortest paths, floyd
// Author: Khaled Farhat
//
// solution: just run floyd to find the shortest path from any node to any other node

#include <bits/stdc++.h>
using namespace std;


int n, adj[59][59];


void floyd()
{
    for (int k=1; k<=n; k++)
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++)
                adj[i][j]=min(adj[i][j], adj[i][k]+adj[k][j]);
}

int main()
{
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ti++)
    {
        cin >> n;

        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++)
                cin >> adj[i][j];

        floyd();

        int r, ans=0;
        cin >> r;
        while (r--)
        {
            int from, to;
            cin >> from >> to;
            ans+=adj[from][to];
        }

        cout << "Case #" << ti << ": " << ans << "\n";
    }

    return 0;
}
