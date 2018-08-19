#include <iostream>
using namespace std;
int N;
string a;
int main()
{
    cin>>N;
    cin>>a;a+='0';
    int nr=0;
    for(int i=0;i<=N;i++)
    {
        if(a[i]=='1')nr++;
        else {cout<<nr;nr=0;}
    }
    return 0;
}
