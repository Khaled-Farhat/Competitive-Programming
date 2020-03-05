// Problem: UVA 10422 - Knights in FEN
// Tags: Graphs, SSSP, BFS
// Author: Khaled Farhat
// Solution idea:
//      - In each test case we are given a state and asked to find the shortest path of length <= 10 to a final state,
//        let's call the final state F. Since the graph is undirected, the shortest path from any state S to F is the same
//        of the shortest path from F to S, so we can run just one BFS from F and find the shortest paths to the other states
//        before processing any test case, so we can answer each test case in O(1)/
//      - We will use two bitmasks to represent each state, one of the contains just a set bit in the empty cell, and the other
//        contains a set bit in position of black Knights.
//
// Breadth First Search: https://en.wikipedia.org/wiki/Breadth-first_search


#include <bits/stdc++.h>
using namespace std;

#define     F       first
#define     S       second
typedef pair<int, int>  pi;

int lg2[(1<<25)],
    dc[]={-2, -2, -1, -1, 1, 1, 2, 2},
    dr[]={-1, 1, -2, 2, -2, 2, -1, 1};
map<pi, int> dist;

bool valid(int r, int c) {
    return (r>=0 && r<5 && c>=0 && c<5);
}

int getBit(int r, int c) {
    return (1<<(r*5+c));
}

pi getPos(int mask) {
    int pos=lg2[mask];
    return {pos/5, pos%5};
}

void bfs(int startNode) {
    queue<pi> q;
    q.push({startNode, getBit(2, 2)});
    dist[{startNode, getBit(2, 2)}]=0;
    while (!q.empty()) {
        pi cur=q.front();
        q.pop();

        if (dist[cur]>=10) {
            break;
        }

        int& curMask=cur.F;
        pi pos=getPos(cur.S);
        for (int k=0; k<8; ++k) {
            int toR=pos.F+dr[k],
                toC=pos.S+dc[k];

            if (valid(toR, toC)) {
                int nxtPos=getBit(toR, toC),
                    nxtMask=(curMask & (~nxtPos));

                if (curMask & nxtPos) {
                    nxtMask |= getBit(pos.F, pos.S);
                }

                if (dist.find({nxtMask, nxtPos})==dist.end()) {
                    dist[{nxtMask, nxtPos}]=dist[cur]+1;
                    q.push({nxtMask, nxtPos});
                }
            }
        }
    }
}

void precalc() {
    int mask=0;
    for (int i=0; i<5; ++i) {
        for (int j=i+1; j<5; ++j) {
            mask |= getBit(i, j);
        }
    }

    mask |= getBit(0, 0);
    mask |= getBit(1, 1);

    lg2[0]=lg2[1]=0;
    for (int i=2; i<(1<<25); ++i) {
        lg2[i]=lg2[(i>>1)]+1;
    }

    bfs(mask);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    precalc();
    int t;
    cin >> t;
    cin.ignore();
    while (t--) {
        int mask=0, pos=0;
        for (int i=0; i<5; ++i) {
            string s;
            getline(cin, s);
            for (int j=0; j<5; ++j) {
                if (s[j]=='1') {
                    mask |= getBit(i, j);
                }
                else if (s[j]==' ') {
                    pos=getBit(i, j);
                }
            }
        }

        if (dist.find({mask, pos})!=dist.end()) {
            cout << "Solvable in " << dist[{mask, pos}] << " move(s).\n";
        }
        else {
            cout << "Unsolvable in less than 11 move(s).\n";
        }
    }

    return 0;
}
