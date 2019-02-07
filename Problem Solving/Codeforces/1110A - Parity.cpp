/**
 *  created on: 07.02.2019
 *  author: Khaled Farhat
**/



#include <iostream>
#include <cmath>
using namespace std;


    int a[100001], k, b;
    unsigned long long n=0;


int main()
{
    cin >> b >> k;

    for (int i=0; i<k; i++)
        cin >> a[i];

    
    unsigned long long p=1;
    
    for (int i=k-1; i>=0; i--)
    {
        n+=a[i]*p;

        p*=b;
    }

    
    if (n%2==0)     cout << "even";
    else            cout << "odd";

    
    return 0;
}
