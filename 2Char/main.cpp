#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int m[27][27],maxim,n,i;
typedef pair<int,int> rez;
char v[1001];
void complet(rez a)
{
    if(a.first>=1)
    {
        if(a.second<1)
        {
            for(int i=1;i<=26;i++)
            {
                m[a.first][i]+=strlen(v);
                if(i!=a.first) m[i][a.first]+=strlen(v);
                if(m[a.first][i]>maxim)
                maxim=m[a.first][i];
                if(m[i][a.first]>maxim)
                maxim=m[i][a.first];
            }
        }
        else
        {
            m[a.first][a.second]+=strlen(v);
            m[a.second][a.first]+=strlen(v);
            if(m[a.first][a.second]>maxim)
            maxim=m[a.first][a.second];
            if(m[a.second][a.first])
            maxim=m[a.second][a.first];
        }
    }
}
void calcul()
{
    char c1=v[0],c2='\0';
    int nr=1;
    while(v[nr]==c1)
    nr++;
    if(v[nr]!='\0')
    {
        c2=v[nr];
        while(v[nr]==c2||v[nr]==c1)
        nr++;
    }
    if(v[nr]=='\0')
    {
        complet(rez(c1-'a'+1,c2-'a'+1));
    }
}
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
        scanf("%s",v);
        calcul();
    }
    cout<<maxim;
    return 0;
}
