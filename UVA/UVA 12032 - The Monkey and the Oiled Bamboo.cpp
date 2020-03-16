// Problem: UVA 12032 - The Monkey and the Oiled Bamboo
// Tags: Binary Search
// Author: Khaled Farhat
// Solution idea:
//      - if k factor is sufficient then all factors x > k are also sufficient, hence we can do a binary search over k
//      - to check that k is sufficient, we will do a loop over the array and check that no jump is greater than k, and every
//        time we need to jump exactly k we will subtract 1 from it.

#include <bits/stdc++.h>
using namespace std;

const int MAX=1e5+9;
int n, r[MAX];

// returns 1 if k is sufficient, 0 otherwise
bool check(int k) {
    for (int i=0; i<n; ++i) {
        if (r[i+1]-r[i]>k) {
            return 0; // we cannot jump
        }
        else if (r[i+1]-r[i]==k) {
            --k;
        }
    }

    // if we succeed and made all jumps, then return 1
    return 1;
}

int BSFind(int low, int high) {
    int res=1e9;

    while (low<=high) {
        int mid=low+(high-low)/2;

        if (check(mid)) { // if mid is sufficient then all x : (x > mid) are also sufficient
            res=mid;      // so update the answer and search in [low, mid-1]
            high=mid-1;
        }
        else { // if mid is not sufficient then all x : (x<mid) are also not sufficient
            low=mid+1; // so search in range [mid+1, high]
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    for (int testCase=1; testCase<=t; ++testCase) {
        cin >> n;
        r[0]=0;
        for (int i=1; i<=n; ++i) {
            cin >> r[i];
        }

        cout << "Case " << testCase << ": " << BSFind(0, 1e8) << "\n";
    }

    return 0;
}
