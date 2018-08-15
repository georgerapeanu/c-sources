#include <iostream>
#include <map>
using namespace std;
map<string,int> M;
int N;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        string a;
        cin>>a;
        if(M[a])cout<<"YES\n";
        else cout<<"NO\n";
        M[a]=1;
    }
    return 0;
}
