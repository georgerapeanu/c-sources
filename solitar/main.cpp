#include <cstdio>
#include <iostream>
using namespace std;
FILE *f=fopen("solitar.in","r");
FILE *g=fopen("solitar.out","w");
int N,V[100005],i,op;
bool varf[100005],capat[100005];
pair <int,int> a;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
    }
    i=N;
    while(i>0)
    {
        a=make_pair(V[i],V[i]);
        i--;
        while(a.first==V[i]-1)
            {i--;a.first++;}
        capat[a.second]=1;
        varf[a.first]=1;
        if(capat[a.first+1])
        {
            op+=1;
            capat[a.first+1]=0;
            varf[a.first]=0;
        }
        else
        {
            op+=2;
            if(a.first==N)
                op--;
        }
        if(varf[a.second-1])
        {
            capat[a.second]=0;
            varf[a.second-1]=0;
        }
    }
    if(a.first==N)
    fprintf(g,"%d",op-1);
    else
    fprintf(g,"%d",op);
    fclose(f);
    fclose(g);
    return 0;
}
