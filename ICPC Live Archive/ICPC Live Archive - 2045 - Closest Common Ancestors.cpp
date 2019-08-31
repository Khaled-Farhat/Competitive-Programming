// Problem: ICPC Live Archive - 2045 - Closest Common Ancestors
// Tags: Graphs, LCA, Sparse Table
// Author: Khaled Farhat
// Solution idea:
//      1. Get LCA, in this solution I am using Euler Tour to reduce the problem to RMQ,
//         which can be solved using Sparse Table Data Structure <n*log(n), o(1)>
// 

#include <bits/stdc++.h>
using namespace std;


int n, root, idx, lg2[1000009], dep[2000009], cnt[100009], loc[1000009], spt[200009][21];
vector<int> adj[1000009];
vector<int> euler;
set<int> s;
bool vis[1000009];
char ch;


void dfs(int cur, int depth) {

    vis[cur]=1;
    loc[cur]=idx;
    dep[idx++]=depth;
    euler.push_back(cur);

    for (int i=0; i<adj[cur].size(); i++) {
        int child=adj[cur][i];

        if (vis[child])
            continue;

        dfs(child, depth+1);

        dep[idx++]=depth;
        euler.push_back(cur);
    }
}

void buildSparse() {

    dfs(root, 0);

    for (int i=1; i<idx; i++)
        spt[i][0]=i;

    for (int j=1; (1<<j)<idx; j++)
        for (int i=1; i+(1<<j)-1<idx; i++) {
            int x=spt[i][j-1],
                y=spt[i+(1<<(j-1))][j-1];

            if (dep[x]<dep[y])      spt[i][j]=x;
            else                    spt[i][j]=y;
        }
}

int qwr(int l, int r) {
    int k=lg2[r-l+1],
        x=spt[l][k],
        y=spt[r-(1<<k)+1][k];

    if (dep[x]<dep[y])
        return x;

    return y;
}

void lca(int u, int v) {

    if (loc[u]>loc[v])
        swap(u, v);

    int mn=euler[qwr(loc[u], loc[v])];

    cnt[mn]++;
    s.insert(mn);
}

void initialize() {

    idx=0;
    euler.clear();
    s.clear();

    for (int i=0; i<=n; i++) {
        adj[i].clear();
        cnt[i]=vis[i]=0;
        loc[i]=-1;
    }
}

void buildLog() {

    lg2[0]=lg2[1]=0;

    for (int i=2; i<=1000000; i++)
        lg2[i]=lg2[i/2]+1;
}

int main() {

    buildLog();

    while (cin >> n) {

        initialize();

        for (int i=1; i<=n; i++) {
            int cur;
            cin >> cur >> ch >> ch;

            if (i==1)
                root=cur;

            int k;
            cin >> k >> ch;

            while (k--) {
                int to;
                cin >> to;
                adj[cur].push_back(to);
                adj[to].push_back(cur);
            }
        }

        buildSparse();

        int q;
        cin >> q;
        while (q--) {
            int x, y;
            cin >> ch >> x >> y >> ch;
            lca(x, y);
        }

        for (int i=1; i<=n; i++)
            if (cnt[i])
                cout << i << ":" << cnt[i] << "\n";
    }

    return 0;
}
