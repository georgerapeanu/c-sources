#include <iostream>
#include <vector>
#include <cstdlib>
#define NMAX 505
using namespace std;
int N,A[NMAX],B[NMAX];
int M,iB,st,val;
vector<pair<int,char> > V;
int j,suma,maxim;
bool ok;
void eval(int st,int dr)
{
    if(!ok&&dr-st!=0)
    {
        cout<<"NO";
        exit(0);
    }
    maxim=0;
    for(int i=st;i<=dr;i++)
    {
        if(A[i]>A[maxim]&&((i-1>=st&&A[i]>A[i-1])||(i+1<=dr&&A[i]>A[i+1])))
            maxim=i;
    }
    if(!maxim)
        return ;
    if(A[maxim]>A[maxim+1])
    {
        for(int i=maxim+1;i<=dr;i++)
            V.push_back(make_pair(maxim-st+iB,'R'));
        for(int i=maxim;i>st;i--)
            V.push_back(make_pair(i-st+iB,'L'));
    }
    else
    {
        for(int i=maxim;i>st;i--)
            V.push_back(make_pair(i-st+iB,'L'));
        for(int i=maxim+1;i<=dr;i++)
            V.push_back(make_pair(iB,'R'));
    }
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
        cin>>A[i];
    cin>>M;
    for(int i=1;i<=M;i++)
        cin>>B[i];
    st=1;iB=1;
    val=A[1];
    for(int i=1;i<=N;i++)
    {
        suma+=A[i];
        if(val!=A[i])
            ok=1;
        if(suma>B[iB])
        {
            cout<<"NO";
            return 0;
        }
        if(suma==B[iB])
        {
            eval(st,i);
            suma=0;
            maxim=0;
            val=A[i+1];
            st=i+1;
            ok=0;
            iB++;

        }
    }
    if(iB<=M)
    {
        cout<<"NO";
        return 0;
    }
    cout<<"YES\n";
    for(vector<pair<int,char> >::iterator it=V.begin();it!=V.end();it++)
        cout<<(*it).first<<" "<<(*it).second<<"\n";
    return 0;
}
