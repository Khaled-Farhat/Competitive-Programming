// Problem: SPOJ QUEEN - Wandering Queen
// Tags: Graphs, BFS
// Author: Khaled Farhat

#include <bits/stdc++.h>
using namespace std;


#define     F       first
#define     S       second

typedef pair<int, int>  pi;




int n, m, dist[1009][1009],
    dr[]={-1, 0, 1, -1, 1, -1, 0, 1},
    dc[]={-1, -1, -1, 0, 0, 1, 1, 1};
bool vis[8][1009][1009];
char grid[1009][1009];



bool valid(int r, int c, int k)
{
    return r>=0  &&  r<n  &&  c>=0  &&  c<m  &&  grid[r][c]!='X'  &&  !vis[k][r][c];
}

void bfs(int r, int c, int dst_r, int dst_c)
{
    queue<pi> q;
    q.push({r, c});
    dist[r][c]=1;

    int sz=1,
        dep=0;
    bool ok=0;
    for(; !q.empty()  &&  !ok; sz=(int)q.size(), dep++)
        while (sz--)
        {
            int cur_r=q.front().F,
                cur_c=q.front().S;
            q.pop();

            if (cur_r==dst_r  &&  cur_c==dst_c)
            {
                ok=1;
                break;
            }

            for (int k=0; k<8; k++)
                for (int i=1; i<=m; i++)
                {
                    int toR=cur_r+dr[k]*i,
                        toC=cur_c+dc[k]*i;

                    if (valid(toR, toC, k))
                    {
                        if (dist[toR][toC]==-1)
                        {
                            q.push({toR, toC});
                            dist[toR][toC]=dep+1;
                            vis[k][toR][toC]=1;
                        }

                        else
                            vis[k][toR][toC]=1;
                    }

                    else // we can not go more in this direction
                        break;
                }
        }
}

void initialize()
{
    for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
            {
                dist[i][j]=-1;

                for (int k=0; k<8; k++)
                    vis[k][i][j]=0;
            }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;

        initialize();

        pi st, en;
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
            {
                cin >> grid[i][j];

                if (grid[i][j]=='S')        st={i, j};
                else if (grid[i][j]=='F')   en={i, j};
            }

        bfs(st.F, st.S, en.F, en.S);

        cout << dist[en.F][en.S] << "\n";
    }

    return 0;
}
