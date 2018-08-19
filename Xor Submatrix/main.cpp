#include <iostream>

using namespace std;
int U[2005];
int V[2005];
int rez=0;
int N,M;
struct trie
{
    trie *fii[2];
    trie()
    {
        fii[0]=fii[1]=NULL;
    }
}*T;
void ins(trie *T,int nr,int bit)
{
    if(bit==-1)return ;
    if(T->fii[(nr>>bit)&1]==NULL)T->fii[(nr>>bit)&1]=new trie;
    ins(T->fii[(nr>>bit)&1],nr,bit-1);
}
int q(trie *T,int nr,int bit)
{
    if(bit==-1)return 0;
    if(T->fii[!((nr>>bit)&1)]!=NULL)return (1<<bit)+q(T->fii[!((nr>>bit)&1)],nr,bit-1);
    return q(T->fii[((nr>>bit)&1)],nr,bit-1);
}
int main() {
    T=new trie;
    cin>>N>>M;
    for(int i=1;i<=N;i++){cin>>V[i];V[i]^=V[i-1];}
    for(int i=1;i<=M;i++){cin>>U[i];U[i]^=U[i-1];}
    for(int i=1;i<=N;i++)
    {
        for(int j=i;j<=N;j++)
        {
            if((j-i+1)%2==0)
            {
                rez=max(rez,V[j]^V[i-1]);
            }
            else
            {
                ins(T,V[j]^V[i-1],30);
            }
        }
    }
    for(int i=1;i<=M;i++)
    {
        for(int j=i;j<=M;j++)
        {
            if((j-i+1)%2==0)
            {
                rez=max(rez,U[j]^U[i-1]);
            }
            else
            {
                rez=max(rez,q(T,U[j]^U[i-1],30));
            }
        }
    }
    cout<<rez;
    return 0;
}
