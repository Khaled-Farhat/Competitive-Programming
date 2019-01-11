/**
 *  created on: 09.01.2019
 *  author: Khaled Farhat
**/



#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    unsigned long long sum=n*(1+n)/2;

    if (sum%2==0)       cout << 0;
    else                cout << 1;

    return 0;
}
