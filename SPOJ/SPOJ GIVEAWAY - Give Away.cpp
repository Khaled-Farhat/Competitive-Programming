  // Problem: SPOJ GIVEAWAY - Give Away
// Tags: Data Structures, SQRT Decomposition, Binary Search
// Author: Khaled Farhat
// Solution idea:
//      - To answer the query (how many element >=c in range), We will divide the array to sqrt(n) buckets,
//        in each bucket we will keep a vector with block's elements but in sorted order, now when we are given
//        a range [a .. b], for every bucket that are completely in the range we will get the number of elements >= c
//        using binary search over that bucket's elements, because all the vector elements are sorted, and for each bucket
//        that are not completely in range [a.. b] (there will be at most two buckets), we will just iterate over their elements
//        because there are no more than sqrt(n) elements in each bucket.
//
//      - Time complexity: n + (m * sqrt(n) * log(sqrt(n)))
//
// Sqrt Decomposition: https://cp-algorithms.com/data_structures/sqrt_decomposition.html

#include <bits/stdc++.h>
using namespace std;

const int MAX=5e5+9;
int n, sq, arr[MAX];
vector<int> v[707];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    sq=(int)sqrt(n+.0)+1;
    for (int i=0; i<n; ++i) {
        cin >> arr[i];
        v[i/sq].push_back(arr[i]);
    }

    for (int i=0; i<707; ++i) {
        sort(v[i].begin(), v[i].end());
    }

    int m;
    cin >> m;
    while (m--) {
        bool type;
        cin >> type;

        if (!type) {
            int a, b, c;
            cin >> a >> b >> c;
            --a; --b;

            int leftBucket=a/sq, rightBucker=b/sq, ans=0;
            if (leftBucket==rightBucker) {
                for (int i=a; i<=b; ++i) {
                    ans+=(arr[i]>=c);
                }
            }
            else {
                for (int i=a, en=(leftBucket+1)*sq-1; i<=en; ++i) {
                    ans+=(arr[i]>=c);
                }
                for (int i=leftBucket+1; i<=rightBucker-1; ++i) {
                    ans+=v[i].size()-(upper_bound(v[i].begin(), v[i].end(), c)-v[i].begin());
                }
                for (int i=rightBucker*sq; i<=b; ++i) {
                    ans+=(arr[i]>=c);
                }
            }

            cout << ans << "\n";
        }
        else {
            int a, b;
            cin >> a >> b;
            --a;

            int bucket=a/sq;
            for (int i=0; i<v[bucket].size(); ++i) {
                if (v[bucket][i]==arr[a]) {
                    v[bucket][i]=arr[a]=b;
                    break;
                }
            }

            sort(v[bucket].begin(), v[bucket].end());
        }
    }

    return 0;
}
