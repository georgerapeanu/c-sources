#include <cstdio>
#define mp make_pair
#include <set>
using namespace std;
FILE *f=fopen("great.in","r");
FILE *g=fopen("great.out","w");
typedef pair<int,int> pii;
long long loc,G,nrpar;
int t;
int N;
long long sumA,sumB,votA,votB;
int people,weight;
pii tmp;
double rap(pii a)
{
    return 1.0*a.first/a.second;
}
struct cmp{
    bool operator () (pii a,pii b)
    {
            return rap(a)<rap(b);
    }
};
multiset<pii,cmp> S;
multiset<pii> ::iterator it,it2;
double grap(multiset<pii> ::iterator it)
{
    if(it==S.end())
        return 1000000001;
    return 1.0*it->first/it->second;
}
void pushA()
{
    while(sumA<sumB)
    {
        it2--;
        sumA+=it2->first;
        sumB-=it2->first;
        votA+=it2->second/2+1;
        votB-=(it2->second/2+1);
    }
}
void pushB()
{
    while(sumA-it2->first>sumB+it2->first)
    {
        sumA-=it2->first;
        sumB+=it2->first;
        votA-=(it2->second/2+1);
        votB+=it2->second/2+1;
        it2++;
    }
}
void c1()
{
        if(t==0)
        {
            loc+=people;
            G+=weight;
            nrpar+=(people%2==0);
            S.insert(tmp);

        }
        else
        {
            it=S.find(tmp);
            S.erase(it);
            loc-=people;
            G-=weight;
            nrpar-=(people%2==0);
        }
        if(t==0)
        {
            if(grap(it2)<=rap(tmp))
            {
                votB+=tmp.second/2;
                votA+=tmp.second/2+1;
                sumA+=tmp.first;
            }
            else
            {
                votB+=tmp.second;
                sumB+=tmp.first;
            }
        }
        else
        {
            if(grap(it2)<rap(tmp))
            {
                votA-=(tmp.second/2+1);
                votB-=tmp.second/2;
                sumA-tmp.first;
            }
            else
            {
                votB-=tmp.second;
                sumB-=tmp.first;
            }
        }
        pushA();
        pushB();
        if(loc%2==0||G%2==0||nrpar)
            return ;
        if(votA<votB&&sumA>sumB)
            fputs("YES\n",g);
        else
            fputs("NO\n",g);
}
void c2()
{
    if(t==0)
    {
        loc+=people;
        G+=weight;
        nrpar+=(people%2==0);
        S.insert(make_pair(weight,people));

    }
    else
    {
        it=S.find(make_pair(weight,people));
        S.erase(it);
        loc-=people;
        G-=weight;
        nrpar-=(people%2==0);
    }
    if(loc%2==0||G%2==0||nrpar)
        return ;
    sumA=votA=0;
    sumB=G;
    votB=loc;
    bool ok=0;
    for(multiset<pii> ::reverse_iterator it=S.rbegin();it!=S.rend();it++)
    {
        sumA+=it->first;
        sumB-=it->first;
        votB=votB-(it->second)/2-1;
        votA+=(it->second)/2+1;
        if(votA<votB&&sumA>sumB)
        {fputs("YES\n",g);ok=1;break;}
    }
    if(!ok)
        fputs("NO\n",g);
}
int main()
{
    fscanf(f,"%d",&N);
    it2=S.end();
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d%d%d",&t,&people,&weight);
        tmp=mp(weight,people);
        if(N>5000)
            c1();
        else
            c2();
    }
    fclose(f);
    fclose(g);
    return 0;
}
