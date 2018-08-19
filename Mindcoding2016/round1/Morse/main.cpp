#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
string repr;
map<string,int> M;
string A[256];
string cod;
int maxim;
int main()
{
    char c;
    for(int i=1;i<=26;i++)
    {
        cin>>c>>cod;
        A[c]=cod;
    }
    int N;
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>cod;
        repr.clear();
        for(auto it:cod)
        {
            repr=repr+A[it];
        }
        M[repr]++;
        maxim=max(maxim,M[repr]);
    }
    if(maxim==1)
        cout<<-1;
    else
        cout<<maxim;
    return 0;
}
