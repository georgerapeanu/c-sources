#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#define inf (1<<30)
using namespace std;
FILE *f=fopen("in","r");
FILE *g=fopen("out","w");
///parsare
const int LEN=1000;
char buff[LEN];
int ind=LEN-1;
int i32()
{
    int rez=0;
    int sgn=1;
    while((buff[ind]<'0'||buff[ind]>'9')&&buff[ind]!='-')
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    if(buff[ind]=='-')
    {
        sgn=-1;
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    while(buff[ind]>='0'&&buff[ind]<='9'){
        rez=rez*10+buff[ind]-'0';
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    return rez*sgn;
}
long long i64()
{
    long long rez=0;
    int sgn=1;
    while((buff[ind]<'0'||buff[ind]>'9')&&buff[ind]!='-')
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    if(buff[ind]=='-')
    {
        sgn=-1;
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    while(buff[ind]>='0'&&buff[ind]<='9'){
        rez=rez*10+buff[ind]-'0';
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    return rez*sgn;
}
short i16()
{
    short rez=0;
    int sgn=1;
    while((buff[ind]<'0'||buff[ind]>'9')&&buff[ind]!='-')
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    if(buff[ind]=='-')
    {
        sgn=-1;
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    while(buff[ind]>='0'&&buff[ind]<='9'){
        rez=rez*10+buff[ind]-'0';
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    return rez*sgn;
}
///gataparsarea
///inverse
int MOD,phi;
int F[1005];
void getphi(int val)
{
    phi=val;
    F[0]=0;
    for(int i=2;i*i<=val;i++)
    {
        if(val%i==0)
        {
            F[++F[0]]=i;
            phi=phi/i*(i-1);
            while(val%i==0)val/=i;
        }
    }
    if(val!=1)
    {
        phi=phi/val*(val-1);
        F[++F[0]]=val;
    }
}
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=(1LL*p*b)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
struct inverse
{
    int E[1005],val;
    inverse()
    {
        val=0;memset(E,0,sizeof(E));
    }
    inverse(int nr)
    {
        val=nr;memset(E,0,sizeof(E));
        for(int i=1;i<=F[0];i++)
        {
            while(val%F[i]==0)
            {
                E[i]++;
                val/=F[i];
            }
        }
    }
    inverse operator *(inverse other)
    {
        inverse tmp;
        for(int i=1;i<=F[0];i++)
            tmp.E[i]=E[i]+other.E[i];
        tmp.val=(1LL*val*other.val)%MOD;
        return tmp;
    }
    inverse operator /(inverse other)
    {
        inverse tmp;
        for(int i=1;i<=F[0];i++)
            tmp.E[i]=E[i]-other.E[i];
        tmp.val=(1LL*val*lgpow(other.val,phi-1))%MOD;
        return tmp;
    }
    int toint()
    {
       int rez=val;
       for(int i=1;i<=F[0];i++)
            rez=(1LL*rez*lgpow(F[i],E[i]))%MOD;
       return rez;
    }
};
///gatainverse
///numeramari
typedef int tp;///pt inmultire sa ai grija,pe o pozitie adaugi in worst case min(A[0],B[0]) * (BASE - 1) ^ 2 ~ min(A[0],B[0]) * 1e8 <= 2e9 <=> min(A[0],B[0]) <= 20 !!!!
const tp BASE=10000;///daca folosesti impscalar sau imp,nu ar trebui sa o faci mare
///daca vrei sa folosesti functia rad,base trebuie neaparat sa fie 10
///const int LEN=1000;
void init(tp A[],tp val)
{
    memset(A,0,sizeof(tp)*(A[0]+1));
    if(val==0){A[0]=1;A[1]=0;return ;}
    while(val){A[++A[0]]=val%BASE;val/=BASE;}
}
void add(tp A[],tp B[])
{
    tp t=0;
    for(tp i=1;i<=A[0]||i<=B[0]||t;i++)
    {
        A[i]=(A[i]+t+B[i]);
        t=0;
        while(A[i]>=BASE){t++;A[i]-=BASE;}
        A[0]=max(A[0],i);
    }
}
short cmp(tp A[],tp B[])
{
    if(A[0]!=B[0])return A[0]<B[0] ? -1:1;
    int ind=A[0];
    while(ind&&A[ind]==B[ind])ind--;
    if(!ind)return 0;
    return A[ind]<B[ind] ? -1:1;

}
void scad(tp A[],tp B[])
{
    tp t=0;
    for(int i=1;i<=B[0]||t;i++)
    {
        A[i]=A[i]-t-B[i];
        t=0;
        if(A[i]<0){t=1;A[i]+=BASE;}
    }
    while(A[0]>1&&A[A[0]]==0)A[0]--;
}
tp C[LEN];
tp R[LEN];
void mult(tp A[],tp B[])
{
    memset(C,0,sizeof(C));
    C[0]=A[0]+B[0]-1;
    for(int i=1;i<=A[0];i++)
        for(int j=1;j<=B[0];j++)
            C[i+j-1]+=A[i]*B[j];
    tp t=0;
    for(tp i=1;i<=C[0]||t;i++)
    {
        C[i]+=t;
        t=C[i]/BASE;
        C[i]%=BASE;
        C[0]=max(C[0],i);
    }
    memcpy(A,C,sizeof(C));
    while(A[0]>1&&A[A[0]]==0)A[0]--;
}
void multscalar(tp A[],int val)
{
    tp t=0;
    for(tp i=1;i<=A[0]||t;i++)
    {
        A[i]=A[i]*val+t;
        t=A[i]/BASE;
        A[i]%=BASE;
        A[0]=max(A[0],i);
    }
    while(A[0]>1&&A[A[0]]==0)A[0]--;
}
void imp(tp A[],tp B[])
{
    init(C,0);
    init(R,0);
    for(int i=A[0];i;i--)
    {
        multscalar(R,BASE);
        R[1]=A[i];
        multscalar(C,BASE);
        while(cmp(R,B)>=0)
        {
            C[1]++;
            scad(R,B);
        }
    }
    memcpy(A,C,sizeof(C));
}
void impscalar(tp A[],tp val)
{
    tp r=0;
    init(C,0);
    for(int i=A[0];i;i--)
    {
        r=r*BASE+A[i];
        multscalar(C,BASE);
        C[1]=r/val;
        r%=val;
    }
    memcpy(A,C,sizeof(C));
}
tp tmp[LEN];
tp CRad[LEN];
tp RRad[LEN];
void rad(tp A[])
{
    init(RRad,0);
    int l=A[0];
    RRad[1]=A[l--];
    if(A[0]%2==0){multscalar(RRad,BASE);RRad[1]=A[l--];}
    init(CRad,BASE-1);
    while(1)
    {
        memcpy(tmp,CRad,sizeof(CRad));
        mult(tmp,tmp);
        if(cmp(tmp,RRad)<=0)
            break;
        CRad[1]--;
    }
    scad(RRad,tmp);
    for(;l;l-=2)
    {
        multscalar(RRad,BASE*BASE);
        RRad[0]=max(RRad[0],(tp)2);
        RRad[2]=A[l];
        RRad[1]=A[l-1];
        multscalar(CRad,BASE);
        int cf=BASE-1;
        while(cf>0)
        {
            memcpy(tmp,CRad,sizeof(CRad));
            multscalar(tmp,2);
            tmp[1]=cf;
            multscalar(tmp,cf);
            if(cmp(tmp,RRad)<=0)break;
            cf--;
        }
        CRad[1]=cf;
        if(cf!=0)scad(RRad,tmp);
    }
    while(CRad[0]>1&&CRad[CRad[0]]==0)CRad[0]--;
    memcpy(A,CRad,sizeof(CRad));
}
void afis(tp A[]){
    cout << A[A[0]];
    for(int i = A[0] - 1;i;i--){
        tp cb = BASE / 10;
        while(cb > 1 && cb > A[i]){
            cb /= 10;
            cout << "0";
        }
        cout << A[i];
    }
}
///gata numeremari
///treapuri
struct treap
{
    int key, prio;
    treap *l,*r;
    treap(int k,int p,treap *st,treap *dr)
    {
        key=k;
        prio=p;
        l=st;
        r=dr;
    }
}*T,*nill,*deg,*t1,*t2;
treap* fi(treap* &T,int key)
{
    if(T->key==key||T==nill)return T;
    if(key>T->key)return fi(T->r,key);
    return fi(T->l,key);
}
void rotst(treap* &T)
{
    treap *tmp=T->l;
    T->l=tmp->r;
    tmp->r=T;
    T=tmp;
}
void rotdr(treap* &T)
{
    treap *tmp=T->r;
    T->r=tmp->l;
    tmp->l=T;
    T=tmp;
}
void balance(treap* &T)
{
    if(T->l!=nill&&T->l->key>T->key)
        rotst(T);
    if(T->r!=nill&&T->r->key>T->key)
        rotdr(T);
}
void ins(treap* &T,int k,int p)
{
    if(T==nill)
    {
        T=new treap(k,p,nill,nill);
        return ;
    }
    if(k<T->key)ins(T->l,k,p);
    else ins(T->r,k,p);
    balance(T);
}
void del(treap* &T,int k)
{
    if(T==nill)return;
    if(T->key==k)
    {
        if(T->l==nill&&T->r==nill)
        {
            delete T;
            T=nill;
            return ;
        }
        if(T->r->prio>T->l->prio)
        {
            rotdr(T);
            del(T->l,k);
        }
        else
        {
            rotst(T);
            del(T->r,k);
        }
    }
    else if(T->key>k)del(T->l,k);
    else if(T->key<k)del(T->r,k);
}
treap* join(treap* &T,treap* &T1,treap* &T2,int key)
{
    T=new treap(key,0,T1,T2);
    del(T,key);
}
void split(treap* &T,treap* &T1,treap* &T2,int key)
{
    ins(T,key,inf);
    T1=T->l;
    T2=T->r;
    delete T;
    T=nill;
}
int mod=10234;
int myrand()
{
    return rand()%mod+1;
}
///gata treapuri
tp A[LEN];
tp M[LEN];
tp N[LEN];
int main()
{
    srand(time(NULL));
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    for(int i = 1;i <= 30;i++){
        N[i] = M[i] = BASE - 1;
    }
    N[0] = M[0] = 30;
    mult(N,M);
    afis(N);
    fclose(f);
    fclose(g);
    return 0;
}
