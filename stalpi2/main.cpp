#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#define val first
#define ind second.first
#define cul second.second
#define x first
#define y second
using namespace std;
FILE *f=fopen("stalpi2.in","r");
FILE *g=fopen("stalpi2.out","w");
int N,D,i,maxcul,j;
int apcul[105];
int cuplaj[10005];
pair <int,pair<int,int> > A[10005],B[10005];
pair <int,int> luate[105];
double sarma;
char c[100005];
int main()
{
    fscanf(f,"%d %d",&N,&D);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&A[i].val,&A[i].cul);
        A[i].ind=i;
        maxcul=max(A[i].cul,maxcul);
    }

    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&B[i].val,&B[i].cul);
        B[i].ind=i;
    }
    sort(A+1,A+1+N);
    sort(B+1,B+1+N);
    j=1;
    for(i=1;i<=N;i++)
    {
        while(B[j].val<=A[i].val&&j<=N)
            {apcul[B[j].cul]=j;j++;}
        if(apcul[A[i].cul])
        {
            cuplaj[i]=apcul[A[i].cul];
        }
    }
    for(i=1;i<=maxcul;i++)
        apcul[i]=0;
    j=N;
    for(i=N;i>0;i--)
    {
        while(B[j].val>=A[i].val&&j>0)
            {apcul[B[j].cul]=j;j--;}
        if(apcul[A[i].cul])
        {
            if((A[i].val-B[cuplaj[i]].val>B[apcul[A[i].cul]].val-A[i].val)||cuplaj[i]==0)
                cuplaj[i]=apcul[A[i].cul];
        }
    }
    for(i=1;i<=N;i++)
    {
        if(!luate[A[i].cul].first)
            luate[A[i].cul]=make_pair(i,cuplaj[i]);
        else
        {
            if(abs(A[luate[A[i].cul].x].val-B[luate[A[i].cul].y].val)>abs(A[i].val-B[cuplaj[i]].val))
                luate[A[i].cul]=make_pair(i,cuplaj[i]);
        }
    }
    for(i=1;i<=maxcul;i++)
    {
        if(luate[i].first)
        {
            sarma+=sqrt(double(pow(A[luate[i].first].val-B[luate[i].second].val,2)+pow(D,2)));
            luate[i]=make_pair(A[luate[i].x].ind,B[luate[i].y].ind);
        }
    }
    sprintf(c,"%f",sarma);
    j=0;
    while(c[j]!='.')
        j++;
    c[j+4]='\0';
    fputs(c,g);
    fprintf(g,"\n");
    for(i=1;i<=maxcul;i++)
    {
        if(luate[i].first)
            fprintf(g,"%d %d\n",luate[i].x,luate[i].y);
    }
    fclose(f);
    fclose(g);
    return 0;
}
