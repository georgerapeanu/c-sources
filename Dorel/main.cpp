#include <cstdio>
#include <iostream>
#include <cstring>
#include <unordered_set>
#define x first
#define y second
#define M1 10657
#define M2 10651
#define I1 3094
#define I2 4123
#define NMAX 10000
using namespace std;
FILE *f=fopen("dorel.in","r");
FILE *g=fopen("dorel.out","w");
unordered_set<int> S;
char A[2*NMAX+5];
char B[2*NMAX+5];
char C[NMAX+5];
int N,Q,lA,lB;
typedef pair<int,int> has;
int st[NMAX+5];
int dr[NMAX+5];
int sti[NMAX+5],len=0;
int cod(has a)
{
    return a.x*10000+a.y;
}
has lgpow(has b,int e)
{
    has p={1,1};
    while(e)
    {
        if(e&1){p.x=(1LL*p.x*b.x)%M1;p.y=(1LL*p.y*b.y)%M2;}
        b.x=(1LL*b.x*b.x)%M1;
        b.y=(1LL*b.y*b.y)%M2;
        e>>=1;
    }
    return p;
}
int rm(int num,int mod)
{
    return ((num%mod)+mod)%mod;
}
bool ok(int L)
{
    has st,dr;st=dr={0,0};
    has e=lgpow({31,31},L);
    has f=lgpow({31,31},L-1);
    S.clear();
    for(int i=1;i<=L;i++)
    {
        st.x=rm(st.x*31+A[i]-'a',M1);
        st.y=rm(st.y*31+A[i]-'a',M2);
    }
    for(int i=2*L+1;i>L+1;i--)
    {
        dr.x=rm(dr.x*31+A[i]-'a',M1);
        dr.y=rm(dr.y*31+A[i]-'a',M2);
    }
    for(int i=L+1;i+L<=2*lA+1;i++)
    {
        if(st==dr)
        {
            has c={0,0};
            c.x=rm(st.x*31+A[i]-'a',M1);
            c.y=rm(st.y*31+A[i]-'a',M2);
            S.insert(cod(c));
        }
        st.x=rm(st.x*31+A[i]-'a'-e.x*(A[i-L]-'a'),M1);
        st.y=rm(st.y*31+A[i]-'a'-e.y*(A[i-L]-'a'),M2);
        dr.x=rm((dr.x-A[i+1]+'a')*I1+f.x*(A[i+L+1]-'a'),M1);
        dr.y=rm((dr.y-A[i+1]+'a')*I2+f.y*(A[i+L+1]-'a'),M2);
    }
    st=dr={0,0};
    for(int i=1;i<=L;i++)
    {
        st.x=rm(st.x*31+B[i]-'a',M1);
        st.y=rm(st.y*31+B[i]-'a',M2);
    }
    for(int i=2*L+1;i>L+1;i--)
    {
        dr.x=rm(dr.x*31+B[i]-'a',M1);
        dr.y=rm(dr.y*31+B[i]-'a',M2);
    }
    for(int i=L+1;i+L<=2*lB+1;i++)
    {
        if(st==dr)
        {
            has c={0,0};
            c.x=rm(st.x*31+B[i]-'a',M1);
            c.y=rm(st.y*31+B[i]-'a',M2);
            if(S.find(cod(c))!=S.end())return 1;
        }
        st.x=rm(st.x*31+B[i]-'a'-e.x*(B[i-L]-'a'),M1);
        st.y=rm(st.y*31+B[i]-'a'-e.y*(B[i-L]-'a'),M2);
        dr.x=rm((dr.x-B[i+1]+'a')*I1+f.x*(B[i+L+1]-'a'),M1);
        dr.y=rm((dr.y-B[i+1]+'a')*I2+f.y*(B[i+L+1]-'a'),M2);
    }
    return 0;
}
int main()
{
    fgets(C+1,NMAX+5,f);
    N=strlen(C+1);N-=(C[N]=='\n');
    for(int i=1;i<=N;i++)
    {
        while(len&&C[sti[len]]<C[i])len--;
        if(!len)st[i]=1;
        else st[i]=sti[len];
        sti[++len]=i;
    }
    len=0;
    for(int i=N;i;i--)
    {
        while(len&&C[sti[len]]>C[i])len--;
        if(!len)dr[i]=N;
        else dr[i]=sti[len];
        sti[++len]=i;
    }
    fscanf(f,"%d",&Q);
    for(int i=1;i<=Q;i++)
    {
        int k;
        fscanf(f,"%d",&k);
        lA=0;lB=0;
        for(int j=1;j<=N;j++)
        {
            if(j>=st[k]&&j<=dr[k])
            {
                lB++;
                B[2*lB-1]='z'+1;
                B[2*lB]=C[j];
            }
            else
            {
                lA++;
                A[2*lA-1]='z'+1;
                A[2*lA]=C[j];
            }
        }
        A[2*lA+1]=B[2*lB+1]='{';
        int lo=0,hi=min(lA,lB);
        while(lo<hi)
        {
            int mid=(lo+hi+1)/2;
            if(ok(mid))
            {
                lo=mid;
            }
            else
            {
                hi=mid-1;
            }
        }
        fprintf(g,"%d ",hi);
    }
    fclose(f);
    fclose(g);
    return 0;
}
