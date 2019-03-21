/**
 *  created on: 21.03.2019
 *  author: Khaled Farhat
**/



#include <iostream>
#include <vector>
#include <utility>
#include <map>
using namespace std;


    const int MOD=1e9+7;
    int n, k;
    long long ans;
    vector< vector<int> > adj;
    vector<bool> vis;
    map< pair<int, int>, bool> black;


long long powMod (long long b, long long p)
{
    if (p==0)
        return 1;

    long long sq=powMod(b, p/2);
    sq*=sq;
    sq%=MOD;

    if (p%2!=0)
        sq*=b;

    sq%=MOD;
    return sq;
}

int dfs (int node)
{
    vis[node]=1;
    int cnt=1;

    for (int i=0; i<adj[node].size(); i++)
    {
        int child=adj[node][i];

        if (!vis[child]  &&  !black[make_pair(node, child)])
            cnt+=dfs(child);
    }

    return cnt;
}

int main()
{
    cin >> n >> k;

    adj=vector< vector<int> > (n+1);
    vis=vector<bool> (n+1, 0);

    for (int i=0; i<n-1; i++)
    {
        int u, v, x;
        cin >> u >> v >> x;

        adj[u].push_back(v);
        adj[v].push_back(u);

        black[make_pair(u, v)]=x;
        black[make_pair(v, u)]=x;
    }

    ans=powMod(n, k);
    for (int i=1; i<=n; i++)
        if (!vis[i])
        {
            long long cnt=dfs(i);
            ans-=powMod(cnt, k);

            ans+=MOD;
            ans%=MOD;
        }

    cout << ans;

    return 0;
}
