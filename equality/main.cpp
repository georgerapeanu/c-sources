#include <map>
#include <iostream>
using namespace std;
int val,nr,N,K;
map<int,int> M;
int main() {
    cin>>N>>K;
    for(int i=1;i<=N;i++){cin>>val;M[val]++;}
    while(M.rbegin()->first-M.begin()->first>K)
    {
        int m=min(M.rbegin()->second,M.begin()->second);
        int b=M.rbegin()->first;
        int a=M.begin()->first;
        M[a+1]+=m;
        M[b-1]+=m;
        M[a]-=m;
        M[b]-=m;
        nr+=m;
        if(!M[a])M.erase(M.find(a));
        if(!M[b])M.erase(M.find(b));
    }
    cout<<nr;
    return 0;
}
