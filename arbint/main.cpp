#include <algorithm>
#include <cstdio>
#define mij(A,B) (A+B)/2
using namespace std;
FILE *f=fopen("arbint.in","r");
FILE *g=fopen("arbint.out","w");
int start,finish,val,AINT[10000000],i,N,M,poz;
bool c;
void u(int nod,int st,int dr,int pos,int val){
    if(st > pos || dr < pos){
        return ;
    }

    if(st == dr){
        AINT[nod] = val;
        return ;
    }

    int mid = (st + dr) / 2;
    u(nod * 2,st,mid,pos,val);
    u(nod * 2 + 1,mid + 1,dr,pos,val);
    AINT[nod] = max(AINT[2 * nod],AINT[2 * nod + 1]);
}

int q(int nod,int st,int dr,int S,int D){
    if(dr < S || st > D){
        return 0;
    }

    if(S <= st && dr <= D){
        return AINT[nod];
    }
    int mid = (st + dr) / 2;
    return max(q(nod * 2,st,mid,S,D),q(nod * 2 + 1,mid + 1,dr,S,D));
}

int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        poz=i;
        u(1,1,N,poz,val);
    }
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d",&c);
        if(!c)
        {
            fscanf(f,"%d %d",&start,&finish);
            fprintf(g,"%d\n",q(1,1,N,start,finish));
        }
        else
        {
            fscanf(f,"%d %d",&poz,&val);
            u(1,1,N,poz,val);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
