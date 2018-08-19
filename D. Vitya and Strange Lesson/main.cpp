#include <iostream>
using namespace std;
bool sw[32];
int N,Q;
struct trie
{
    trie *l,*r;
    int nr;
    bool S;
    trie()
    {
        nr=1;
        S=0;
        l=r=NULL;
    }
}*T;
void ins(trie *T,int nr,int poz)
{
    if(poz==-1)return ;
    if(((nr>>poz)&1))
    {
        if(T->r==NULL)T->r=new trie;
        ins(T->r,nr,poz-1);
    }
    else
    {
        if(T->l==NULL)T->l=new trie;
        ins(T->l,nr,poz-1);
    }
    T->nr=(T->l==NULL ? 0:T->l->nr)+(T->r==NULL ? 0:T->r->nr);

}
void u(int x)
{
    for(int bit=0;bit<=30;bit++)
    {
        if((x>>bit)&1)sw[bit]^=1;
    }
}
int q(trie *T,int poz)
{
    if(T==NULL)return 0;
    if(T->S!=sw[poz]){swap(T->l,T->r);T->S^=1;}
    if((T->l==NULL ? 0:T->l->nr)<(1<<(poz)))
    {
        return q(T->l,poz-1);
    }
    if((T->r==NULL ? 0:T->r->nr)<(1<<(poz)))
    {
        return (1<<poz)+q(T->r,poz-1);
    }
    return T->nr;
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    T=new trie;
    cin>>N>>Q;
    for(int i=1;i<=N;i++)
    {
        int val;
        cin>>val;
        ins(T,val,30);
    }
    while(Q--)
    {
        int x;
        cin>>x;
        u(x);
        cout<<q(T,30)<<"\n";
    }
    return 0;
}
