#include <iostream>
using namespace std;
long long n,l[500010],r[500010],i,nr,ultim=-10;
void swap(int x,int y)
{
    int tmp;
    tmp=l[x];
    l[x]=l[y];
    l[y]=tmp;
    tmp=r[x];
    r[x]=r[y];
    r[y]=tmp;
}
void qs(int left,int right)
{
    int pivot=r[(left+right)/2];
    int i,j;
    i=left;
    j=right;
    while(i<=j)
    {
        while(r[i]<pivot) i++;
        while(r[j]>pivot) j--;
        if(i<=j)
        {
            swap(i,j);
            i++;
            j--;
        }
    }
    if(i<right)
    qs(i,right);
    if(j>left)
    qs(left,j);
}
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>l[i]>>r[i];
    }
    qs(1,n);
    for(i=1;i<=n;i++)
    {
        if(ultim<l[i])
        {
            ultim=r[i];
            nr++;
        }
    }
    cout<<nr;
    return 0;
}
