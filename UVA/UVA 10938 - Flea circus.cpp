// Problem: UVA 10938 - Flea circus
// Tags: Graphs, LCA, Sparse Table
// Author: Khaled Farhat
//
// Solution idea and tutorial:
//      for each two nodes (x, y):
//
//      1. Get the Lowest Common Ancestor of x and y, the path between x and y must pass from LCA(x, y)
//
//      2. The path length is the distance from y to LCA(x, y) + the distance from LCA(x, y) to x,
//         so the path is (depth[x]-depth[LCA(x, y)])+(depth[y]-depth[LCA(x, y)])
//         the depth of x is the distance between the root and x
//         we can find the depth of each node using DFS: depth[child]=depth[parent]+1
//
//      3. Each node should go half the path length, it is easy to do so using Sparse Table Data Structure
//
//      4. If the path length is odd, then it is obvious that the nodes will not meet
// 
// Read about Sparse Table: https://www.hackerearth.com/practice/notes/sparse-table/
// Read about Lowest Common Ancestor: https://cp-algorithms.com/graph/lca_binary_lifting.html

#include <bits/stdc++.h>
using namespace std;


int n, lg2[5009], spt[5009][19], dep[5009];
vector<int> adj[5009];


void dfs(int cur, int par) {

    for (int i=0; i<adj[cur].size(); i++) {
        int child=adj[cur][i];

        if (child==par)
            continue;

        spt[child][0]=cur;
        dep[child]=dep[cur]+1;
        dfs(child, cur);
    }
}

void buildSparse() {

    dep[1]=0;
    dfs(1, -1);

    for (int j=1; (1<<j)<=n; j++)
        for (int i=1; i<=n; i++)
            if (spt[i][j-1]!=-1)
                spt[i][j]=spt[spt[i][j-1]][j-1];
}

void lca(int x, int y) {

    if (dep[x]<dep[y])
        swap(x, y);

    int saveX=x,
        saveY=y;

    // first we should make x and y at the same depth
    for (int k=lg2[n]; k>=0; k--)
        if (dep[x]-(1<<k)>=dep[y])
            x=spt[x][k];

    int lcaNode=x;

    if (x!=y) {
        for (int k=lg2[n]; k>=0; k--)
            if (spt[x][k]!=spt[y][k]) {
                x=spt[x][k];
                y=spt[y][k];
            }

        lcaNode=spt[x][0];
    }

    // the distance of the shortest path between saveX and saveY
    int dist=(dep[saveX]-dep[lcaNode])+(dep[saveY]-dep[lcaNode]),
        jump=dist/2; // each node will jump half the path distance

    x=saveX; // x is the deeper node
    int cnt=0;
    for (int k=lg2[n]; k>=0; k--)
        if (cnt+(1<<k)<=jump) {
            x=spt[x][k];
            cnt+=(1<<k);
        }

    if (dist%2!=0)
        cout << "The fleas jump forever between " << min(x, spt[x][0]) << " and " << max(x, spt[x][0]) << ".\n";

    else
        cout << "The fleas meet at " << x << ".\n";
}

void buildLog() {

    lg2[0]=lg2[1]=0;

    for (int i=2; i<=5000; i++)
        lg2[i]=lg2[i/2]+1;
}

void initialize() {

    memset(spt, -1, sizeof spt);

    for (int i=1; i<=n; i++)
        adj[i].clear();
}

int main() {

    buildLog();

    while (cin >> n  &&  n) {

        initialize();

        for (int i=0; i<n-1; i++) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        buildSparse();

        int l;
        cin >> l;
        while (l--) {
            int x, y;
            cin >> x >> y;
            lca(x, y);
        }
    }

    return 0;
}
