#include <iostream>
#include <algorithm>
#define NMAX 10005
#define LL long long
#define inf 1LL<<62
using namespace std;
LL D[NMAX],N;
LL B[NMAX];
LL st,dr,l1,l2,l3;
LL L[4];
LL C[4];
int main()
{
    cin>>L[1]>>L[2]>>L[3]>>C[1]>>C[2]>>C[3];
    cin>>N;
    cin>>st>>dr;
    if(st>dr)
        swap(st,dr);
    for(int i=2;i<=N;i++)
    {
        cin>>D[i];
        B[i]=inf;
    }
    B[1]=inf;
    B[st]=0;
    l1=l2=l3=st;
    for(LL i=st+1;i<=dr;i++)
    {
        while(D[i]-D[l1]>L[1])
            l1++;
        while(D[i]-D[l2]>L[2])
            l2++;
        while(D[i]-D[l3]>L[3])
            l3++;
        if(l1!=i)
            B[i]=min(min(B[l1]+C[1],B[l2]+C[2]),B[l3]+C[3]);
        else if(l2!=i)
            B[i]=min(B[l2]+C[2],B[l3]+C[3]);
        else
            B[i]=B[l3]+C[3];
    }
    cout<<B[dr];
    return 0;
}
///3 4 5 2 3 7
///4
///1 4
///2
///7
///8
///11
/// de incercat testul
