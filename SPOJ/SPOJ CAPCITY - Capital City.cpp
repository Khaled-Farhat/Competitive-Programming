// Problem: SPOJ CAPCITY - Capital City
// Tags: Graphs, Strongly Connected Component
// Author: Khaled Farhat
//
// Solution idea and tutorial:
//
//      - Let's get all Strongly Connected Components
//
//      - All nodes in the same SCC can reach each other, so we will search for SCCs that each other SCCs can reach it
//
//      - First observation: if there is a SCC that each SCCs can reach it, then this SCC is unique, prove:
//        hypothesis: There is at most one SCC that all SCCs can reach it
//        prove: suppose (there is two SCCs: (x) and (y)) and (x != y) and (all SCCs can reach (x) and (y))
//               all SCCs can reach (x) => (y) can reach (x)
//               all SCCs can reach (y) => (x) can reach (y)
//               hence we have (x) reaches (y) and (y) reaches (x) => (x) and (y) are in the same SCC => x == y
//               This is a contradiction with hypothesis that (x !=y )
//
//      - Since this SCC is unique and all SCCs visit it, then this SCC will not visit any other SCC,
//        we can we can prove that in similar way to the previous prove,
//        then we will search for SCC that its out degree is 0,
//        and also do not forget to check that there is no more SCC with satisfy that
//
// this solution uses Tarjan Algorithm to find SCC: https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm


#include <bits/stdc++.h>
using namespace std;


const int MAX=1e5+5;
int n, cnt, scc, nDfs[MAX], lowLink[MAX], outDegree[MAX], comp[MAX];
vector<int> adj[MAX];
stack<int> stk;
bool inStack[MAX], vis[MAX];


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

        else if (inStack[child]) {
            lowLink[cur]=min(lowLink[cur], nDfs[child]);
        }
    }

    if (nDfs[cur]==lowLink[cur]) {

        int u=-1;

        while (u!=cur) {
            u=stk.top();
            stk.pop();

            comp[u]=scc;
            inStack[u]=0;
        }

        scc++;
    }
}

void dfs(int cur) {

    vis[cur]=1;

    for (int i=0; i<adj[cur].size(); i++) {
        int child=adj[cur][i];

        if (comp[child]!=comp[cur]) {
            outDegree[comp[cur]]++;
        }

        if (!vis[child]) {
            dfs(child);
        }
    }
}

int main() {

    int m;
    cin >> n >> m;

    while (m--) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    memset(nDfs, -1, sizeof nDfs);

    for (int i=1; i<=n; i++) {
        if (nDfs[i]==-1) {
            tarjan(i);
        }
    }

    for (int i=1; i<=n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }

    int ansComp=-1;

    for (int i=0; i<scc; i++) {
        if (!outDegree[i]) {
            if (ansComp!=-1) {
                cout << 0;
                return 0;
            }
            else
                ansComp=i;
        }
    }

    vector<int> ansNodes;
    
    for (int i=1; i<=n; i++) {
        if (comp[i]==ansComp) {
            ansNodes.push_back(i);
        }
    }

    cout << ansNodes.size() << "\n";

    for (int i=0; i<ansNodes.size(); i++) {
        cout << ansNodes[i] << " ";
    }

    return 0;
}
