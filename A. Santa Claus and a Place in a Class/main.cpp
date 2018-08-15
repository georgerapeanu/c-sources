#include <iostream>

using namespace std;
int N,M,K,i,j;
char c;
int main()
{
    cin>>N>>M>>K;
    if(K%2==0)
        c='R';
    else
        c='L';
    K=K-(1-K%2)-1;
    j=K/(2*M)+1;
    i=(K%(2*M))/2+1;
    cout<<j<<" "<<i<<" "<<c;
    return 0;
}
