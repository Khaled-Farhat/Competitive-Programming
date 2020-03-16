// Problem: UVA 11428 - Cubes
// Tags: Binary Search
// Author: Khaled Farhat
// Solution idea:
//      - We need to find two positive integers x, y : N = (x^3) - (y^3)
//      => N + (y^3) = (x^3)
//      - We will do a bruteforce over y and find if there is such x using binary search,
//        it is sufficient to try y values that are less or equal 60 because (60^3) - (59^3) > N always

#include <bits/stdc++.h>
using namespace std;

int BSFind(int low, int high, int val) {
    while (low<=high) {
        int x=low+(high-low)/2,
            xCube=x*x*x;

        if (xCube>val) {
            high=x-1;
        }
        else if (xCube<val) {
            low=x+1;
        }
        else {
            return x;
        }
    }

    return -1; // not found
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n && n) {
        bool can=0;

        for (int y=0; y<=60; ++y) {
            int x=BSFind(0, 60, n+y*y*y);

            if (x!=-1) {
                can=1;
                cout << x << " " << y << "\n";
                break;
            }
        }

        if (!can) {
            cout << "No solution\n";
        }
    }

    return 0;
}
