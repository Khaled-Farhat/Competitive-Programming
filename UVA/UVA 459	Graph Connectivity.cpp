// Problem: UVA 459	Graph Connectivity
// Tags: Graphs, DFS
// Author: Khaled Farhat

#include <bits/stdc++.h>
using namespace std;


int n;
vector< vector<int> > adj(29);
bool vis[29];


void dfs(int node)
{
    vis[node]=1;

    for (int i=0; i<adj[node].size(); i++)
    {
        int child=adj[node][i];

        if (!vis[child])
            dfs(child);
    }
}

void initialize()
{
    for (int i=0; i<26; i++)
    {
        vis[i]=0;
        adj[i].clear();
    }
}

int main()
{
    int t;
    cin >> t;;
    while (t--)
    {
        char mx;
        cin >> mx;
        n=(int)mx-'A';

        cin.ignore();
        while (1)
        {
            string s;
            getline(cin, s);

            if (s.empty())
                break;

            int u=s[0]-'A',
                v=s[1]-'A';

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int ans=0;
        for (int i=0; i<=n; i++)
            if (!vis[i])
            {
                ans++;
                dfs(i);
            }

        cout << ans << "\n";

        if (t)
            cout << "\n";
    }

    return 0;
}
