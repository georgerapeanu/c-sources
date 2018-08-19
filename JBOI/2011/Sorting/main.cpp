#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
int nr,N,rez;
vector<int> V;
int gcd(int a,int b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++){cin>>nr;rez=gcd(abs(nr-i),rez);}
    for(int i=1;i<=rez;i++)if(rez%i==0)V.push_back(i);
    cout<<V.size()<<"\n";
    for(auto it:V)cout<<it<<" ";
    return 0;
}
