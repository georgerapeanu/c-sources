#include<iostream>
#include<algorithm>
using namespace std;
int N,L[205];
int rez;
int main()
{
    cin>>N;
    for(int i=1;i<=2*N;i++)cin>>L[i];
    sort(L+1,L+1+2*N);
    for(int i=1;i<=2*N;i+=2)rez+=L[i];
    cout<<rez;
    return 0;
}
