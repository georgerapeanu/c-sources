#include <iostream>
#include <cmath>
using namespace std;
int n,c[100000];
long v[100000],mini[100000],maxi[100000];
int quick(int left,int right)
{
    int i,j,pivot;
    pivot=v[(left+right)/2];
    i=left;
    j=right;
    while(i<=j)
    {
        while(v[i]<pivot)
        i++;
        while(v[j]>pivot)
        j--;
        if(i<=j)
        {
            long aux;
            aux=v[i];
            v[i]=v[j];
            v[j]=aux;
            aux=c[i];
            c[i]=c[j];
            c[j]=aux;
            i++;
            j--;
        }
    }
    if(left<j)
    quick(left,j);
    if(i<right)
    quick(i,right);
}
int main()
{
    int i=0;
    std::cin>>n;
    for(i=1;i<=n;i++)
    {std::cin>>v[i];c[i]=i;}
    quick(1,n);
    for(i=2;i<=n-1;i++)
    {
        if(v[i]-v[i-1]<v[i+1]-v[i])
        mini[c[i]]=v[i]-v[i-1];
        else
        mini[c[i]]=v[i+1]-v[i];
        if(v[i]-v[1]>v[n]-v[i])
        {
            maxi[c[i]]=v[i]-v[1];
        }
        else
        maxi[c[i]]=v[n]-v[i];
    }
    mini[1]=v[2]-v[1];
    maxi[1]=v[n]-v[1];
    mini[n]=v[n]-v[n-1];
    maxi[n]=v[n]-v[1];
    for(i=1;i<=n;i++)
    std::cout<<mini[i]<<" "<<maxi[i]<<"\n";
    return 0;
}
