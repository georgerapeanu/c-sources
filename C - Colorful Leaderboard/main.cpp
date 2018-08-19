#include <iostream>
#include <bitset>
using namespace std;
int nr,cul;
int N;
int A[105];
bitset<9> U;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        if(A[i]<400){cul+=(U[1]==0);U[1]=1;}
        else if(A[i]<800){cul+=(U[2]==0);U[2]=1;}
        else if(A[i]<1200){cul+=(U[3]==0);U[3]=1;}
        else if(A[i]<1600){cul+=(U[4]==0);U[4]=1;}
        else if(A[i]<2000){cul+=(U[5]==0);U[5]=1;}
        else if(A[i]<2400){cul+=(U[6]==0);U[6]=1;}
        else if(A[i]<2800){cul+=(U[7]==0);U[7]=1;}
        else if(A[i]<3200){cul+=(U[8]==0);U[8]=1;}
        else
            nr++;
    }
    cout<<max(1,cul)<<" "<<nr+cul;
    return 0;
}
