// Problem: Light OJ 1034 - Hit the Light Switches
// Tags: Graphs, Topological sorting, Strongly Connected Components
// Author: Khaled Farhat
// Solution idea:
//      1. Get all connected components,
//        now in each component, it is sufficient to choose only one node, since it can reach all others nodes in this component.
//
//      2. Transitive closure: some component can be reached from other components,
//                             so calculate the in degree of each component using DFS
//      3. Iterate over components, for the component i:
//         - if the component in degree is 0 this means that we can reach all nodes in this component from a node outside this component
//           so we will not choose any node in this component
//         - else, if the in degree of a component is 0, then we can not reach any node in this component from a node outside the component,
//           so we must choose a node in this component and increase the answer by 1
// 

#include <bits/stdc++.h>
using namespace std;
 
 
int ndfs[10009], lowLink[10009], comp[10009], n, scc, cnt, indComp[10009];
vector< vector<int> > adj(10009);
stack<int> stk;
bool inStack[10009], vis[10009];
 
 
 
 
void tarjan(int node)
{
    ndfs[node]=lowLink[node]=cnt++;
 
    stk.push(node);
    inStack[node]=1;
 
    for (int i=0; i<adj[node].size(); i++)
    {
        int child=adj[node][i];
 
        if (ndfs[child]==-1)
        {
            tarjan(child);
            lowLink[node]=min(lowLink[node], lowLink[child]);
        }
 
        else if (inStack[child])
            lowLink[node]=min(lowLink[node], ndfs[child]);
    }
 
    if (lowLink[node]==ndfs[node])
    {
        int u=-1;
 
        while (u!=node)
        {
            u=stk.top();
            inStack[u]=0;
            stk.pop();
 
            comp[u]=scc;
        }
 
        scc++;
    }
}
 
void dfs(int node)
{
    vis[node]=1;
 
    for (int i=0; i<adj[node].size(); i++)
    {
        int child=adj[node][i];
 
        if (comp[child]!=comp[node])
            indComp[comp[child]]++;
 
        if (!vis[child])
            dfs(child);
    }
}
 
void initialize()
{
    for (int i=0; i<=n; i++)
    {
        ndfs[i]=comp[i]=lowLink[i]=-1;
        indComp[i]=inStack[i]=vis[i]=0;
        adj[i].clear();
    }
 
    scc=cnt=0;
}
 
int main()
{
    int t;
    scanf("%d", &t);
    for (int id=1; id<=t; id++)
    {
        int m;
        scanf("%d%d", &n, &m);
 
        initialize();
 
        while (m--)
        {
            int x, y;
            scanf("%d%d", &x, &y);
 
            adj[x].push_back(y);
        }
 
        for (int i=1; i<=n; i++)
            if (ndfs[i]==-1)
                tarjan(i);
 
        for (int i=1; i<=n; i++)
            if (!vis[i])
                dfs(i);
 
        int ans=0;
        for (int i=0; i<scc; i++)
            if (!indComp[i])
                ans++;
 
        printf("Case %d: %d\n", id, ans);
    }
 
    return 0;
}

