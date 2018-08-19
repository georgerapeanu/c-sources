#include <iostream>
#include <set>
#define val first
#define ind second
#define mp make_pair
using namespace std;
set<pair<int,int> > H;
int N;
long long K;
int V[100006];
int dr;
int main() {
    cin>>N>>K;
    for(int i=1;i<=N;i++)
        cin>>V[i];
    dr=1;
    for(int i=1;i<N&&i<=K;i++)
        {H.insert(mp(V[i+1],i+1));dr++;}
    for(int i=1;i<=N&&K>0;i++)
    {
        if(V[i]>=(*H.rbegin()).first)
        {
            H.erase(mp(V[i+1],i+1));
            continue;
        }
        pair<int,int> tmp=mp(V[i],(*H.rbegin()).second);
        swap(V[i],V[(*H.rbegin()).second]);K-=((*H.rbegin()).second-i);
        H.erase(*H.rbegin());
        H.insert(tmp);
        while(dr>i+1+K)
        {
            H.erase(mp(V[dr],dr));
            dr--;
        }
        while(dr<i+1+K)
        {
            dr++;
            H.insert(mp(V[dr],dr));
        }
    }
    for(int i=1;i<=N;i++)
        cout<<V[i]<<" ";
    return 0;
}
