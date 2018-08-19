#include <cstdio>
#include <vector>
using namespace std;
FILE *f=fopen("interclasare.in","r");
FILE *g=fopen("interclasare.out","w");
int A[10005];
int B[10005];
int N,M,i,cnt;
int BA[10005];
int BB[10005];
int lA,lB,j;
int PA[10005];
int PB[10005],ua,ub;
vector<int> iA,iB;
pair<int,bool> V[20005];
void interclasare()
{
    while(!iA.empty()&&!iB.empty())
    {
        if(A[*(iA.rbegin())]<=B[*(iB.rbegin())])
        {
            V[++cnt]=make_pair(*(iA.rbegin()),0);
            iA.pop_back();
        }
        else
        {
            V[++cnt]=make_pair(*(iB.rbegin()),1);
            iB.pop_back();
        }
    }
    while(!iA.empty())
    {
        V[++cnt]=make_pair(*(iA.rbegin()),0);
        iA.pop_back();
    }
    while(!iB.empty())
    {
        V[++cnt]=make_pair(*(iB.rbegin()),1);
        iB.pop_back();
    }
}
void afmaxA()
{
    int st,dr,mid,last;
    for(i=1;i<=N;i++)
    {
        st=1;
        dr=lA;
        last=0;
        while(st<=dr)
        {
            mid=(st+dr)/2;
            if(A[BA[mid]]<=A[i])
            {
                last=mid;
                st=mid+1;
            }
            else
                dr=mid-1;
        }
        PA[i]=BA[last];
        if(last+1>lA)
        {
            lA++;
            BA[lA]=i;
        }
        else
        {
            if(A[BA[last+1]]>A[i])
                BA[last+1]=i;
        }
    }
}
void afmaxB()
{
    int st,dr,mid,last;
    for(i=1;i<=M;i++)
    for(i=1;i<=M;i++)
    {
        st=1;
        dr=lB;
        last=0;
        while(st<=dr)
        {
            mid=(st+dr)/2;
            if(B[BB[mid]]<=B[i])
            {
                last=mid;
                st=mid+1;
            }
            else
                dr=mid-1;
        }
        PB[i]=BB[last];
        if(last+1>lB)
        {
            lB++;
            BB[lB]=i;
        }
        else
        {
            if(B[BB[last+1]]>B[i])
                BB[last+1]=i;
        }
    }
}
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
        fscanf(f,"%d",&A[i]);
    fscanf(f,"%d",&M);
    for(i=1;i<=M;i++)
        fscanf(f,"%d",&B[i]);
    afmaxA();
    afmaxB();
    fprintf(g,"%d\n",lA+lB);
    i=BA[lA];
    while(i)
    {
        iA.push_back(i);
        i=PA[i];
    }
    i=BB[lB];
    ua=1;
    ub=1;
    while(i)
    {
        iB.push_back(i);
        i=PB[i];
    }
    interclasare();
    for(i=1;i<=cnt;i++)
    {
        if(V[i].second==0)
        {
            for(j=ua;j<=V[i].first;j++)
                fprintf(g,"%d ",A[j]);
            ua=V[i].first+1;
        }
        else
        {
            for(j=ub;j<=V[i].first;j++)
                fprintf(g,"%d ",B[j]);
            ub=V[i].first+1;
        }
    }
    while(ua<=N)
    {
        fprintf(g,"%d ",A[ua]);
        ua++;
    }
    while(ub<=M)
    {
        fprintf(g,"%d ",B[ub]);
        ub++;
    }
    fclose(f);
    fclose(g);
    return 0;
}
