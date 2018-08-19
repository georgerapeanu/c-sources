#include <iostream>

using namespace std;
int grundy[61];
int unr,sum;
int main()
{
    unr=0;
    sum=1;
    for(int i=1;i<=60;i++)
    {
        if(sum==i)
        {
            unr++;
            sum+=unr+1;
        }
        grundy[i]=unr;
    }
    int N,val;
    int rez=0;
    cin>>N;
    for(;N;N--)
    {
        cin>>val;
        rez^=grundy[val];
    }
    cout<<(rez!=0 ? "NO":"YES");
    return 0;
}
