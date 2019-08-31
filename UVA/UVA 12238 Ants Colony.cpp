// Problem: UVA 12238 Ants Colony
// Tags: Graphs, LCA, Sparse Table
// Author: Khaled Farhat
//
// Solution idea and tutorial:
//      for each two nodes (x, y):
//
//      1. Get the Lowest Common Ancestor of x and y, the path between x and y must pass from LCA(x, y)
//
//      2. The path length is the distance from y to LCA(x, y) + the distance from LCA(x, y) to x,
//         we can calculate this distance using sparse table, for each jump of 2^j, update the cost and the destination:
//         spt[i][j].destination = spt[ spt[i][j-1] ][j-1].destination
//         spt[i][j].cost = spt[i][j-1].cost + spt[ spt[i][j-1] ][j-1].cost
// 
// Read about Sparse Table: https://www.hackerearth.com/practice/notes/sparse-table/
// Read about Lowest Common Ancestor: https://cp-algorithms.com/graph/lca_binary_lifting.html

#include <bits/stdc++.h>
using namespace std;


#define     F       first
#define     S       second

typedef long long       ll;
typedef pair<int, int>  pi;
typedef pair<int, ll>   pl;


int n, lg2[100009], dep[100009];
pl spt[100009][20];
vector<pi> adj[100009];


void dfs(int cur, int par) {

    for (int i=0; i<adj[cur].size(); i++) {
        int child=adj[cur][i].F,
            cost=adj[cur][i].S;

        if (child==par)
            continue;

        dep[child]=dep[cur]+1;
        spt[child][0]={cur, cost};

        dfs(child, cur);
    }
}

pl combine(pl x, pl y) {

    return {y.F, x.S+y.S};
}

void buildSparse() {

    dep[1]=0;
    dfs(1, -1);

    for (int j=1; (1<<j)<=n; j++)
        for (int i=1; i<=n; i++)
            if (spt[i][j-1].F!=-1  &&  spt[spt[i][j-1].F][j-1].F!=-1)
                spt[i][j]=combine(spt[i][j-1], spt[spt[i][j-1].F][j-1]);
}

ll lca(int x, int y) {

    if (dep[x]<dep[y])
        swap(x, y);

    ll sum=0;
    for (int k=lg2[n]; k>=0; k--)
        if (dep[x]-(1<<k)>=dep[y]) {
            sum+=spt[x][k].S;
            x=spt[x][k].F;
        }

    for (int k=lg2[n]; k>=0; k--)
        if (spt[x][k].F!=spt[y][k].F) {
            sum+=spt[x][k].S+spt[y][k].S;
            x=spt[x][k].F;
            y=spt[y][k].F;
        }

    if (x!=y)
        sum+=spt[x][0].S+spt[y][0].S;

    return sum;
}

void buildLog() {

    lg2[0]=lg2[1]=0;

    for (int i=2; i<=100000; i++)
        lg2[i]=lg2[i/2]+1;
}

void initialize() {

    memset(spt, -1, sizeof spt);

    for (int i=0; i<=n; i++)
        adj[i].clear();
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    buildLog();

    while (cin >> n  &&  n ) {

        initialize();

        for (int i=1; i<=n-1; i++) {
            int to, cost;
            cin >> to >> cost;
            adj[i].push_back({to, cost});
            adj[to].push_back({i, cost});
        }

        buildSparse();

        int q;
        cin >> q;
        while (q--) {
            int s, t;
            cin >> s >> t;

            cout << lca(s, t);

            if (q)
                cout << " ";
        }

        cout << "\n";
    }

    return 0;
}
