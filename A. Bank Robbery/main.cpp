#include <iostream>
using namespace std;
int N,st,dr,a;
int rez;
int val;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>a>>st>>dr;
    cin>>N;
    if(a<st){dr=st;st=0;}
    else if(a>dr){st=dr;dr=1000000001;}
    for(int i=1;i<=N;i++)
    {
        cin>>val;
        rez+=(st<val&&val<dr);
    }
    cout<<rez;
    return 0;
}
