#include <iostream>
#define F first
#define S second
using namespace std;
long long n,d,i,j,sumf,maxi;
typedef pair<long long,long long> vec;
vec v[100001];
void quickSort(long long left, long long right) {
      long long i = left, j = right;
      vec tmp;
      long long pivot;
      pivot = v[(left + right) / 2].F;
      while (i <= j) {
            while (v[i].F< pivot)
                  i++;
            while (v[j].F > pivot)
                  j--;
            if (i <= j) {
                  tmp = v[i];
                  v[i] = v[j];
                  v[j] = tmp;
                  i++;
                  j--;
            }
      }

      if (left < j)
            quickSort(left, j);
      if (i < right)
            quickSort(i, right);
}
long long abs(long long nr)
{
    if(nr<0)
    return nr*-1;
    return nr;
}
int main()
{
    cin>>n>>d;
    for(i=1;i<=n;i++)
    cin>>v[i].F>>v[i].S;
    quickSort(1,n);
    for(i=1;i<=n;i++)
    {
        sumf=0;
       for(j=i;j<=n&&abs(v[j].F-v[i].F<d);j++)
       {
           sumf+=v[j].S;
       }
       maxi=maxi>sumf ? maxi:sumf;
    }
    cout<<maxi;
    return 0;
}
