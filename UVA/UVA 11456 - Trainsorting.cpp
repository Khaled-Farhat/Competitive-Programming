// Problem: UVA 11456 - Trainsorting
// Tags: Dynamic Programming, Longest Increasing Subsequence, Longest Decreasing Subsequence
// Author: Khaled Farhat
// Solution:
//      - The problem is, you get cars one by one and each car has a weight, when you get a car,
//        you can put it either in the beginning or end of the sequence or you can refuse it at all.
//        the goal is to obtain the longest sequence such that cars weights are decreasing.
//        so we want to get the longest sequence such that ( b[1] > b[2] > b[3] > ... > b[k] )
//
//      - Observation 1: consider that you put a car of weight X on the left, then to put another car on the left
//                       it must has a weight greater than X.
//      - Observation 2: consider that you put a car of weight X on the right, then to put another car on the right
//                       it must has a weight less than X.
//      - Observation 3: consider the the car i was the first car to add, then:
//                       - all cars weights from i to the right must be decreasing.
//                       - all cars weights from i to the left must be increasing
//      - so the problem now: if we considered that i was the first car to add, the longest sequence here can be
//        obtained in the following way:
//        select the longest decreasing subsequence from n to i (it ends in i) and put those cars to the right of i,
//        select the longest increasing subsequence from n to i (it ends in i) and put those cars to the left of i.
//
//      - The problem now became trivial, it is easy to find the longest increasing subsequence using
//        dynamic programming and binary search, to find the final answer we will do a bruteforce over i
//        (bruteforce over the first car to add) and we will maximize the answer each time.
//
// Time Complexity: O(n * log(n))
//
// Longest Increasing Subsequence tutorial: https://cp-algorithms.com/sequences/longest_increasing_subsequence.html

#include <bits/stdc++.h>
using namespace std;

const int OO=1e9+9;
const int MAX=2009;
int n, a[MAX];
vector<int> dp[2];  // dp[0][k] (minimum end) of (longest increasing subsequence from n to i of length k)
                    // dp[1][k] (maximum end) of (longest decreasing subsequence from n to i of length k)

// binary search, find the first cars of weight less than val
int BSFindFirstLessThan(int val) {
    int res=1, low=0, high=n;
    while (low<=high) {
        int mid=low+(high-low)/2;
        if (dp[1][mid]<val) {
            res=mid;
            high=mid-1;
        }
        else {
            low=mid+1;
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i=1; i<=n; ++i) {
            cin >> a[i];
        }

        dp[0]=dp[1]=vector<int>(n+1);

        dp[0][0]=-OO;
        dp[1][0]=OO;
        for (int i=1; i<=n; ++i) {
            dp[0][i]=OO;
            dp[1][i]=-OO;
        }

        int ans=0;
        for (int i=n; i>=1; --i) {
            // binary search, first car of weight greater than a[i]
            int posInc=upper_bound(dp[0].begin(), dp[0].end(), a[i])-dp[0].begin();
        
            // binary search, first car of weight less than a[i]
            int posDec=BSFindFirstLessThan(a[i]);

            ans=max(ans, posInc+posDec-1);
            dp[0][posInc]=a[i];
            dp[1][posDec]=a[i];
        }

        cout << ans << "\n";
    }

    return 0;
}
