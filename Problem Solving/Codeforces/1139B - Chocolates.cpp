/**
 *  created on: 21.03.2019
 *  author: Khaled Farhat
**/



#include <iostream>
using namespace std;


    long long ans=0;
    int x=1e9+9, n, a[200009];


int main()
{
    cin >> n;
    for (int i=0; i<n; i++)
        cin >> a[i];

    for (int i=n-1; i>=0; i--)
    {
        x=max(min(a[i], x-1), 0);
        ans+=x;
    }

    cout << ans;

    return 0;
}
