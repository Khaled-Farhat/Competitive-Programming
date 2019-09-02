// Problem: SPOJ TFRIENDS - True Friends
// Tags: Graphs, Strongly Connected Component
// Author: Khaled Farhat
//
// Solution idea and tutorial:
//      - The answer is the number of Strongly Connected Components
//
// this solution uses Tarjan Algorithm to find SCC: https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm

#include <bits/stdc++.h>
using namespace std;


const int MAX=109;
int n, cnt, scc, nDfs[MAX], lowLink[MAX];
stack<int> stk;
char adj[MAX][MAX];
bool inStack[MAX];


void tarjan(int cur) {

    nDfs[cur]=lowLink[cur]=cnt++;

    stk.push(cur);
    inStack[cur]=1;

    for (int i=1; i<=n; i++) {

        if (adj[cur][i]=='N') {
            continue;
        }

        if (nDfs[i]==-1) {
            tarjan(i);
            lowLink[cur]=min(lowLink[cur], lowLink[i]);
        }

        else if (inStack[i]) {
            lowLink[cur]=min(lowLink[cur], nDfs[i]);
        }
    }

    if (lowLink[cur]==nDfs[cur]) {
        int u=-1;

        while (u!=cur) {
            u=stk.top();
            stk.pop();
            inStack[u]=0;
        }

        scc++;
    }
}

void initialize() {

    scc=cnt=0;
    memset(nDfs, -1, sizeof nDfs);
}

int main() {

    int t;
    cin >> t;

    while (t--) {
        cin >> n;

        initialize();

        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                cin >> adj[i][j];
            }
        }

        for (int i=1; i<=n; i++) {
            if (nDfs[i]==-1) {
                tarjan(i);
            }
        }

        cout << scc << "\n";
    }

    return 0;
}
