#include <cstdio>
#include <iostream>
using namespace std;
int N,val,i,fost[400000],ultim=-1,nr,s,nr0;
short grupa[400000];
pair<int,int> rez[400000];
int main()
{
    scanf("%d",&N);
    for(i=1;i<=N;i++)
    {
        scanf("%d",&val);
        if(fost[val])
        {
            if(fost[val]>ultim)
            {
                ultim=i;
                nr++;
                rez[nr].first=fost[val];
                rez[nr].second=i;
                grupa[i+1]--;
                grupa[fost[val]]++;
            }
        }
        fost[val]=i;
    }
    nr0=1;
    for(i=1;i<=N;i++)
    {
        s+=grupa[i];
        if(rez[nr0].second<i)
            nr0++;
        if(!s)
        {
            rez[nr0].first--;
        }
    }
    if(nr)
        printf("%d\n",nr);
    else
        printf("-1");
    for(i=1;i<=nr;i++)
        printf("%d %d\n",rez[i].first,rez[i].second);
    return 0;
}
