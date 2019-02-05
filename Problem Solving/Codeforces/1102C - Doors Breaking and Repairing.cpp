/**
 *  created on: 09.01.2019
 *  author: Khaled Farhat
**/



#include <iostream>
#include <algorithm>
using namespace std;


    int n, x, y, door=0, arr[105];


int main()
{
    cin >> n >> x >> y;

    
    if (x>y)
    {
        cout << n;
        return 0;
    }


    for (int i=0; i<n; i++)
        cin >> arr[i];

    
    sort(arr, arr+n);


    for (int i=0; i<n; i++)
    {
        arr[i]=max(0, arr[i]-x);

        if (arr[i]==0)
        {
            door++;
            arr[i+1]+=y;
            sort(arr, arr+n);
        }
    }

    
    cout << door;

    
    return 0;
}
