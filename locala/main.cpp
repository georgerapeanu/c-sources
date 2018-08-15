#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
FILE *f=fopen("locala.in","r");
FILE *g=fopen("locala.out","w");
int NA,NB;
int N;
int A[300005];
int V[300005];
int B[300005];
int R[300005];
bool isA[300005];
bool isB[300005];
bool U[300005];
int tmp[300005];
set<int> S;
int imin,imax;
int solve1()
{
    S.clear();
    for(int i=1;i<=N;i++)if(!isA[i]&&!isB[i])S.insert(i);
    memset(tmp,0,sizeof(tmp));
    for(int i=1;i<=NA;i++)V[2*i-1]=A[i];
    for(int i=1;i<=NB;i++)V[2*i]=B[i];
    for(int i=1;i<=NA;i++)
        if((V[2*i-2]<V[2*i-1]&&V[2*i-2])||(V[2*i]<V[2*i-1]&&V[2*i]))
            return 0;
    for(int i=1;i<=NB;i++)
        if((V[2*i-1]>V[2*i]&&V[2*i-1])||(V[2*i]<V[2*i+1]&&V[2*i+1]))
            return 0;
    int len=max(2*NA-1,2*NB);
    for(int i=1;i<len;i++)
    {
        int x=V[i],y=V[i+1];
        if(x>y)swap(x,y);
        tmp[x]++;
        tmp[y+1]--;
    }
    for(int i=1;i<=N;i++)
    {
        tmp[i]+=tmp[i-1];
        if(!isA[i]&&!isB[i]&&!tmp[i])return 0;
    }
    R[0]=1;R[1]=V[1];
    for(int i=1;i<len;i++)
    {
        int x,y;
        x=V[i];y=V[i+1];
        if(x<y)
        {
            while(S.lower_bound(x)!=S.end()&&*S.lower_bound(x)<=y)
            {
                R[++R[0]]=*S.lower_bound(x);
                S.erase(S.lower_bound(x));
            }
            R[++R[0]]=V[i+1];
        }
        else
        {
            int st=R[0];
            while(S.lower_bound(y)!=S.end()&&*S.lower_bound(y)<=x)
            {
                R[++R[0]]=*S.lower_bound(y);
                S.erase(S.lower_bound(y));
            }
            int dr=R[0];
            if(st<dr)reverse(R+st+1,R+dr+1);
            R[++R[0]]=V[i+1];
        }
    }
    return 1;
}
int solve2()
{
    S.clear();
    for(int i=1;i<=N;i++)if(!isA[i]&&!isB[i])S.insert(i);
    memset(tmp,0,sizeof(tmp));
    for(int i=1;i<=NB;i++)V[2*i-1]=B[i];
    for(int i=1;i<=NA;i++)V[2*i]=A[i];
    for(int i=1;i<=NB;i++)
        if((V[2*i-2]>V[2*i-1]&&V[2*i-2])||(V[2*i]>V[2*i-1]&&V[2*i]))
            return 0;
    for(int i=1;i<=NA;i++)
        if((V[2*i-1]<V[2*i]&&V[2*i-1])||(V[2*i+1]<V[2*i]&&V[2*i+1]))
            return 0;
    int len=max(2*NA,2*NB-1);
    for(int i=1;i<len;i++)
    {
        int x=V[i],y=V[i+1];
        if(x>y)swap(x,y);
        tmp[x]++;
        tmp[y+1]--;
    }
    for(int i=1;i<=N;i++)
    {
        tmp[i]+=tmp[i-1];
        if(!isA[i]&&!isB[i]&&!tmp[i])return 0;
    }
    R[0]=1;R[1]=V[1];
    for(int i=1;i<len;i++)
    {
        int x,y;
        x=V[i];y=V[i+1];
        if(x<y)
        {
            while(S.lower_bound(x)!=S.end()&&*S.lower_bound(x)<=y)
            {
                R[++R[0]]=*S.lower_bound(x);
                S.erase(S.lower_bound(x));
            }
            R[++R[0]]=V[i+1];
        }
        else
        {
            int st=R[0];
            while(S.lower_bound(y)!=S.end()&&*S.lower_bound(y)<=x)
            {
                R[++R[0]]=*S.lower_bound(y);
                S.erase(S.lower_bound(y));
            }
            int dr=R[0];
            if(st<dr)reverse(R+st+1,R+dr+1);
            R[++R[0]]=V[i+1];
        }
    }
    return 1;
}
int main()
{
    fscanf(f,"%d %d %d",&N,&NA,&NB);
    imin=1;imax=N;
    if(NA+NB<2){fprintf(g,"-1");return 0;}
    if(NA+NB>N||NA>(N/2+(N%2))||NB>(N/2+(N%2))){fprintf(g,"-1");return 0;}
    for(int i=1;i<=NA;i++){fscanf(f,"%d",&A[i]);isA[A[i]]=1;}
    for(int i=1;i<=NB;i++){fscanf(f,"%d",&B[i]);isB[B[i]]=1;}
    if(N==1)
    {
        if(isA[1]&&isB[1])fprintf(g,"1");
        else fprintf(g,"-1");
        return 0;
    }
    for(int i=1;i<=N;i++)if(isA[i]&&isB[i]){fprintf(g,"-1");return 0;}
    sort(A+1,A+1+NA);
    sort(B+1,B+1+NB);
    if(abs(NA-NB)>1){fprintf(g,"-1");return 0;}
    if(abs(NA-NB)==1)
    {
        if(NA>NB)
        {
            int tmp=solve1();
            if(tmp==0)
            {
                fprintf(g,"-1");
                return 0;
            }
            for(int i=1;i<=N;i++)fprintf(g,"%d ",R[i]);return 0;
        }
        else
        {
            int tmp=solve2();
            if(tmp==0)
            {
                fprintf(g,"-1");
                return 0;
            }
            for(int i=1;i<=N;i++)fprintf(g,"%d ",R[i]);return 0;
        }
    }
    else
    {
        int a=solve1();
        if(a)for(int i=1;i<=N;i++)fprintf(g,"%d ",R[i]);
        else
        {
            int b=solve2();
            if(b)for(int i=1;i<=N;i++)fprintf(g,"%d ",R[i]);
            else fprintf(g,"-1");
        }
        return 0;
    }
    return 0;
}
