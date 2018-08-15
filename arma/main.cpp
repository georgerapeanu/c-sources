#include <cstdio>
#include <iostream>
#include <vector>
#include <bitset>
#define NMAX 10001
#define PMAX 50001
using namespace std;
FILE *f=fopen("arma.in","r");
FILE *g=fopen("arma.out","w");
int c,N,val,cval;
int V[80001],A[NMAX];
vector<int> P;
bitset<PMAX> B;
long long rez;
int lpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)
            p*=b;
        b*=b;
        e/=2;
    }
    return p;
}
int gcd(int a,int b)
{
    if(!b)
        return a;
    return gcd(b,a%b);
}
int main()
{
    B[0]=B[1]=1;
    for(long long i=2;i*i<=PMAX;i++)
    {
        if(!B[i])
        {
            for(long long j=i*i;j<=PMAX;j+=i)
                B[j]=1;
        }
    }
    for(long long i=2;i<=PMAX;i++)
    {
        if(!B[i])
        {
            P.push_back(i);
        }
    }
   /// cout<<P.size();
    fscanf(f,"%d%d",&c,&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        cval=val;
        int ind=0;
        for(vector<int>::iterator it=P.begin();it!=P.end()&&*it<=val&&val!=1;it++,ind++)
        {
            V[ind]=0;
            while(val%(*it)==0)
            {
                val/=(*it);
                V[ind]++;
            }
            if(V[ind])
                A[i]=gcd(A[i],V[ind]);
        }
        if(val!=1)
        {
            rez+=cval;
            A[i]=1;
        }
        else
        {
            int nr=1;
            for(int j=0;j<ind;j++)
            {
                if(V[j])
                    nr*=lpow(P[j],V[j]/A[i]);
            }
            rez+=nr;
        }
    }
    if(c==1)
        fprintf(g,"%lld",rez);
    else
        for(int i=1;i<=N;i++)
            fprintf(g,"%d\n",A[i]);
    fclose(f);
    fclose(g);
    return 0;
}
