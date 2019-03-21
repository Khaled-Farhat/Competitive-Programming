/**
 *  created on: 21.03.2019
 *  author: Khaled Farhat
**/



#include <iostream>
using namespace std;

    int n, ans=0;
    string s;

int main()
{
    cin >> n >> s;

    for (int i=1; i<=s.size(); i++)
        if (s[i-1]=='2'  ||  s[i-1]=='4'  ||  s[i-1]=='6'  ||  s[i-1]=='8')
            ans+=i;

    cout << ans;

    return 0;
}
