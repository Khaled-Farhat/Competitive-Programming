// Problem: UVA 10131 - Is Bigger Smarter?
// Tags: Dynamic Programming - Longest Increasing subsequence
// Author: Khaled Farhat
// Solutions: sort the elephant by weights in non-increasing order, the task now is to find the longest
//            increasing subsequence over elephants IQs and it is now a trivial task, we will use dynamic programming.
//
// Time Complexity: O(n * n)
//
// Longest Increasing Subsequence: https://cp-algorithms.com/sequences/longest_increasing_subsequence.html

#include <bits/stdc++.h>
using namespace std;

#define     F       first
#define     S       second
typedef pair<int, int>  pi;

const int MAX=1009;
const int OO=1e9+9;
int n, dp[MAX], previous[MAX];

struct Elephant {
    Elephant() {}
    Elephant(int a, int b, int c) : weight(a), iq(b), index(c) {}

    // sort by non-increasing size, then by non-decreasing IQ
    bool operator<(const Elephant& right) {
        if (weight!=right.weight) {
            return weight>right.weight;
        }

        return iq<right.iq;
    }

    int weight, iq, index;
} elephants[MAX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int nextInput=1;
    while (cin >> elephants[nextInput].iq) {
        cin >> elephants[nextInput].weight;
        elephants[nextInput].index=nextInput;
        ++nextInput;
        ++n;
    }

    sort(elephants+1, elephants+n+1);

    int longestIncreasingSubsequence=0, lastElement=1;
    for (int i=1; i<=n; ++i) {
        dp[i]=1;
        for (int j=1; j<i; ++j) {
            if (elephants[j].iq<elephants[i].iq && elephants[j].weight>elephants[i].weight && dp[j]+1>dp[i]) {
                previous[i]=j;
                dp[i]=1+dp[j];
                if (dp[i]>longestIncreasingSubsequence) {
                    longestIncreasingSubsequence=dp[i];
                    lastElement=i;
                }
            }
        }
    }

    stack<int> ans;
    while (lastElement) {
        ans.push(elephants[lastElement].index);
        lastElement=previous[lastElement];
    }

    cout << longestIncreasingSubsequence << "\n";
    while (!ans.empty()) {
        cout << ans.top() << "\n";
        ans.pop();
    }

    return 0;
}
