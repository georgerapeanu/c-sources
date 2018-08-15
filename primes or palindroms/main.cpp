#include <iostream>
using namespace std;
int ciur[743],maxi,pi[743],rub[743],p,q,i,j;
int ispal(int x)
{
    int tmp=x;
    int k=0;
    while(x){k=k*10+x%10;x/=10;}
    return (tmp==k? 1:0);

}
int main()
{
    std::cin>>p>>q;
    ciur[0]=ciur[1]=1;
    rub[1]=1;
    for(i=2;i<=742;i++)
    {
        pi[i]=pi[i-1];
        rub[i]=rub[i-1]+ispal(i);
        if(!ciur[i])
        {
            pi[i]++;
            for(j=i*i;j<=742;j+=i)
            ciur[j]=1;
        }
        if(pi[i]*q<=rub[i]*p)
        maxi=i;
    }
    if(maxi==0)
    std::cout<<"Palindromic tree is better than splay tree";
    else
    cout<<maxi;
    return 0;
}
