#include <iostream>
using namespace std;
int A,B,N;
int nr;
int sens=0;
int V[100001];
int main()
{
    cin>>A>>B;
    N=B-A+1;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
    }
    for(int i=1;i<=N;i++)
    {
        while(i<N&&V[i]==V[i+1])
            i++;
        if(i<N&&V[i]<V[i+1])
            sens=1;
        else
            sens=-1;
        while(i<N&&V[i]*sens<=V[i+1]*sens)
        {
            i++;
        }
        nr++;
    }
    cout<<nr;
    return 0;
}
