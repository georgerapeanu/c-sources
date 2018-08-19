#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream f("camion.in");
ofstream g("camion.out");
struct data
{
    int x1,x2,y1,y2;
};
vector<data> Q;
int N,M,K,C;
int rez[605];
int main()
{
    f>>N>>M>>K>>C;
    for(int i=1;i<=K;i++)
    {
        data a;
        f>>a.x1>>a.y1>>a.x2>>a.y2;
        Q.push_back(a);
    }
    for(int i=1;i<=N;i++)rez[i]=C;
    reverse(Q.begin(),Q.end());
    for(auto it:Q)
    {
        for(int i=it.x1;i<=it.x2;i++)
        {
            if(rez[i]>=it.y1)rez[i]+=it.y2-it.y1+1;
        }
    }
    for(int i=1;i<=N;i++)
        g<<(rez[i]>M ? 0:rez[i])<<"\n";
    return 0;
}
