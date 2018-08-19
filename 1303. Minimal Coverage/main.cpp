#include <iostream>
#define inf 50004
#include <vector>
#include <algorithm>
#define st first
#define dr second
using namespace std;
pair <int,int> V[100001];
int usegm,M;
pair<int,int> segm;
vector<pair<int,int> > rez;
int N;
int main()
{
    cin>>M;
    segm.st=-inf;
    N=1;
    do
    {
        cin>>V[N].first>>V[N].second;
        N++;
    }
    while(V[N-1].first||V[N-1].second);
    N-=2;
    sort(V+1,V+1+N);
    int i=1;
    while(V[i].dr<0)
        i++;
    if(V[i].st>0||i>N)
    {
        cout<<"No solution";
        return 0;
    }
    for(;i<=N&&segm.dr<M;i++)
    {
        if(segm.st<=V[i].st&&V[i].st<=segm.dr&&V[i].dr>segm.dr)
        {
            if(V[usegm].dr<V[i].dr)
                usegm=i;
        }
        else if(V[i].st>segm.dr)
        {
            if(usegm==0)
            {
                cout<<"No solution";
                return 0;
            }
            segm.dr=V[usegm].dr;
            rez.push_back(V[usegm]);
            usegm=0;
            i--;
        }
    }
    if(usegm)
    {
        segm.dr=V[usegm].dr;
        rez.push_back(V[usegm]);
    }
    if(segm.dr<M)
    {
        cout<<"No solution";
        return 0;
    }
    cout<<rez.size()<<"\n";
    for(auto it:rez)
        cout<<(it).first<<" "<<(it).second<<"\n";
    return 0;
}
