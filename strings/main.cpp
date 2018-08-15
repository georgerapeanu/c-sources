#include <iostream>
#include <cstdlib>
#include <ctime>
#define MOD 1000000007
#define BASE 31
using namespace std;
int pw[400005];
int N,M;

int myrand()
{
    return ((rand()&((1<<14)-1))<<14)+(rand()&((1<<14)-1))+1;
}
int adun(int a,int b)
{
    a+=b;
    if(a>=MOD)a-=MOD;
    return a;
}
int mult(int a,int b)
{
    return (1LL*a*b)%MOD;
}
struct hsh
{
    int len,h;
    hsh()
    {
        len=h=0;
    }
    hsh (char c)
    {
        h=c-'a'+1;
        len=(c!='a'-1);
    }
};
hsh operator + (hsh a,hsh b)
{
    a.len+=b.len;
    a.h=adun(mult(a.h,pw[b.len]),b.h);
    return a;
}
bool operator ==(hsh a,hsh b)
{
    return a.h==b.h&&a.len==b.len;
}
struct treap
{
    char key;
    int prio;
    hsh h,hr;
    bool rev;
    int sz;
    treap *l,*r;
    treap (char c,int p,int s,treap* a,treap* b)
    {
        key=c;
        prio=p;
        sz=s;
        l=a;
        r=b;
        rev=0;
        h=hr=hsh(c);
    }
}*T,*nill;
void unrev(treap* &T)
{
    if(!T->rev||T==nill)return;
    T->rev=0;swap(T->l,T->r);swap(T->h,T->hr);
    T->l->rev^=1;
    T->r->rev^=1;
}
void rehash(treap* &T)
{
    if(T==nill)return;
    unrev(T);
    unrev(T->l);
    unrev(T->r);
    hsh tmp(T->key);
    T->h=(T->l->h+tmp)+T->r->h;
    T->hr=(T->r->hr+tmp)+T->l->hr;
}
void resz(treap* &T)
{
    if(T==nill)return;
    T->sz=T->l->sz+T->r->sz+1;
}
treap* join(treap* T1,treap* T2)
{
    unrev(T1);
    unrev(T2);
    if(T1==nill)return T2;
    if(T2==nill)return T1;
    if(T1->prio>T2->prio)
    {
        T1->r=join(T1->r,T2);
        rehash(T1);resz(T1);
        return T1;
    }
    else
    {
        T2->l=join(T1,T2->l);
        rehash(T2);resz(T2);
        return T2;
    }
}
void split(treap* T,treap* &L,treap* &R,int pos)
{
    if(T==nill){L=nill;R=nill;return ;}
    unrev(T);
    int tmp=T->l->sz;
    if(pos<=tmp)
    {
        R=T;
        split(R->l,L,R->l,pos);
        resz(R);rehash(R);
    }
    else
    {
        L=T;
        split(L->r,L->r,R,pos-tmp-1);
        resz(L);rehash(L);
    }
}
bool palindrom(int st,int dr)
{
    treap *T1,*T2,*T3;
    split(T,T2,T3,dr);
    split(T2,T1,T2,st-1);
    bool rez=(T2->h==T2->hr);
    T=join(join(T1,T2),T3);
    return rez;
}
void ins(int pos,char k)
{
    treap *T1,*T2,*T3;
    split(T,T1,T3,pos-1);
    T2=new treap(k,myrand(),1,nill,nill);
    T=join(join(T1,T2),T3);
}
void rev(int st,int dr)
{
    treap *T1,*T2,*T3;
    split(T,T2,T3,dr);
    split(T2,T1,T2,st-1);
    T2->rev^=1;
    T=join(join(T1,T2),T3);
}
void upd(int i,int j,int k)
{
    treap *T1,*T2,*T3;
    split(T,T2,T3,j);
    split(T2,T1,T2,i-1);
    T1=join(T1,T3);
    split(T1,T1,T3,k);
    T=join(join(T1,T2),T3);
}
void afis(treap* T)
{
    if(T==nill)return ;
    unrev(T);
    afis(T->l);
    cerr<<T->key;
    afis(T->r);
}
string a;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    srand(time(NULL));
    T=nill=new treap('a'-1,0,0,NULL,NULL);
    cin>>N>>M;
    cin>>a;
    pw[0]=1;for(int i=1;i<=N+M;i++)pw[i]=(1LL*pw[i-1]*BASE)%MOD;
    for(int i=1;i<=N;i++)
    {
        ins(i,a[i-1]);
    }
    for(int i=1;i<=M;i++)
    {
        char c;
        cin>>c;
        if(c=='Q')
        {
            int st,dr;
            cin>>st>>dr;
            cout<<(palindrom(st,dr)==1 ? "YES":"NO")<<"\n";
        }
        else
        {
            int tip;
            cin>>tip;
            if(tip==1)
            {
                int st,dr,k;
                cin>>st>>dr>>k;
                upd(st,dr,k);
            }
            else if(tip==2)
            {
                int st,dr;
                cin>>st>>dr;
                rev(st,dr);
            }
            else
            {
                int pos;
                cin>>pos>>c;
                ins(pos,c);
            }
        }
        //afis(T);cerr<<"\n";
    }
    return 0;
}
