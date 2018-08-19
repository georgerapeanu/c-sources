#include <iostream>
using namespace std;
long long x,l,i,n,st[100001],dr[100001],ultim=-1,nr;
void quickSort( int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = dr[(left + right) / 2];

      /* partition */
      while (i <= j) {
            while (dr[i] < pivot)
                  i++;
            while (dr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = dr[i];
                  dr[i] = dr[j];
                  dr[j] = tmp;
                  tmp=st[i];
                  st[i]=st[j];
                  st[j]=tmp;
                  i++;
                  j--;
            }
      };

      /* recursion */
      if (left < j)
            quickSort(left, j);
      if (i < right)
            quickSort(i, right);
}
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>l>>x;
        st[i]=x;
        dr[i]=x+l;
    }
    quickSort(1,n);
    for(i=1;i<=n;i++)
    {
        if(ultim<=st[i])
            {nr++;ultim=dr[i];}
    }
    cout<<nr;
    return 0;
}
