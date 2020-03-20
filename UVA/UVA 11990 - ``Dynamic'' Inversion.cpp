// Problem: UVA 11990 - ``Dynamic'' Inversion
// Tags: Data Structures, SQRT Decomposition, Binary Search
// Author: Khaled Farhat
// Solution idea:
//      - When we remove an integer i from the array, we will decrease the answer by
//          - the number of indexes j < i : a[j] > a[i]
//          - the number of indexes j > i : a[j] < a[i]
//      - So we need a data structure to perform three types of operations:
//          - count how many integers greater than k in range [L .. R]
//          - count how many integers less than k in rage [L .. R]
//          - update an element in the array
//      - We will divide the array to SQRT(n) blocks, each block will have a vector contains all that block elements in a sorted order
//          - Now to answer the first two types of operations, we will iterate over the blocks that are completely
//            in range [L .. R] and we will use binary search to count the the number of elements greater than or less
//            than k (because the elements are sorted), there will be no more than sqrt(n) blocks and for each block we
//            will do a binary search over its elements, so the complexity will be O(Sqrt(n) * log(sqrt(n))),
//            and for subranges that are not completely in a block we will just iterate over them (there will be
//            no more than sqrt(n) so we will iterate over them in O(sqrt(n)).
//          - The third operation we will set a[i] to -1 and just remove a[i] from its block's vector in O(sqrt(n))
//
//      - Total complexity for each test case is: O(n + (m * Sqrt(n) * log(sqrt(n))))
//
// Sqrt Decomposition: https://cp-algorithms.com/data_structures/sqrt_decomposition.html
// the problem can also be solved using segment tree and binary indexed tree

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

template<class key, class cmp = std::less<key>>
using ordered_set=tree<key, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long       ll;

const int MAX=2e5+9;
int n, m, sq, a[MAX], idx[MAX];
vector<int> v[450];
ordered_set<int> s;
ll ans;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> n) {
        ans=0;
        s.clear();
        for (int i=0; i<450; ++i) {
            v[i].clear();
        }

        cin >> m;
        sq=(int)sqrt(n+.0)+1;
        for (int i=0; i<n; ++i) {
            cin >> a[i];
            idx[a[i]]=i;

            ans+=s.size()-s.order_of_key(a[i]);
            v[i/sq].push_back(a[i]);
            s.insert(a[i]);
        }

        for (int i=0; i<450; ++i) {
            sort(v[i].begin(), v[i].end());
        }

        while (m--) {
            cout << ans << "\n";
            int p;
            cin >> p;

            // update
            int blockToEdit=idx[p]/sq;
            for (int i=0; i<v[blockToEdit].size(); ++i) {
                if (v[blockToEdit][i]==p) {
                    a[idx[p]]=-1;
                    v[blockToEdit].erase(v[blockToEdit].begin()+i);
                    break;
                }
            }
            sort(v[blockToEdit].begin(), v[blockToEdit].end());

            // subtract # of greater than p in range [1 .. idx[p]]
            if (idx[p]) {
                int l=0, r=idx[p]-1,
                    blockLeft=l/sq, blockRight=r/sq;

                if (blockLeft==blockRight) {
                    for (int i=l; i<=r; ++i) {
                        ans-=(a[i]>p);
                    }
                }
                else {
                    for (int i=l, en=min(n-1, (blockLeft+1)*sq-1); i<=en; ++i) {
                        ans-=(a[i]>p);
                    }
                    for (int i=blockLeft+1; i<=blockRight-1; ++i) {
                        ans-=v[i].size()-(upper_bound(v[i].begin(), v[i].end(), p)-v[i].begin());
                    }
                    for (int i=blockRight*sq; i<=r; ++i) {
                        ans-=(a[i]>p);
                    }
                }
            }

            // subtract # of less than p in range [idx[p]+1 .. n-1]
            if (idx[p]!=n-1) {
                int l=idx[p]+1, r=n-1,
                    blockLeft=l/sq, blockRight=r/sq;

                if (blockLeft==blockRight) {
                    for (int i=l; i<=r; ++i) {
                        ans-=(a[i]!=-1 && a[i]<p);
                    }
                }
                else {
                    for (int i=l, en=min(n-1, (blockLeft+1)*sq-1); i<=en; ++i) {
                        ans-=(a[i]!=-1 && a[i]<p);
                    }
                    for (int i=blockLeft+1; i<=blockRight-1; ++i) {
                        ans-=(lower_bound(v[i].begin(), v[i].end(), p)-v[i].begin());
                    }
                    for (int i=blockRight*sq; i<=r; ++i) {
                        ans-=(a[i]!=-1 && a[i]<p);
                    }
                }
            }
        }
    }

    return 0;
}
