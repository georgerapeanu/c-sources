#include <iostream>

using namespace std;
long long A,B,K;
long long fi(long long a,long long b,long long K)
{
    if(a==0&&b==0)return 0;
    if(b==0)
    {
        if(K==1)return a;
        K--;
        return K%3==1 ? 0:a;
    }
    if(a==0)
    {
        return K%3==1 ? 0:b;
    }
    if(K==1)return a;
    if(K==2)return b;
    if(a<b)
    {
        if(K==1)return a;
        return fi(b,b-a,K-1);
    }
    long long rap=a/b;
    if(rap%2==0)
    {
        if(K<=3*(rap/2))
        {
            if(K%3==2)return b;
            if(K%3==1)return a-(2*(K/3)*b);
            return a-((2*(K/3-1)+1)*b);
        }
        return fi(a-rap*b,b,K-(3*(rap/2)));
    }
    else
    {
        if(K<=3*(rap/2)+1)
        {
            if(K%3==1)return a-(2*(K/3)*b);
            if(K%3==2)return b;
            return a-((2*(K/3-1)+1)*b);
        }
        return fi(b,a-rap*b,K-(3*(rap/2)+1));
    }

}
int main()
{
    cin>>A>>B>>K;
    cout<<fi(A,B,K);
    return 0;
}
