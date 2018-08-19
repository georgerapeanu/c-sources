#include <fstream>
using namespace std;
ifstream f("1.in");
ofstream g("1.out");
int v[100];
void merge(int l,int m, int h) //0 1 2
{
    int arr1[10],arr2[10],n1,n2,i,j,k;
    n1=m-l+1; //2
    n2=h-m; //1
    for(i=0;i<n1;i++)
    arr1[i]=v[i+l];
    for(j=0;j<n2;j++)
    arr2[j]=v[j+m+1];
    arr1[i]=99999;
    arr2[j]=99999;i=j=0;
    for(k=l;k<=h&&arr1[i]!=99999&&arr2[j]!=99999;k++)
    {
        if(arr1[i]>arr2[j])
        {v[k]=arr2[j];j++;}
        else
        {v[k]=arr1[i];i++;}
    }
    if(arr1[i]==99999)
    {
        while(k<=h)
        {
            v[k]=arr2[j];
            k++;
            j++;
        }
    }
    if(arr2[j]==99999)
    {
        while(k<=h)
        {
            v[k]=arr1[i];
            k++;
            i++;
        }
    }
}
void merge_sort(int low, int high)
{
    int mid;
    mid=(low+high)/2;
    if(low<high)
    {
        merge_sort(low,mid);
        merge_sort(mid+1,high);
        merge(low,mid,high);
    }
}
int main()
{
    int n,i;
    f>>n;
    for(i=0;i<n;i++)
    {
        f>>v[i];
    }
    merge_sort(0,n-1);
    for(i=0;i<n;i++)
    g<<v[i]<<" ";
    f.close();g.close();
    return 0;
}
