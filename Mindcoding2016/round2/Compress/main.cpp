#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
map<char,int> val;
string comp(string a)
{
    string rez;rez.clear();rez+='#';
    for(int i=1;i<6;i+=2)
    {
        int nr=16*val[a[i]]+val[a[i+1]];
        char best='0';
        for(auto it:val)
        {
            if(abs(nr-17*it.second)<abs(nr-17*val[best]))
                best=it.first;
        }
        rez+=best;
    }
    return rez;
}
int main()
{
    for(char i='0';i<='9';i++)
        val[i]=i-'0';
    for(char i='A';i<='F';i++)
        val[i]=i-'A'+10;
    int N,M;
    cin>>N>>M;
    string a;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            cin>>a;
            cout<<comp(a)<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
