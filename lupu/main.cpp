#include <cstdio>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;
FILE *f=fopen("lupu.in","r");
FILE *g=fopen("lupu.out","w");
pair <long long,long long> O[100005];
priority_queue <long long> H;
long long N,i,X,L,CN,maxim,rez;
bool cmp(pair<long long,long long> a,pair<long long,long long> b)
{
    if(a.first!=b.first)
        return a.first>b.first;
    return a.second>b.second;
}
int main()
{
    fscanf(f,"%lld%lld%lld",&N,&X,&L);
    for(i=1;i<=N;i++)
        fscanf(f,"%lld%lld",&O[i].first,&O[i].second);
    sort(O+1,O+1+N,cmp);
    i=1;
    for(i=1;i<=N;i++)
    {
        if(O[i].first<=X)///daca avem o varianta care se incadreaza in distanta
        {
            X-=L;///scadem distanta
            H.push(-O[i].second);///o adaugam in minheap
        }
        else if(!H.empty()&&-H.top()<O[i].second)///daca minimul din cele alese este mai mic decat elem curent,atuncia il putem lua pe el si il eliminam pe minim
        {
            H.pop();
            H.push(-O[i].second);
        }
    }
    while(!H.empty())
    {
        rez-=H.top();
        H.pop();
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}

