#include <iostream>
#include <cstring>
using namespace std;
char A[100005];
char B[100005];
int F[100005];
int N,M;
int nr,j;
int main()
{
    cin.getline(A+1,100005);N=strlen(A+1);N-=(A[N]=='\n');
    cin.getline(B+1,100005);M=strlen(B+1);M-=(B[M]=='\n');
    for(int i=2;i<=M;i++)
    {
        int k=F[i-1];
        while(k&&B[k+1]!=B[i])k=F[k];
        if(B[k+1]==B[i])k++;
        F[i]=k;
    }
    for(int i=1;i<=N;i++)
    {
        if(A[i]==B[j+1]||A[i]=='?')j++;
        else
        {
            while(j&&B[j+1]!=A[i])j=F[j];
            if(B[j+1]==A[i])j++;
        }
        if(j==M){nr++;j=F[j];}
    }
    cout<<nr;
    return 0;
}
