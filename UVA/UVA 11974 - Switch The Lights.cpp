// Problem: UVA 11974 - Switch The Lights
// Tags: Dynamic Programming, Bit mask
// Author: Khaled Farhat
// Solution:
// - The problem is, we have n lamps and initially they are all turned on, and we have m switches, each switch affects a subset of the lamp,
//   we are asked what is minimal number f switches required to turn off all lights.
//
// - We will use dynamic programming to solve this problem, since there are many overlaps,
//   the state is: (index, mask).
//   - index will denote to the current switch.
//   - mask will help us to know which lamps are terned on, the ith bit in the mask is set to 1 if the ith lamp is turned on,
//   each time we have two choices, either using the switch or not using it,
//   if we used it, we must flip all bits in mask, that are affected by the current switch
//
// Time Complexity: O(m * (2^n))

#include <bits/stdc++.h>
using namespace std;

const int MAX=109;
const int OO=1e4+4;
int n, m, affected[MAX], memo[MAX][(1<<15)];

int dp(int i, int mask) {
    if (i==m) { // we reached the end
        if (mask) { // invalid case, some lamps are turned on
            return OO;
        }

        return 0; // base case
    }

    int& ret=memo[i][mask]; // check that we have not visited this state before
    if (ret!=-1) {
        return ret;
    }

    ret=OO;
    ret=min(ret, 1+dp(i+1, (mask^affected[i]))); // use and flip all bits that are set in affected[i]
    ret=min(ret, dp(i+1, mask)); // do not use

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    for (int test=1; test<=t; ++test) {
        cin >> n >> m;
        for (int i=0; i<m; ++i) {
            affected[i]=0;
        }

        for (int i=0; i<m; ++i) {
            for (int j=0; j<n; ++j) {
                bool bit;
                cin >> bit;

                if (bit) {
                    affected[i] |= (1<<j); // set the jth bit to 1
                }
            }
        }

        int startMask=0;
        for (int i=0; i<n; ++i) {
            startMask |= (1<<i); // initially, all lamps are turned on
        }

        memset(memo, -1, sizeof memo);
        int ans=dp(0, startMask);

        cout << "Case " << test << ": ";
        if (ans==OO)        cout << "IMPOSSIBLE\n";
        else                cout << ans << "\n";
    }

    return 0;
}
