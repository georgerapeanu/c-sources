#include <iostream>
#include <cmath>
using namespace std;
long long n,maxim;
int calcul(long long nr)
{
    long long i=2,cnr=nr,putere=0;
    while(cnr!=1&&i<=sqrt(nr)&&putere<2)
    {
        putere=0;
        while(cnr%i==0)
        {
            cnr/=i;
            putere++;
        }
        i++;
    }
    if(putere>=2)
    return 0;
    return 1;
}
int main()
{
    long long i=0;
    cin>>n;
    for(i=1;i<=sqrt(n)&&(i>maxim||n/i>maxim);i++)
    {
        if(n%i==0)
        {
            if(calcul(n/i))
            {
                if(maxim<n/i)
                maxim=n/i;
            }
            if(calcul(i))
            {
                if(maxim<i)
                maxim=i;
            }
        }

    }
    cout<<maxim;
    return 0;
}
