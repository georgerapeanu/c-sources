#include <iostream>
using namespace std;
long i,j,tmp=0,v[101],x[101],n,st,s;
void quick(long left,long right)
{
    long pivot=x[(left+right)/2];
    i=left;
    j=right;
    while(i<=j)
    {
        while(x[i]<pivot)i++;
        while(x[j]>pivot)j--;
        if(i<=j)
        {
            tmp=x[i];
            x[i]=x[j];
            x[j]=tmp;
            tmp=v[i];
            v[i]=v[j];
            v[j]=tmp;
            i++;j--;
        }
    }
    if(j>left)
    quick(left,j);
    if(i<right)
    quick(i,right);
}
int main()
{
    std::cin>>n;
    for(i=1;i<=n;i++)
    {
        std::cin>>x[i]>>v[i];
    }
    quick(1,n);
    st=1;
    while(x[st]<0)
    st++;
    st--;
    if(st>=n-st)
    {
        for(i=st-(n-st);i<=st;i++)
        s+=v[i];
        for(i=st+1;i<=n;i++)
        s+=v[i];
    }
    else
    {
        for(i=1;i<=st;i++)
        s+=v[i];
        for(i=st+1;i<=2*st+1;i++)
        s+=v[i];
    }
    std::cout<<s;
    return 0;
}
