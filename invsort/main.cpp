#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f=fopen("invsort.in","r");
FILE *g=fopen("invsort.out","w");
int V[32005];
int tmp[32005];
int N;
void srt(int st,int dr)
{
    if(st==dr)return ;
    if(st==dr-1)
    {
        if(tmp[st]>tmp[dr]){swap(tmp[st],tmp[dr]);swap(V[st],V[dr]);fprintf(g,"%d %d\n",st,dr);}
        return ;
    }
    int mid=(st+dr)/2;
    srt(st,mid);
    srt(mid+1,dr);
    int i=mid,j=mid+1;
    while(tmp[i]&&i>=st)i--;
    while(!tmp[j]&&j<=dr)j++;
    j--;i++;
    if(i<j)
    {
        reverse(tmp+i,tmp+j+1);
        reverse(V+i,V+j+1);
        fprintf(g,"%d %d\n",i,j);
    }
}
void solve(int st,int dr)
{
    if(st==dr)return;
    if(st==dr-1)
    {
        if(V[st]>V[dr])
        {
            swap(V[st],V[dr]);
            fprintf(g,"%d %d\n",st,dr);
        }
        return ;
    }
    int mini=1<<30,maxi=0;
    for(int i=st;i<=dr;i++){mini=min(mini,V[i]);maxi=max(maxi,V[i]);}
    if(mini==maxi)return ;
    for(int i=st;i<=dr;i++)tmp[i]=(V[i]>(maxi+mini)/2);
    srt(st,dr);
    int mid=st;
    while(tmp[mid]==0)mid++;
    solve(st,mid-1);
    solve(mid,dr);

}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        tmp[i]=V[i];
    }
    solve(1,N);
    return 0;
}
