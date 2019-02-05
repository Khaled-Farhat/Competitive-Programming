/**
 *  created on: 03.02.2019
 *  author: Khaled Farhat
**/



#include <iostream>
using namespace std;


    string s, t;


bool isVowel(char a)
{
    string v="aeiou";
    
    for (int i=0; i<5; i++)
        if (a==v[i])
            return 1;

    return 0;
}


int main()
{
    cin >> s >> t;

    if ( s.size()!=t.size() )
    {
        cout << "NO";
        return 0;
    }


    for (int i=0; i<s.size(); i++)
    {
        int cnt=0;
        if (  isVowel( s[i] )  )        cnt++;
        if (  isVowel( t[i] )  )        cnt++;

        if (cnt%2!=0)
        {
            cout << "NO";
            return 0;
        }
    }


    cout << "YES";

    
    return 0;
}
