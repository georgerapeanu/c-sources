#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
FILE *f=fopen("bilete.in","r");
FILE *g=fopen("bilete.out","w");
int N,K;
set <int> S;
int V;
void eval()
{
    int cf1,cf2,cf3,cf4,cf5,cf6;
    cf1=V/100000;
    cf2=(V/10000)%10;
    cf3=(V/1000)%10;
    cf4=(V/100)%10;
    cf5=(V/10)%10;
    cf6=V%10;
    if(K==1)
    {
        int nr=cf5*10+N-cf6+1;
        if(S.find(nr)==S.end())
            S.insert(V);
    }
    else if(K==2)
    {
        int a,b;
        if(cf3*10+(N-cf4+1)<cf5*10+(N-cf6+1))
        {
            a=cf3*10+(N-cf4+1);
            b=cf5*10+(N-cf6+1);
        }
        else
        {
            a=cf5*10+(N-cf6+1);
            b=cf3*10+(N-cf4+1);
        }
        if(S.find(a*100+b)==S.end())
            S.insert(V);
    }
    else
    {
        int A[3];
        A[0]=cf1*10+(N-cf2+1);
        A[1]=cf3*10+(N-cf4+1);
        A[2]=cf5*10+(N-cf6+1);
        sort(A,A+3);
        if(S.find(10000*A[0]+100*A[1]+A[2])==S.end())
            S.insert(V);
    }
}
void btr(int l,int c,int K)
{
    if(!K)
       eval();
    else if(l==N+1)
        ;
    else
    {
        V=V*100+10*l+c;
        btr(l+c/N,c%N+1,K-1);
        V/=100;
        btr(l+c/N,c%N+1,K);
    }
}
int main()
{
    fscanf(f,"%d%d",&N,&K);
    btr(1,1,K);
    for(auto it:S)
        fprintf(g,"%d\n",it);
    fclose(f);
    fclose(g);
    return 0;
}
