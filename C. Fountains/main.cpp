#include <cstdio>
#include <iostream>
#include <algorithm>
#define x first
#define y second
using namespace std;
int N,C,D;
int a,b,rez;
pair<int,int> A[100005];
pair<int,int> B[100005];
int maxA[100005];
int maxB[100005];
char c;
int ind1,ind2;
int main()
{
    scanf("%d %d %d\n",&N,&C,&D);
    for(int i=1;i<=N;i++)
    {
        scanf("%d %d %c\n",&a,&b,&c);
        if(c=='C')
        {
            A[++A[0].x].x=b;
            A[A[0].x].y=a;
        }
        else
        {
            B[++B[0].x].x=b;
            B[B[0].x].y=a;
        }
    }
    sort(A+1,A+1+A[0].x);
    sort(B+1,B+1+B[0].x);
    for(int i=1;i<=A[0].x;i++)
        maxA[i]=max(maxA[i-1],A[i].y);
    for(int i=1;i<=B[0].x;i++)
        maxB[i]=max(maxB[i-1],B[i].y);
    A[++A[0].x].x=(1<<30);
    B[++B[0].x].x=(1<<30);
    for(int i=1;i<=A[0].x;i++)
    {
        if(A[i].x>C){ind1=i-1;break;}
        int st=0,dr=i-1;
        while(st<dr)
        {
            int mid=(st+dr+1)/2;
            if(A[mid].x+A[i].x<=C)
                st=mid;
            else
                dr=mid-1;
        }
        if(st==0)continue;
        rez=max(A[i].y+maxA[st],rez);
    }
    for(int i=1;i<=B[0].x;i++)
    {
        if(B[i].x>D)
        {
            ind2=i-1;
            break;
        }
        int st=0,dr=i-1;
        while(st<dr)
        {
            int mid=(st+dr+1)/2;
            if(B[mid].x+B[i].x<=D)
                st=mid;
            else
                dr=mid-1;
        }
        if(st==0)continue;
        rez=max(B[i].y+maxB[st],rez);
    }
    if(ind1&&ind2)
        rez=max(maxA[ind1]+maxB[ind2],rez);
    printf("%d",rez);
    return 0;
}
