// Problem: Light OJ 1210 - Efficient Traffic System
// Tags: Graphs, Strongly Connected Component
// Author: Khaled Farhat
//
// Solution idea:
//      The task ask us to determine the minimum number of edges we should add, such that for each node there is path to each other node, so:
//
//      - Get all Strongly Connected Components. All nodes in each SCC can reach each other,
//         so we will not add any edge between two nodes if they are in the same SCC,
//         each edge we should add are between two nodes in different SCC.
//
//      - Now, we can reduce the task to find the minimum number of edges we should add so that for each SCC,
//        there is a path to each other SCC.
//        it is obvious that we can do that by linking:
//        (all component with out degree equals 0) to (all components with in degree equals 0).
//
//      - So we count the number of components with (out degree == 0) and the number of components with (in degree == 0),
//        and the answer is the maximum between these two numbers.
//
//      - One special case is when there is one SCC,
//        then there is no need to add any edge since each node in this SCC have a path to each other node in this SCC.
//
// this solution uses Tarjan Algorithm to find SCC: https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm

#include <bits/stdc++.h>
using namespace std;


const int MAX=20009;
int n, cnt, scc, inD[MAX], outD[MAX], comp[MAX], low[MAX], ndfs[MAX];
vector<int> adj[MAX];
stack<int> stk;
bool inStack[MAX], vis[MAX];


void tarjan(int node) {
    ndfs[node]=low[node]=cnt++;

    stk.push(node);
    inStack[node]=1;

    for (int i=0; i<adj[node].size(); i++) {
        int child=adj[node][i];

        if (ndfs[child]==-1) {
            tarjan(child);
            low[node]=min(low[node], low[child]);
        }

        else if (inStack[child])
            low[node]=min(low[node], ndfs[child]);
    }

    if (ndfs[node]==low[node]) {
        int u=-1;

        do {
            u=stk.top();
            stk.pop();

            inStack[u]=0;
            comp[u]=scc;
        } while(u!=node);

        scc++;
    }
}

void dfs(int node) {
    vis[node]=1;

    for (int i=0; i<adj[node].size(); i++) {
        int child=adj[node][i];

        if (comp[node]!=comp[child]) {
            outD[comp[node]]++;
            inD[comp[child]]++;
        }

        if (!vis[child])
            dfs(child);
    }
}

void initialize() {
    scc=cnt=0;

    for (int i=0; i<=n; i++) {
        ndfs[i]=low[i]=comp[i]=-1;
        inD[i]=outD[i]=vis[i]=inStack[i]=0;
        adj[i].clear();
    }
}

int main() {
    int t;
    scanf("%d", &t);

    for (int id=1; id<=t; id++) {
        int m;
        scanf("%d%d", &n, &m);

        initialize();

        while (m--) {
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
        if (scc>1) {
            int in=0, out=0;

            for (int i=0; i<scc; i++) {
                if (!inD[i])        in++;
                if (!outD[i])       out++;
            }

            ans=max(in, out);
        }

        printf("Case %d: %d\n", id, ans);
    }

    return 0;
}
