#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int N;
int V[105];
int main() {
     cin>>N;
    for(int i=1;i<=N;i++)
        cin>>V[i];
    if(N==1)
    {
        cout<<2*V[1]<<" 1";
        return 0;
    }
    sort(V+1,V+1+N);
    int i=1;
    if(V[1]==V[2])
    {
        cout<<V[1]<<" "<<N;
    }
    else
    {
        cout<<min(V[2],2*V[1])<<" "<<1;
    }
    return 0;
}
