// Problem: Light OJ 1168 - Wishing Snake
// Tags: Graphs, Strongly Connected Component
// Author: Khaled Farhat
//
// Solution idea and tutorial:
//
//      - The solution exists if the snack can visit every edge in the graph
//
//      - Get all Strongly Connected Components,
//        it is obvious that: if the snack was in any SCC then it can visit every other edge in this SCC
//
//      - So the problem now have been reduce to check if the snack can visit the edges which connect any two SCC,
//        and to check that, three condition must hold:
//
//        1. (in degree of each SCC) <= 1
//            why is that true? if a SCC has in degree of more than 1 SCC, the snack will be visited by one of those parents,
//            but then it can not visit any other edge that links other parents with this SCC, prove:
//
//            hypothesis: if (x and y are two SCC) and (x != y) and (x can visit y), then (y can not visit x)
//            prove: if (y can visit x) => ( (x can visit y) and (y can visit x) )
//                   => (x and y are the same SCC and x=y),
//                   This is a contradiction with hypothesis that (x!=y)
//
//        2. (out degree of each SCC) <= 1
//            why is that true? if the snack was in a SCC which has out degree of more that 1,
//            the snack can not walk through more that one edge which connect this SCC with its neighbors,
//            we can prove that in similar way to the previous condition
//
//        3. The snack at first in the checkpoint 0, so we can run DFS to check if the 0 SCC can visit all other SCCs
//
// this solution uses Tarjan Algorithm to find SCC: https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm

#include <bits/stdc++.h>
using namespace std;


const int MAX=1e5+9;
int n, cnt, scc, nDfs[MAX], lowLink[MAX], comp[MAX], out[MAX], in[MAX];
vector<int> adj[MAX], adjComp[MAX];
stack<int> stk;
bool inStack[MAX], vis[MAX], exist[MAX];


void tarjan(int cur) {

    nDfs[cur]=lowLink[cur]=cnt++;

    stk.push(cur);
    inStack[cur]=1;

    for (int i=0; i<adj[cur].size(); i++) {
        int child=adj[cur][i];

        if (nDfs[child]==-1) {
            tarjan(child);
            lowLink[cur]=min(lowLink[cur], lowLink[child]);
        }

        else if (inStack[child])
            lowLink[cur]=min(lowLink[cur], nDfs[child]);
    }

    if (nDfs[cur]==lowLink[cur]) {
        int u=-1;

        while (u!=cur) {
            u=stk.top();
            stk.pop();
            inStack[u]=0;
            comp[u]=scc;
        }

        scc++;
    }
}

void dfs(int cur) {

    vis[cur]=1;

    for (int i=0; i<adj[cur].size(); i++) {
        int child=adj[cur][i];

        if (comp[child]!=comp[cur]) {
            out[comp[cur]]++;
            in[comp[child]]++;
            adjComp[comp[cur]].push_back(comp[child]);
        }

        if (!vis[child])
            dfs(child);
    }
}

void dfsComp(int curComp) {

    vis[curComp]=1;

    for (int i=0; i<adjComp[curComp].size(); i++) {
        int child=adjComp[curComp][i];

        if (!vis[child])
            dfsComp(child);
    }
}

void initialize() {

    cnt=scc=0;

    for (int i=0; i<1000; i++) {
        in[i]=out[i]=exist[i]=vis[i]=inStack[i]=0;
        nDfs[i]=lowLink[i]=-1;
        adj[i].clear();
        adjComp[i].clear();
    }
}

int main() {

    int t;
    scanf("%d", &t);

    for (int id=1; id<=t; id++) {
        scanf("%d", &n);
        initialize();

        for (int i=0; i<n; i++) {
            int k;
            scanf("%d", &k);

            while (k--) {
                int u, v;
                scanf("%d%d", &u, &v);
                exist[u]=exist[v]=1;
                adj[u].push_back(v);
            }
        }

        if (!exist[0]) {
            printf("Case %d: NO\n", id);
            continue;
        }

        for (int i=0; i<1000; i++)
            if (exist[i]  &&  nDfs[i]==-1)
                tarjan(i);

        for (int i=0; i<1000; i++)
            if (exist[i]  &&  !vis[i])
                dfs(i);

        memset(vis, 0, sizeof vis);
        dfsComp(comp[0]);

        bool can=1;
        for (int i=0; i<scc; i++)
            if (in[i]>1  ||  out[i]>1  ||  !vis[i])
                can=0;

        if (!can)
            printf("Case %d: NO\n", id);

        else
            printf("Case %d: YES\n", id);
    }

    return 0;
}
