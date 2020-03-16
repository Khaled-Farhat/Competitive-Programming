// Problem: UVA 10611 - The Playboy Chimp
// Tags: Binary Search
// Author: Khaled Farhat
// Solution idea: Binary search over indexes

#include <bits/stdc++.h>
using namespace std;

const int MAX=5e4+9;
int n, a[MAX];

// returns index of (last) (a[i] < val)
// returns -1 if not found
int BSFindPrev(int low, int high, int val) {
    int index=-1;

    while (low<=high) {
        int mid=low+(high-low)/2;

        if (a[mid]<val) { // all previous element are smaller than a[i]
            index=mid;      // so search in range [mid+1, high]
            low=mid+1;
        }
        else {
            high=mid-1; // all next elements are greater than a[i]
                        // so search in range [low, mid-1]
        }
    }

    return index;
}

// returns index of (first) (a[i] > val)
// returns -1 if not found
int BSFindNext(int low, int high, int val) {
    int index=-1;

    while (low<=high) {
        int mid=low+(high-low)/2;

        if (a[mid]>val) { // all next element are greater than a[i]
            index=mid;      // so search in range [low, mid-1]
            high=mid-1;
        }
        else {
            low=mid+1; // all previous elements are smaller than a[i]
                       // so search in range [mid+1, high]
        }
    }

    return index;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i=1; i<=n; ++i) {
        cin >> a[i];
    }

    int q;
    cin >> q;
    while (q--) {
        int val;
        cin >> val;

        int lastSmallerIndex=BSFindPrev(1, n, val),
            nextGreaterIndex=BSFindNext(1, n, val);

        if (lastSmallerIndex==-1)       cout << "X ";
        else                            cout << a[lastSmallerIndex] << " ";

        if (nextGreaterIndex==-1)       cout << "X\n";
        else                            cout << a[nextGreaterIndex] << "\n";
    }

    return 0;
}
