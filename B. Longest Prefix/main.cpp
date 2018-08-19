#include <iostream>
#include <cstring>
using namespace std;
string a,b;
int T;
int fr[280];
int main()
{
    cin>>T;
    while(T--)
    {
        memset(fr,0,sizeof(fr));
        cin>>a>>b;
        for(auto it:b)fr[it]++;
        int rez=-1;
        for(;rez<((int)a.size())-1&&fr[a[rez+1]];rez++)
            fr[a[rez+1]]--;
        cout<<rez+1<<"\n";
    }
    return 0;
}
