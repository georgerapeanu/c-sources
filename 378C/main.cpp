#include <iostream>
#include <vector>
using namespace std;
vector <pair<int,char> > V;
int A[505];
int B[505];
int i,j,st,dr;
int val,L;
bool ok;
int main()
{
    cin>>N;
    for(i=1;i<=N;i++)
        cin>>A[i];
    cin>>M;
    for(j=1;j<=M;j++)
        cin>>B[j];
    for(i=1;i<=M;i++)
    {
        sum=0;
        maxim=0;
        ok=0;
        val=A[j];
        while(sum<B[i]&&j<=N)
        {
            sum+=A[j];
            if(A[j]>A[maxim])
                maxim=j;
            if(A[j]!=val)
                ok=1;
            j++;
        }
        if(!ok&&j-B[i]>1)
        {fprintf(g,"NO");return 0;}
        for(k=maxim-B[i];k)
    }
    return 0;
}
