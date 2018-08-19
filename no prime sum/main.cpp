#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#define NMAX 200000
#define gr first
#define val second
using namespace std;
vector<int> elem;
bitset<NMAX+5> E;
pair<int,int> V[2005];
int N,A[2005];
int main() {
    E[0]=E[1]=1;
    for(int i=2;i*i<=NMAX;i++)
    {
        if(!E[i])
        {
            for(int j=i*i;j<=NMAX;j+=i)
                E[j]=1;
        }
    }
    cin>>N;
    for(int i=1;i<=N;i++) cin>>A[i];
    for(int i=1;i<=N;i++)
    {
        for(int j=i+1;j<=N;j++)
        {
            if(i!=j&&E[A[i]+A[j]]==0)
                {V[i].gr++;V[i].val=A[i];V[j].gr++;V[j].val=A[j];}
        }
    }
    sort(V+1,V+1+N);
    int poz=N;
    while(V[poz].gr>0)
    {
        for(int j=1;j<poz;j++)
        {
            if(V[poz].val!=V[j].val&&E[V[poz].val+V[j].val]==0)
                V[j].gr--;
        }
        elem.push_back(V[poz].val);
        poz--;
        sort(V+1,V+1+poz);
    }
    cout<<elem.size()<<"\n";
    for(auto it:elem) cout<<it<<" ";
    return 0;
}
