#include <iostream>
#include <bitset>
#include <vector>
using namespace std;
unsigned long long nr;
bitset<100000> B;
vector <long long> P;
int main()
{
    B[0]=B[1]=1;
    for(long long i=2;i*i<100000;i++)
    {
        if(!B[i])
        {
            P.push_back(i);
            for(long long j=i*i;j<100000;j+=i)
                B[j]=1;
        }
    }
    cin>>nr;
    long long prod=1,prev=1,i=0;
    while(prod%prev==0&&prod>0&&prod<=nr)
    {
        prev=P[i];
        prod*=P[i];
        i++;
    }
    cout<<i;
    return 0;
}
