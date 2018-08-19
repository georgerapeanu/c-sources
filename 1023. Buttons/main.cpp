#include <iostream>
using namespace std;
int K,rez;
int main()
{
    cin>>K;
    rez=3;
    while(K%rez!=0) rez++;
    cout<<rez-1;
    return 0;
}
