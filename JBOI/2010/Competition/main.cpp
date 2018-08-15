#include <iostream>
#include <queue>
using namespace std;
int N,K;
int V[10005];
int P[10005];
int rez;
struct data
{
    int cross;
    int lap;
    int nr;
    bool operator < (const data &other)const
    {
        return cross>other.cross;
    }
};
priority_queue<data> H;
int t;
int main()
{
    cin>>K>>N;
    for(int i=1;i<=K;i++)
    {
        cin>>V[i];
        cin>>P[i];
        data tmp;
        tmp.cross=V[i];tmp.lap=1;tmp.nr=i;
        H.push(tmp);
    }
    int lcros=0,nr=0;
    while(rez<K&&!H.empty())
    {
        data tmp=H.top();H.pop();
        if(lcros!=tmp.cross){lcros=tmp.cross;nr=1;}
        else nr++;
        rez=max(rez,nr);
        if(tmp.lap<N)
        {
            tmp.cross+=V[tmp.nr]+tmp.lap%P[tmp.nr];
            tmp.lap++;
            H.push(tmp);
        }
    }
    cout<<rez;
    return 0;
}
