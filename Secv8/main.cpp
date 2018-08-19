#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;
FILE *f=fopen("secv8.in","r");
FILE *g=fopen("secv8.out","w");
int N,M,C;
int myrand()
{
    int val=rand()%10000;
    return val+(!val);
}
struct treap
{
    int sz;
    bool lazy;
    int k,p;
    treap *l,*r;
    treap(int key,int prio,treap *t1,treap *t2,int s)
    {
        k=key;
        p=prio;
        l=t1;
        r=t2;
        sz=s;
        lazy=0;
    }
}*T,*nill;
void refrrev(treap* &T)
{
    if(T==nill||!T->lazy)return ;
    swap(T->l,T->r);
    T->lazy=0;
    T->l->lazy^=1;
    T->r->lazy^=1;
}
void refrsz(treap* &T)
{
    if(T==nill)return ;
    T->sz=T->l->sz+T->r->sz+1;
}
treap* join(treap* &T1,treap* &T2)
{
    refrrev(T1);
    refrrev(T2);
    if(T1==nill)return T2;
    if(T2==nill)return T1;
    if(T1->p>T2->p){T1->r=join(T1->r,T2);refrsz(T1);return T1;}
    T2->l=join(T1,T2->l);refrsz(T2);return T2;
}
pair<treap*,treap*> split(treap* &T,int pos)
{
    refrrev(T);
    if(T==nill)return {nill,nill};
    pair<treap*,treap*> ans;
    if(T->l->sz+1<=pos)
    {
        ans.first=T;
        pair<treap*,treap*> aux;
        aux=split(T->r,pos-T->l->sz-1);
        ans.second=aux.second;
        ans.first->r=aux.first;
    }
    else
    {
        ans.second=T;
        pair<treap*,treap*> aux;
        aux=split(T->l,pos);
        ans.first=aux.first;
        ans.second->l=aux.second;
    }
    refrsz(ans.first);
    refrsz(ans.second);
    return ans;
}
void ins(treap* &T,int val,int prio,int poz)
{
    pair<treap*,treap*> tmp=split(T,poz-1);
    treap* ceva=new treap(val,prio,nill,nill,1);
    T=join(tmp.first,ceva);
    T=join(T,tmp.second);
}
int fi(treap* &T,int x)
{
    refrrev(T);
    if(T->l->sz+1==x)return T->k;
    if(T->l->sz+1>x)return fi(T->l,x);
    return fi(T->r,x-T->l->sz-1);
}
void M2(int x,int y)
{
    pair<treap*,treap*> tmp=split(T,y);
    pair<treap*,treap*> aux=split(tmp.first,x-1);
    aux.second->lazy^=1;
    T=join(aux.first,aux.second);
    T=join(T,tmp.second);
}
void M3(int x,int y)
{
    pair<treap*,treap*> tmp=split(T,y);
    pair<treap*,treap*> aux=split(tmp.first,x-1);
    T=join(aux.first,tmp.second);
}
void afis(treap* &T)
{
    refrrev(T);
    if(T==nill)return ;
    afis(T->l);
    fprintf(g,"%d ",T->k);
    afis(T->r);
}
int main()
{
    srand(time(NULL));
    T=nill=new treap(0,0,NULL,NULL,0);
    fscanf(f,"%d %d\n",&N,&M);
    for(int i=1;i<=N;i++)
    {
        int x,y;
        fscanf(f,"%c",&C);
        if(C=='I')
        {
            fscanf(f,"%d %d\n",&x,&y);
            ins(T,y,myrand(),x);
        }
        else if(C=='A')
        {
            fscanf(f,"%d\n",&x);
            fprintf(g,"%d\n",fi(T,x));
        }
        else if(C=='R')
        {
            fscanf(f,"%d %d\n",&x,&y);
            M2(x,y);
        }
        else if(C=='D')
        {
            fscanf(f,"%d %d\n",&x,&y);
            M3(x,y);
        }
    }
    afis(T);
    fclose(f);
    fclose(g);
    return 0;
}
