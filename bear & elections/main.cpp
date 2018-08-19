#include <iostream>
using namespace std;
int arr[1001],n,nr=1,num=0,use;
void quickSort(int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  if(nr==i)
                  nr=j;
                  else if(nr==j)
                  nr=i;
                  i++;
                  j--;
            }
      };

      if (left < j)
            quickSort(left, j);
      if (i < right)
            quickSort(i, right);
}
int main()
{
    int i;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>arr[i];
    }
    quickSort(1,n);
    i=n;
    while(arr[nr]>=arr[n]-num)
    {
        while(arr[i-1]=arr[i])
        {
            i--;
            num++;
        }
        if(arr[nr]<arr[n]-num)
        {arr[nr]+=num;use+=num;for(int j=i;j<=n;j++)arr[j]--;}
    }
    use+=arr[n]-arr[nr];
    cout<<use;
}
