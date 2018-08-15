#include <iostream>
#include <cstring>
using namespace std;
char A[100005];
char B[100005];
int N,M;
int V[100005];
int lim;
int i1,i2=(1<<30);
int main()
{
    cin.getline(A+1,100005);N=strlen(A+1);N=N-(A[N]=='\n');
    cin.getline(B+1,100005);M=strlen(B+1);M=M-(B[M]=='\n');
    V[M+1]=N+1;
    for(int i=M;i>0;i--)
    {
        int ind=V[i+1]-1;
        while(ind>0&&A[ind]!=B[i])ind--;
        V[i]=max(0,ind);
    }
    lim=-1;
    for(int i=0;i<=M&&lim<=N;i++)
    {
        lim++;
        while(lim<=N&&A[lim]!=B[i])
            lim++;
        if(lim>N) break;
        int st=i+1,dr=M+1;
        while(st<dr)
        {
            int mid=(st+dr)/2;
            if(lim<V[mid])
                dr=mid;
            else
                st=mid+1;
        }
        if(i2-i1>st-i)
        {
            i2=st;i1=i;
        }
    }
    for(int i=1;i<=i1;i++)
        cout<<B[i];
    for(int i=i2;i<=M;i++)
        cout<<B[i];
    if(i1==0&&i2==M+1)
        cout<<"-";
    return 0;
}
