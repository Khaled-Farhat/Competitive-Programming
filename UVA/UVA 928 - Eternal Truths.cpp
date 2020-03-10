// Problem: UVA 928 - Eternal Truths
// Tags: Graphs, BFS, Shortest Paths, SSSP
// Author: Khaled Farhat
// Solution:
//      - We will run a BFS from the start node but with a small modification,
//        the state will be (current node, number of cells in the next move)
// 
// Breadth-first search: https://en.wikipedia.org/wiki/Breadth-first_search

#include <bits/stdc++.h>
using namespace std;

#define     F       first
#define     S       second
typedef pair<int, int>  pi;

int n, m, dist[309][309][3];
bool vis[309][309][3];
char grid[309][309];
int dc[]={-1, 0, 0, 1},
    dr[]={0, -1, 1, 0};
pi st, en;

bool valid(int fromR, int fromC, int toR, int toC) {
    if (!(toR>=1 && toR<=n && toC>=1 && toC<=m)) {
        return 0;
    }

    if (fromC==toC) {
        for (int r=min(fromR, toR); r<=max(fromR, toR); ++r) {
            if (grid[r][fromC]=='#') {
                return 0;
            }
        }
    }
    else {
        for (int c=min(fromC, toC); c<=max(fromC, toC); ++c) {
            if (grid[fromR][c]=='#') {
                return 0;
            }
        }
    }

    return 1;
}

void bfs() {
    queue< pair<pi, int> > q;
    q.push({st, 0});
    vis[st.F][st.S][0]=1;
    dist[st.F][st.S][0]=0;

    while (!q.empty()) {
        pair<pi, int> currentNode=q.front();
        q.pop();

        int nextMove=currentNode.S+1;
        for (int k=0; k<4; ++k) {
            int toR=currentNode.F.F+dr[k]*nextMove,
                toC=currentNode.F.S+dc[k]*nextMove;

            if (valid(currentNode.F.F, currentNode.F.S, toR, toC) && !vis[toR][toC][nextMove%3]) {
                vis[toR][toC][nextMove%3]=1;
                dist[toR][toC][nextMove%3]=dist[currentNode.F.F][currentNode.F.S][currentNode.S]+1;
                q.push({{toR, toC}, nextMove%3});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        memset(vis, 0, sizeof vis);

        for (int i=1; i<=n; ++i) {
            for (int j=1; j<=m; ++j) {
                cin >> grid[i][j];

                if (grid[i][j]=='S') {
                    st={i, j};
                }
                else if (grid[i][j]=='E') {
                    en={i, j};
                }
            }
        }

        bfs();
        bool can=(vis[en.F][en.S][0] | vis[en.F][en.S][1] | vis[en.F][en.S][2]);
        if (can) {
            int ans=1e9;
            if (vis[en.F][en.S][0]) {
                ans=dist[en.F][en.S][0];
            }

            if (vis[en.F][en.S][1]) {
                ans=min(ans, dist[en.F][en.S][1]);
            }

            if (vis[en.F][en.S][2]) {
                ans=min(ans, dist[en.F][en.S][2]);
            }

            cout << ans << "\n";
        }
        else {
            cout << "NO\n";
        }
    }

    return 0;
}
