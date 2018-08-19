#include <iostream>
#include <bitset>
using namespace std;
int fr[100005];
bitset<100005> fost;
int a,N;
int V[100005];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        fost[V[i]]=1;
        fr[V[i]]++;
    }
    int urez=1;
    for(int i=1;i<=N;i++)
    {
        if(fr[V[i]]==1&&V[i]<=N)
        {
            cout<<V[i]<<" ";
        }
        else
        {
            while(fost[urez])
                urez++;
            cout<<urez<<" ";
            urez++;
        }
        fr[V[i]]--;
    }
    return 0;
}
