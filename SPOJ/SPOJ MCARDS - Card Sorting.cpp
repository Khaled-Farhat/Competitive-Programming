// Problem: SPOJ MCARDS - Card Sorting
// Tags: Dynamic Programming, Longest Increasing subsequence
// Author: Khaled Farhat
// Solution:
//      - The problem is, we are given n pairs, each pair represent a card, it has a type and a value.
//        The goal is to change the positions of the minimum number of cards so that all cards of the same type
//        are in the same group (they are all behind each other), and all cards values in the same group are increasing.
//      - Let's solve a simpler version of the problem, let's consider that all cards have the same type,
//        we want to minimize the number of cards that we will change their position,
//        that it is equivalent to maximize the number of cards that we will not change their positions,
//        because if we have not changed the positions of k cards, it is trivial to see that we must change the
//        positions of the rest n-k cards, so maximizing k will bring us the optimal solution.
//      - Observation: the maximum number of cards that we will not change their positions is the length of the longest
//                     increasing subsequence.
//      - We will go back to the original problem, observe that the number of cards types is at most 4, so we will simply try all
//        permutations of sorting the groups.
//        we can implement that by considering the card type as the first indicator that will tell us if a card is greater than other.
//        Ex: if the permutation was (4 1 2 3), then we will consider that a card of type 2, is greater than a card of type 4,
//        so the problem now is to find the longest increasing subsequence over pairs and it is a trivial task with a bit of modification.
//
// Time Complexity: O( (2 ^ C) * n * log(n) ), where C is the number of types and n is the total number of cards.
//
// Longest Increasing Subsequence: https://cp-algorithms.com/sequences/longest_increasing_subsequence.html

#include <bits/stdc++.h>
using namespace std;

#define     F       first
#define     S       second
typedef pair<int, int>  pi;

const int OO=1e9+9;
const int MAX=409;
int c, n, position[6];
pi dp[MAX], a[MAX];

bool compare(const pi& p1, const pi& p2) {
    if (p1.F!=p2.F) {
        return position[p1.F]<position[p2.F];
    }

    return p1.S<p2.S;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> c >> n;
    n*=c;
    for (int i=1; i<=n; ++i)    cin >> a[i].F >> a[i].S;

    vector<int> permutation;
    for (int i=1; i<=c; ++i)    permutation.push_back(i);

    int longestInceasingSubsequence=0;
    dp[0]={0, 0};
    position[0]=-1;
    position[5]=5;
    do {
        for (int i=1; i<=n; ++i)    dp[i]={5, 5};
        for (int i=0; i<c; ++i)     position[permutation[i]]=i;

        for (int i=1; i<=n; ++i) {
            int currentLength=upper_bound(dp, dp+n+1, a[i], compare)-dp;
            longestInceasingSubsequence=max(longestInceasingSubsequence, currentLength);
            dp[currentLength]=a[i];
        }

    } while (next_permutation(permutation.begin(), permutation.end()));

    cout << n-longestInceasingSubsequence;

    return 0;
}
