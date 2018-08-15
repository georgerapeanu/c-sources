#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
FILE *f=fopen("loto.in","r");
FILE *g=fopen("loto.out","w");
set <int> S;
set <int> rez;
set <int>::iterator it1;
set <int>::iterator it2;
int N,V[10],i,maxim,minim=10000,a;
int *p;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&a);
        S.insert(a);
    }
    for(i=1;i<=6;i++)
    {
        fscanf(f,"%d",&V[i]);
        minim=min(V[i],minim);
        maxim=max(V[i],maxim);
    }
    for(i=1;i<=6;i++)
    {
        if(V[i]!=maxim&&V[i]!=minim)
            rez.insert(V[i]);
    }
    //
    a=minim;
    it1=S.find(a);
    it2=S.find(a);
    if(it1!=S.begin())
    it1--;
    it2++;
    p=std::find(V+1,V+8,*it1);
    while(it1!=S.begin()&&p!=V+8)
    {
        it1--;
        p=find(V+1,V+8,*it1);
    }
    p=find(V+1,V+8,*it2);
    while(it2!=S.end()&&p!=V+8)
    {
        it2++;
        p=find(V+1,V+8,*it2);
    }
    if(it2==S.end()||abs(*it1-V[1])<abs(*it2-V[1]))
    {
        rez.insert(*it1);
        S.erase(it1);
        S.erase(S.find(a));
    }
    else
    {
        rez.insert(*it2);
        S.erase(it2);
        S.erase(S.find(a));
    }
        a=maxim;
        if(it1!=S.begin())
    it1=S.find(a);
    it2=S.find(a);
    it1--;
    it2++;
    p=find(V+1,V+8,*it1);
    while(it1!=S.begin()&&p!=V+8)
    {
        it1--;
        p=find(V+1,V+8,*it1);
    }
    p=find(V+1,V+8,*it2);
    while(it2!=S.end()&&p!=V+8)
    {
        it2++;
        p=find(V+1,V+8,*it2);
    }
    if(it2==S.end()||abs(*it1-V[1])<abs(*it2-V[1]))
    {
        rez.insert(*it1);
        S.erase(it1);
        S.erase(S.find(a));
    }
    else
    {
        rez.insert(*it2);
        S.erase(it2);
        S.erase(S.find(a));
    }
    for(it1=rez.begin();it1!=rez.end();it1++)
    {
        fprintf(g,"%d ",*it1);
    }
    fclose(f);
    fclose(g);
    return 0;
}
