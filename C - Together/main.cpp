#include <iostream>
using namespace std;
int N;
int fr[100005];
int a;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        if(a)fr[a-1]++;
        fr[a]++;
        fr[a+1]++;
    }
    int rez=0;
    for(int i=1;i<=100000;i++)
    {
        if(fr[i]>fr[rez])rez=i;
    }
    cout<<fr[rez];
    return 0;
}
