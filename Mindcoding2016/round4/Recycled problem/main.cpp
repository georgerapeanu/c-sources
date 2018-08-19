#include <iostream>
#include <ctime>
#include <cstdlib>
#include <bitset>
#include <vector>
#include <cstdio>
#define VMAX 7000
using namespace std;
bitset<VMAX+5> B,tmp;
int K,nrelem,val;
vector<int> rez;
int main()
{
    srand(time(NULL));
    cin>>K;
    freopen("1.out","w",stdout);
    B[0]=1;
    while(K)
    {
        tmp.reset();
        val=rand()%5000+1;
        nrelem=0;
        for(int i=0;i<=VMAX;i++)
            if(B[i]&&(!B[i|val])&&(!tmp[i|val]))
            {
                nrelem++;
                tmp[i|val]=1;
            }
        if(K>=nrelem&&nrelem) {rez.push_back(val);K-=nrelem;B|=tmp;}
    }
    cout<<rez.size()<<"\n";
    for(auto it:rez)cout<<it<<" ";
    return 0;
}
