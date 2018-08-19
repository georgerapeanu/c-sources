#include <iostream>
#include <deque>
#include <vector>
using namespace std;
struct punct
{
    int x[6];
};
punct V[1005];
int N;
deque<int> good;
vector<int> rez;
int scalar(punct a,punct b,punct c)
{
    int rez=0;
    for(int i=1;i<=5;i++)rez=rez+(b.x[i]-a.x[i])*(c.x[i]-a.x[i]);
    return rez;
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=5;j++)cin>>V[i].x[j];
        good.push_back(i);
    }
    while(good.size())
    {
        if(good.size()>2)
        {
            int a=good.front();good.pop_front();
            int b=good.front();good.pop_front();
            int c=good.front();good.pop_front();
            if(scalar(V[a],V[b],V[c])<=0)
            {
                good.push_back(a);
            }
            else if(scalar(V[b],V[a],V[c])<=0)
            {
                good.push_back(b);
            }
            else if(scalar(V[c],V[b],V[a])<=0)
            {
                good.push_back(c);
            }
        }
        else
        {
            for(auto it:good)
            {
                bool ok=1;
                for(int i=1;i<=N&&ok;i++)
                {
                    if(i!=it)
                    {
                        for(int j=1;j<=N&&ok;j++)
                        {
                            if(j!=i&&j!=it)
                            {
                                if(scalar(V[it],V[i],V[j])>0)ok=0;
                            }
                        }
                    }
                }
                if(ok)rez.push_back(it);
            }
            good.clear();
        }
    }
    cout<<rez.size()<<"\n";
    for(auto it:rez)cout<<it<<" ";
    return 0;
}
