#include <iostream>

using namespace std;
int N,K;
int A[100005];
void ms(int st,int dr,int valst,int valdr)
{
    if(st==dr-1)
    {
        A[st]=valst;
        return ;
    }
    if(K<=0)
    {
        for(int i=st,j=valst;i<dr;i++,j++)
        {
            A[i]=j;
        }
        return ;
    }
    int mid=(st+dr)/2,valmid=valdr-(mid-st);
    K--;K--;
    ms(st,mid,valmid+1,valdr);
    ms(mid,dr,valst,valmid);
}
int main()
{
    cin>>N>>K;
    K--;
    ms(0,N,1,N);
    if(K<0||K>0)cout<<-1;
    else for(int i=0;i<N;i++)cout<<A[i]<<" ";
    return 0;
}
