#include <iostream>
#define x first.first
#define y first.second
#define ind second
using namespace std;
int N,S;
pair<pair<int,int>,int> V[100005];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)cin>>V[i].x;
    for(int i=1;i<=N;i++){cin>>V[i].y;S+=V[i].y;}
    for(int i=1;i<=N;i++)V[i].ind=i;
    sort(V+1,V+1+N);
    int k=N/2+1,suma=0;
    cout<<k<<"\n";
    if(N%2==1)
    {
        for(int i=1;i<=N;i+=2)
            suma+=V[i].y;
        if(suma*2<=S)
        {
            for(int i=2;i<=N;i+=2)

        }
    }
    return 0;
}
