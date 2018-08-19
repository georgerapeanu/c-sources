#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;
unordered_map <string,int> D;
int A[100005];
int B[100005];
string names;
int N,M,Q;
int tata(int nod)
{
    if(A[nod]==nod) return nod;
    return A[nod]=tata(A[nod]);
}
void u(int a,int b)
{
    a=tata(a);
    b=tata(b);
    if(a==b) return;
    A[b]=a;
}
int main()
{
    cin>>N>>M>>Q;
    for(int i=1;i<=N;i++)
        {cin>>names;D[names]=i;A[i]=i;}
    for(int i=1;i<=M;i++)
    {
        int op;
        string a,b;
        cin>>op>>a>>b;
        int j,k;
        j=tata(D[a]);
        k=tata(D[b]);
        if(op==1)
        {
            if(tata(B[j])==k||tata(B[k])==j)
            {
                cout<<"NO\n";
                continue;
            }
            else
            {
                cout<<"YES\n";
                u(j,k);
                if(B[j]&&B[k]) u(B[j],B[k]);
                else if(B[k]) B[j]=B[k];
            }
        }
        else
        {
            if(j==k){cout<<"NO\n";continue;}
            cout<<"YES\n";
            if(B[j])
            {
                u(k,B[j]);
            }
            if(B[k])
            {
                u(j,B[k]);
            }
            B[j]=k;B[k]=j;
        }
    }
    for(int i=1;i<=Q;i++)
    {
        string a,b;
        cin>>a>>b;
        int j=tata(D[a]),k=tata(D[b]);
        if(j==k)
            cout<<"1\n";
        else if(tata(B[j])==k)
            cout<<"2\n";
        else
            cout<<"3\n";
    }
    return 0;
}
