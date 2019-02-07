/**
 *  created on: 07.02.2019
 *  author: Khaled Farhat
**/



#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


    int n, m, k, a[100002];
    vector <int> v;


int main()
{
    cin >> n >> m >> k;

    for (int i=0; i<n; i++)
        cin >> a[i];



    for (int i=1; i<n; i++)
        v.push_back(a[i]-a[i-1]-1);

    sort(v.begin(), v.end());



    int ans=n;

    for (int i=0; i<n-k; i++)
        ans+=v[i];

    cout << ans;


    return 0;
}
