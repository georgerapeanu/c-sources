#include <cstdio>
#include <cstring>
#define SIGMA 2
#define bit ((nr&(1<<poz))!=0)
using namespace std;
FILE *f=fopen("luffxor.in","r");
FILE *g=fopen("luffxor.out","w");
int V[200005];
struct trie
{
    int cnt;
    trie *fiu[SIGMA];
    trie()
    {
        cnt=0;
        memset(fiu,0,sizeof(fiu));
    }
};
trie *T;
void ins(trie *nod,int nr,int poz)
{
    nod->cnt++;
    if(poz<0){return ;}
    if(nod->fiu[bit]==NULL)
        nod->fiu[bit]=new trie;
    ins(nod->fiu[bit],nr,poz-1);
}
bool del(trie *nod,int nr,int poz)
{
    nod->cnt--;
    if(poz<0) ;
    else if(del(nod->fiu[bit],nr,poz-1))
    {
        nod->fiu[bit]=NULL;
    }
    if(nod->cnt==0&&nod!=T)
        {delete nod;return 1;}
    return 0;
}
int pref(trie *nod,int nr,int poz,int bpoz)
{
    if(poz==bpoz) return nod->cnt;
    if(nod->fiu[bit]==NULL) return 0;
    return pref(nod->fiu[bit],nr,poz-1,bpoz);
}
int main()
{
    int N;
    fscanf(f,"%d",&N);
    T=new trie;
    for(int i=1;i<=N;i++)
    {
        int op;
        fscanf(f,"%d",&op);
        if(op==0)
        {
            int a;
            fscanf(f,"%d",&a);
            V[++V[0]]=a;
            ins(T,a,31);
        }
        else if(op==1)
        {
            int a;
            fscanf(f,"%d",&a);
            del(T,V[a],31);
        }
        else
        {
            int y,k;
            fscanf(f,"%d%d",&y,&k);
            int elem=0,rez=0;
            for(int poz=31;poz>=0;poz--)
            {
                int a,b;
                a=((1<<poz)&y);
                b=((1<<poz)&k);
                if(!a&&!b) ;
                else if(a&&!b) elem+=(1<<poz);
                else if(!a&&b)
                {
                    rez+=pref(T,elem,31,poz-1);
                    elem+=(1<<poz);
                }
                else
                {
                    elem+=(1<<poz);
                    rez+=pref(T,elem,31,poz-1);
                    elem-=(1<<poz);
                }
            }
            rez+=pref(T,elem,31,-1);
            fprintf(g,"%d\n",rez);
        }
    }
    return 0;
}
