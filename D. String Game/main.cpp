#include <iostream>
#include <bitset>
using namespace std;
string p,t;
int op[200005],lp,lt;
bool ok(int poz)
{
    bitset<200005> B;
    B.reset();
    for(int i=0;i<=poz;i++)
        B[op[i]-1]=1;
    int ch=0;
    for(int i=0;i<lt&&ch<lp;i++)
    {
        if(B[i]==1) continue;
        if(p[ch]==t[i]) ch++;
    }
    return ch==lp;
}
int main()
{
    cin>>t>>p;
    lt=t.size();
    lp=p.size();
    for(int i=0;i<lt;i++) cin>>op[i];
    int st=-1,dr=lt-1;
    while(st<dr)
    {
        int mid=(st+dr+1)/2;
        if(ok(mid))
            st=mid;
        else
            dr=mid-1;
    }
    cout<<st+1;
    return 0;
}
