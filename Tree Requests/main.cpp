#include <iostream>
#include <cstdlib>
using namespace std;
typedef pair<int,int> a;  //level&nr
typedef pair<char,int*> b;//ch&urm
typedef pair<a,b> nod;
nod v[500001];
int i,n,m,*leg,*ctr,v1,h,ap[28];
char c;
nod calcul(nod vf,int dp)
{
    if(vf.first.first<=dp)
    {
        if(dp==vf.first.first)
            ap[vf.second.first-'a'+1]++;
        else
        {
            for(int j=1;j<=ctr[vf.first.second];j++)
            {
                calcul(v[vf.second.second[j]],dp);
            }
        }
    }
}
bool merge,used1;
int main()
{
    std::cin>>n>>m;
    leg=(int *)malloc(sizeof(int)*(n+1));
    ctr=(int *)malloc(sizeof(int)*(n+1));
    v[1].first.first=v[1].first.second=1;
    for(i=1;i<=n;i++)
    ctr[i]=0;
    for(i=2;i<=n;i++)
    {
        std::cin>>leg[i];ctr[leg[i]]++;
    }
    for(i=1;i<=n;i++)
    {
        v[i].second.second=new int [ctr[i]+1];
        ctr[i]=0;
    }
    for(i=1;i<=n;i++)
    {
        std::cin>>c;
        if(i==1)
        v[i].second.first=c;
        else
        {
            ctr[leg[i]]++;
            v[leg[i]].second.second[ctr[leg[i]]]=i;
            v[i]=nod(a(v[leg[i]].first.first+1,i),b(c,v[i].second.second));
        }
    }
    for(i=1;i<=m;i++)
    {
        std::cin>>v1>>h;
        used1=0;
        merge=1;
        calcul(v[v1],h);
        for(int j=1;j<=26;j++)
        {
            if(ap[j]%2==1)
            {
                if(used1==1)
                {
                    merge=0;
                    break;
                }
                else
                used1=1;
            }
            ap[j]=0;
        }
        std::cout<<(merge==1 ?"Yes":"No")<<"\n";
    }
    return 0;
}
