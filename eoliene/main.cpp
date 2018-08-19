#include <cstdio>
using namespace std;
FILE *f,*g;
long long x[1001],l,i,n,st[1001],dr[1001],ultim=-5001,nr;
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
    f=fopen("eoliene.in","r");
    g=fopen("eoliene.out","w");
    fscanf(f,"%lld",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%lld",&x[i]);
    }
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%lld",&l);
        st[i]=x[i]-l;
        dr[i]=x[i]+l;
    }
    quickSort(1,n);
    for(i=1;i<=n;i++)
    {
        if(ultim<st[i])
            {nr++;ultim=dr[i];}
    }
    fprintf(g,"%lld",n-nr);
    fclose(f);
    fclose(g);
    return 0;
}
