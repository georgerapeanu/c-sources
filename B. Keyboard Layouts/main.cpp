#include <iostream>
#include <map>
using namespace std;
map<char,int> M;
string a,b,c;
int main()
{
    cin>>a;
    cin>>b;
    cin>>c;
    for(int i=0;i<a.size();i++)M[a[i]]=i;
    for(auto it:c)
    {
        if(!(('a'<=it&&it<='z')||('A'<=it&&it<='Z'))){cout<<it;continue;}
        char tmp=it;
        if('A'<=tmp&&tmp<='Z')tmp-='A'-'a';
        char c=b[M[tmp]];
        if('A'<=it&&it<='Z')c+='A'-'a';
        cout<<c;
    }
    return 0;
}
