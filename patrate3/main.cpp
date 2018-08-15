#include <cstdio>
#include <fstream>
#include <algorithm>
using namespace std;
FILE *f=fopen("patrate3.in","r");
FILE *g=fopen("patrate3.out","w");
pair <int,int> V[2005];
int H,N,i,nr,lnr,Lmax,ci,lci;
int main()
{
    fscanf(f,"%d %d",&N,&H);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&V[2*i-1].first,&V[2*i].first);
        V[2*i-1].second=1;
        V[2*i].first+=V[2*i-1].first;
        V[2*i].second=-1;
    }
    sort(V+1,V+1+2*N);
    for(i=1;i<=2*N;i++)
    {
        nr+=V[i].second;
        if(nr<H)
        {
            if(lci!=0)
            {
                lnr+=V[i].first-V[i-1].first-1;
                if(lnr>Lmax)
                {
                    ci=lci;
                    Lmax=lnr;
                }
            }
            lnr=0;
            lci=0;
        }
        else if(nr>=H)
        {
            if(lci==0)
            {lnr=1;lci=V[i].first;}
            else
                lnr+=V[i].first-V[i-1].first;
        }
    }
    fprintf(g,"%d %d",ci,Lmax);
    fclose(f);
    fclose(g);
    return 0;
}
