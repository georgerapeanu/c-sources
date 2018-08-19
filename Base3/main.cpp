#include <fstream>
#include <iostream>
#include <cassert>
#include <queue>
#define OFF 100000
using namespace std;
ifstream f("base3.in");
ofstream g("base3.out");
int dist[2*OFF+1];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > H;
string a,b,c;
int main()
{
    for(int i=0;i<2*OFF+1;i++)dist[i]=1<<30;
    f>>a>>b>>c;
    for(int i=0;i<(int)a.size();i++)
    {
        if(a[i]=='1')
        {
            dist[OFF+i-((int)a.size()-i-1)]=min((int)a.size(),dist[OFF+i-((int)a.size()-i-1)]);
            H.push({dist[OFF+i-(a.size()-i-1)],OFF+i-((int)a.size()-i-1)});
        }
    }
    for(int i=0;i<(int)b.size();i++)
    {
        if(b[i]=='1')
        {
            dist[OFF+i-((int)b.size()-i-1)]=min(dist[OFF+i-((int)b.size()-i-1)],(int)b.size());
            H.push({dist[OFF+i-((int)b.size()-i-1)],OFF+i-((int)b.size()-i-1)});
        }
    }
    for(int i=0;i<(int)c.size();i++)
    {
        if(c[i]=='1')
        {
            dist[OFF+i-((int)c.size()-i-1)]=min(dist[OFF+i-((int)c.size()-i-1)],(int)c.size());
            H.push({dist[OFF+i-((int)c.size()-i-1)],OFF+i-((int)c.size()-i-1)});
        }
    }
    while(!H.empty())
    {
        pair<int,int> tmp=H.top();H.pop();
        assert(0<=tmp.second&&tmp.second<=2*OFF);
        if(dist[tmp.second]!=tmp.first)continue;
        int nod=tmp.second;
        if(nod+(int)a.size()<=2*OFF&&dist[nod+(int)a.size()]>dist[nod]+(int)a.size())
        {
            dist[nod+(int)a.size()]=dist[nod]+(int)a.size();
            H.push({dist[nod]+(int)a.size(),nod+(int)a.size()});
        }
        if(nod-(int)a.size()>=0&&dist[nod-(int)a.size()]>dist[nod]+(int)a.size())
        {
            dist[nod-(int)a.size()]=dist[nod]+(int)a.size();
            H.push({dist[nod]+(int)a.size(),nod-(int)a.size()});
        }
        if(nod+(int)b.size()<=2*OFF&&dist[nod+(int)b.size()]>dist[nod]+(int)b.size())
        {
            dist[nod+(int)b.size()]=dist[nod]+(int)b.size();
            H.push({dist[nod]+(int)b.size(),nod+(int)b.size()});
        }
        if(nod-(int)b.size()>=0&&dist[nod-(int)b.size()]>dist[nod]+(int)b.size())
        {
            dist[nod-(int)b.size()]=dist[nod]+(int)b.size();
            H.push({dist[nod]+(int)b.size(),nod-(int)b.size()});
        }
        if(nod+(int)c.size()<=2*OFF&&dist[nod+(int)c.size()]>dist[nod]+(int)c.size())
        {
            dist[nod+(int)c.size()]=dist[nod]+(int)c.size();
            H.push({dist[nod]+(int)c.size(),nod+(int)c.size()});
        }
        if(nod-(int)c.size()>=0&&dist[nod-(int)c.size()]>dist[nod]+(int)c.size())
        {
            dist[nod-(int)c.size()]=dist[nod]+(int)c.size();
            H.push({dist[nod]+(int)c.size(),nod-(int)c.size()});
        }
    }
    g<<(dist[OFF]!=(1<<30) ? dist[OFF]:0);
    return 0;
}
