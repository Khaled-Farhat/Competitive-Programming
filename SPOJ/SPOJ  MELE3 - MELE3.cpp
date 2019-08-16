/// SPOJ MELE3 - MELE3
/// topic: graphs - shortest paths - dijkstra
/// Author: Khaled Farhat


#include <bits/stdc++.h>
using namespace std;


#define     F       first
#define     S       second

typedef long long       ll;
typedef pair<int, int>  pi;



const ll OO=1e18;
int k, n;
ll dist[1009];
bool vis[1009];
vector< vector<int> > adj(1009);



void dijkstra()
{
    priority_queue<pi> pq;
    pq.push({0, 1});

    while (!pq.empty())
    {
        int cur=pq.top().S;
        pq.pop();


        if (vis[cur])
            continue;

        vis[cur]=1;


        for (int i=0; i<adj[cur].size(); i++)
        {
            int child=adj[cur][i],
                cost=fabs(child-cur)*5,
                cnt=dist[cur]/cost; // to find the direction of the elevator


            int pos=-1; // the position of the elevator at the current moment
            if (cnt%2==0)       pos=min(child, cur)+(dist[cur]%cost)/5;
            else                pos=max(cur, child)-(dist[cur]%cost)/5;


            int need=cost;

            if (child>cur) // the edges is (lower -> upper)
            {
                if (cnt%2==0) // the elevator direction at the current moment is (lower -> upper)
                {
                    if (pos!=child  &&  pos!=cur) // if the elevator is in the middle of the path,
                        need+=(child-pos)*5; // the elevator is on the upper floor

                    if (pos!=cur) // if the elevator is not on the lower floor,
                        need+=cost; // the elevator is on the lower floor
                }

                else // the director is (upper -> lower)
                {
                    if (pos!=cur) // if the elevator is not on the lower floor at the current moment,
                        need+=(pos-cur)*5; // the elevator now is on the lower floor
                }
            }

            else // the edge is (upper -> lower)
            {
                if (cnt%2==0) // the elevator direction at the current moment is (lower -> upper)
                {
                    if (pos!=cur) // if the elevator is not on the upper floor,
                        need+=(cur-pos)*5; // the elevator now is on the upper floor
                }

                else // the director is (upper -> lower)
                {
                    if (pos!=child  &&  pos!=cur) // if the elevator is in the middle of the path,
                        need+=(pos-child)*5; // the elevator is on the lower floor

                    if (pos!=cur) // if the elevator is not on the upper floor,
                        need+=cost; // the elevator now is on the upper floor
                }
            }

            if (dist[cur]+need<dist[child])
            {
                dist[child]=dist[cur]+need;
                pq.push({-dist[child], child});
            }
        }
    }
}

void initialize()
{
    for (int i=0; i<=k; i++)
        dist[i]=OO, vis[i]=0, adj[i].clear();

    dist[1]=0;
}

int main()
{
    cin >> k >> n;

    initialize();

    for (int i=0; i<n; i++)
    {
        int from, to;
        cin >> from >> to;

        if (from>to)
            swap(from, to);

        adj[from].push_back(to);
        adj[to].push_back(from);
    }

    dijkstra();

    cout << dist[k];

    return 0;
}
