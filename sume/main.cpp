#include <cmath>
#include <algorithm>
#include <cstdio>
#include <unordered_map>
#define LEN 100000000
using namespace std;
FILE *f=fopen("sume.in","r");
FILE *g=fopen("sume.out","w");
int P,N;
int V[5006];
int S[25006];
unordered_map<int,int> M;
char buff[LEN];
int ind=LEN-1;
int i32()
{
    int nr=0;
    while(buff[ind]<'0'||buff[ind]>'9')
        if(++ind>=LEN){fread(buff,1,LEN,f);ind=0;}
    while(buff[ind]>='0'&&buff[ind]<='9')
    {
        nr=nr*10+buff[ind]-'0';
        if(++ind>=LEN){fread(buff,1,LEN,f);ind=0;}
    }
    return nr;
}
bool ev(int s1,int s2,int s3)
{
    M.clear();
    int len=3;
    if((s1+s2+s3)%2!=0)return 0;
    V[1]=(s1+s2+s3)/2-s3;
    V[2]=(s1+s2+s3)/2-s2;
    V[3]=(s1+s2+s3)/2-s1;
    if(V[1]<=0||V[2]<=0||V[3]<=0)return 0;
    for(int i=1;i<=3;i++)
        for(int j=i+1;j<=3;j++)
            M[V[i]+V[j]]++;
    for(int i=1;i<=P;i++)
    {
        if(M[S[i]]==0)
        {
            V[++len]=S[i]-V[1];
            if(len>N||V[len]<=0)return 0;
            for(int i=1;i<len;i++)M[V[i]+V[len]]++;
            M[S[i]]--;
        }
        else
            {M[S[i]]--;}
    }
    return (len==N);
}
int main()
{
    P=i32();
    N=(1+sqrt(1+8*P))/2;
    if(N*(N-1)/2!=P){fprintf(g,"-1");return 0;}
    for(int i=1;i<=P;i++)S[i]=i32();
    sort(S+1,S+1+P);
    for(int i=3;i<=N;i++)
        if(ev(S[1],S[2],S[i])){fprintf(g,"%d\n",N);for(int i=1;i<=N;i++)fprintf(g,"%d ",V[i]);return 0;}
    fprintf(g,"-1");
    fclose(f);
    fclose(g);
    return 0;
}
