#include <cstdio>
using namespace std;
FILE *f=fopen("suma5.in","r");
FILE *g=fopen("suma5.out","w");
struct data
{
    long long st,dr,s1,s2,lazysum;
    bool lazy;
}AINT[800005];
void propag(int nod)
{
    if(!AINT[nod].lazy)return;
    AINT[nod].s1+=AINT[nod].lazysum*(AINT[nod].dr-AINT[nod].st+1);
    AINT[nod].s2+=AINT[nod].lazysum*(AINT[nod].dr-AINT[nod].st+1)*(AINT[nod].dr-AINT[nod].st+2)/2;
    AINT[2*nod].lazy=1;AINT[2*nod].lazysum+=AINT[nod].lazysum;
    AINT[2*nod+1].lazy=1;AINT[2*nod+1].lazysum+=AINT[nod].lazysum;
    AINT[nod].lazysum=0;
    AINT[nod].lazy=0;
}
void u(int nod,int st,int dr,int val)
{
    propag(nod);
    if(AINT[nod].st>=st&&AINT[nod].dr<=dr)
    {
        AINT[nod].lazy=1;
        AINT[nod].lazysum+=val;
        propag(nod);
        return ;
    }
    if(AINT[nod].dr<st||AINT[nod].st>dr)return ;
    u(2*nod,st,dr,val);
    u(2*nod+1,st,dr,val);
    AINT[nod].s1=AINT[2*nod].s1+AINT[2*nod+1].s1;
    AINT[nod].s2=AINT[2*nod].s2+AINT[2*nod+1].s2+(AINT[2*nod].dr-AINT[2*nod].st+1)*AINT[2*nod+1].s1;
}
data q(int nod,int st,int dr)
{
    propag(nod);
    if(AINT[nod].st>dr||AINT[nod].dr<st)return {0,0,0,0,0,0};
    if(st<=AINT[nod].st&&AINT[nod].dr<=dr)
    {
        propag(nod);
        return AINT[nod];
    }
    data a,b;
    a=q(nod*2,st,dr);
    b=q(nod*2+1,st,dr);
    if(AINT[2*nod].st>dr||AINT[2*nod].dr<st)return b;
    if(AINT[2*nod+1].st>dr||AINT[2*nod+1].dr<st)return a;
    a.s1=a.s1+b.s1;
    a.s2=a.s2+b.s2+(a.dr-a.st+1)*b.s1;
    a.dr=b.dr;
    return a;
}
void build(int nod,int st,int dr)
{
    AINT[nod].st=st;
    AINT[nod].dr=dr;
    if(st==dr)
    {
        int x;
        fscanf(f,"%d",&x);
        AINT[nod].s1=AINT[nod].s2=x;
        return ;
    }
    build(nod*2,st,(st+dr)/2);
    build(nod*2+1,(st+dr)/2+1,dr);
    AINT[nod].s1=AINT[2*nod].s1+AINT[2*nod+1].s1;
    AINT[nod].s2=AINT[2*nod].s2+AINT[2*nod+1].s2+(AINT[2*nod].dr-AINT[2*nod].st+1)*AINT[2*nod+1].s1;
}
int N,M,x,y,z,c;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    build(1,1,N);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d",&c);
        if(!c)
        {
            fscanf(f,"%d %d %d",&x,&y,&z);
            u(1,x,y,z);
        }
        else
        {
            fscanf(f,"%d %d",&x,&y);
            fprintf(g,"%lld\n",q(1,x,y).s2);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
