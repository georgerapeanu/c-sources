#include <cstdio>
#include <cstring>
#define SIGMA 26
using namespace std;
FILE *f=fopen("trie.in","r");
FILE *g=fopen("trie.out","w");
struct Trie
{
    int cnt;
    int nrfii;
    Trie *fiu[SIGMA];
    Trie()
    {
        cnt=nrfii=0;
        memset(fiu,0,sizeof(fiu));
    }
};
Trie *T;
void ins(Trie *nod,char *s)
{
    if(*s=='\n')
    {
        nod->cnt++;
        return ;
    }
    if(nod->fiu[*s-'a']==NULL)
    {
        nod->fiu[*s-'a']=new Trie;
        nod->nrfii++;
    }
    ins(nod->fiu[*s-'a'],s+1);
}
bool del(Trie *nod,char *s)
{
    if(*s=='\n')
        nod->cnt--;
    else if(del(nod->fiu[*s-'a'],s+1))
    {
        nod->nrfii--;
        nod->fiu[*s-'a']=NULL;
    }
    if(nod->cnt==0&&nod->nrfii==0&&nod!=T)
    {
        delete nod;return 1;
    }
    return 0;
}
int nrap(Trie *nod,char *s)
{
    if(*s=='\n')
        return nod->cnt;
    if(nod->fiu[*s-'a'])
        return nrap(nod->fiu[*s-'a'],s+1);
    return 0;
}
int com(Trie *nod,char *s,int k)
{
    if(*s=='\n'||nod->fiu[*s-'a']==NULL)
        return k;
    return com(nod->fiu[*s-'a'],s+1,k+1);
}
int main()
{
    T=new Trie;
    char C[32];
    while(fgets(C,32,f)!=NULL)
    {
        if(C[0]=='0') ins(T,C+2);
        else if(C[0]=='1') del(T,C+2);
        else if(C[0]=='2') fprintf(g,"%d\n",nrap(T,C+2));
        else fprintf(g,"%d\n",com(T,C+2,0));
    }
    fclose(f);
    fclose(g);
    return 0;
}
