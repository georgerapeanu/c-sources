#include <iostream>
#include <cstdlib>
#include <ctime>
#define BASE 31
#define MOD 1000000007
using namespace std;
int N,M,b,d,e;
string a;
char c;
int myrand()
{
    int val=rand()%10000;
    return val+(!val);
}
struct treap{
    int st,dr;
    char k;
    int p;
    bool rev;
    int sz;
    treap *l,*r;
    treap(char key,int prio,treap* f1,treap*f2,int s)
    {
        rev=0;
        st=dr=key-'a'+1;
        k=key;
        p=prio;
        l=f1;
        r=f2;
        sz=s;
    }
}*nill,*T;
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=(1LL*b*p)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
void refrha(treap* &T)
{
    if(T==nill)return;
    T->st=((1LL*BASE*T->l->st+T->k-'a'+1)*lgpow(BASE,T->r->sz)+T->r->st);
    T->dr=((1LL*BASE*T->r->dr+T->k-'a'+1)*lgpow(BASE,T->l->sz)+T->l->dr);
}
void refrsize(treap* &T)
{
    if(T==nill)return;
    T->sz=T->l->sz+1+T->r->sz;
}
void refrrev(treap* &T)
{
     if(T==nill)return ;
     if(!T->rev)return ;
     T->rev=0;
     swap(T->l,T->r);
     T->l->rev^=1;
     T->r->rev^=1;
}
void rotst(treap* &T)
{
     treap* tmp=T->l;
     T->l=tmp->r;
     tmp->r=T;
     T=tmp;
     refrsize(T);
     refrsize(T->r);
     refrha(T->r);
     refrha(T);
}
void rotdr(treap* &T)
{
    treap* tmp=T->r;
    T->r=tmp->l;
    tmp->l=T;
    T=tmp;
    refrsize(T);
    refrsize(T->l);
    refrha(T->l);
    refrha(T);
}
void balance(treap* &T)
{
    refrrev(T);
    refrsize(T);
    refrsize(T->l);
    refrsize(T->r);
    if(T->l->p>T->p)rotst(T);
    if(T->r->p>T->p)rotdr(T);
}
void ins(treap* &T,int key,int prio,int pos)
{
    refrrev(T);
    if(T==nill)
    {
        T=new treap(key,prio,nill,nill,1);return ;
    }
    if(pos<=T->l->sz+1)ins(T->l,key,prio,pos);
    else ins(T->r,key,prio,pos-T->l->sz-1);
    balance(T);
}
void del(treap* &T,int pos)
{
    refrrev(T);
    if(T->l==nill&&T->r==nill)
    {
        delete T;
        T=nill;
        return ;
    }
    if(T->l->sz+1==pos)
    {
        if(T->l->p>T->r->p)
        {
            refrrev(T);
            refrrev(T->l);
            rotst(T);
            del(T->r,T->r->l->sz+1);
        }
        else
        {
            refrrev(T);
            refrrev(T->r);
            rotdr(T);
            del(T->l,T->l->l->sz+1);
        }
    }
    refrsize(T);
}
treap* join(treap* &T1,treap* &T2)
{
    treap* t=new treap(0,1,T1,T2,1);
    del(t,t->l->sz+1);
    return t;
}
pair<treap*,treap*> split(treap* &T,int pos)///[1,pos)
{
    ins(T,'a'-1,1<<30,pos);
    return {T->l,T->r};
}
bool palin(int a,int b)
{
    pair<treap*,treap*> tmp,aux;
    tmp=split(T,b+1);
    aux=split(tmp.first,a);
    bool rez=(aux.second->st==aux.second->dr);
    treap* t=join(aux.first,aux.second);
    T=join(t,tmp.second);
    return rez;
}
void M1(int i,int j,int k)
{
    pair<treap*,treap*> tmp,aux;
    tmp=split(T,j+1);
    aux=split(tmp.first,i);
    treap* t;t=join(aux.first,tmp.second);
    tmp=split(t,k+1);
    t=join(tmp.first,aux.second);
    T=join(t,tmp.second);
}
void M2(int i,int j)
{
    pair<treap*,treap*> tmp,aux;
    tmp=split(T,j+1);
    aux=split(tmp.first,i);
    aux.second->rev^=1;
    treap* t=join(aux.first,aux.second);
    T=join(t,tmp.second);
}
void M3(int i,char c)
{
    ins(T,c,myrand(),i);
}
void afis(treap* T)
{
    if(T==nill)return ;
    afis(T->l);
    cerr<<T->k;
    afis(T->r);
}
int main()
{
    srand(time(NULL));
    T=nill=new treap('a'-1,0,NULL,NULL,0);
    cin>>N>>M;
    cin>>a;
    for(int i=1;i<=N;i++)
        ins(T,a[i-1],myrand(),i);
   // afis(T);cerr<<"\n";
    for(int i=1;i<=M;i++)
    {
        int a,b,d,e;
        cin>>c;
        if(c=='Q')
        {
            cin>>a>>b;
            cout<<(palin(a,b) ? "YES\n":"NO\n");
        }
        else
        {
            cin>>a;
            if(a==1)
            {
                cin>>b>>d>>e;
                M1(b,d,e);
            }
            else if(a==2)
            {
                cin>>b>>d;
                M2(b,d);
            }
            else
            {
                cin>>b>>c;
                M3(b,c);
            }
        }
        //afis(T);cerr<<"\n";
    }
    return 0;
}
