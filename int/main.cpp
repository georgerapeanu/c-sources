#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
FILE *f,*g;
typedef pair<int,int> pereche;
pereche v[50001];
int ultim=-2000000001,i,n,ctr;
void swap(int left,int right)
{
    pereche temp;
    temp.first=v[left].first;
    temp.second=v[left].second;
    v[left].first=v[right].first;
    v[left].second=v[right].second;
    v[right].first=temp.first;
    v[right].second=temp.second;
}
void quickSort(int left, int right) {
      int i = left, j = right;
      int pivot = v[(left+right)/2].second;
      /* partition */
      while (i <= j) {
            while (v[i].second < pivot)
                  i++;
            while (v[j].second > pivot)
                  j--;
            if (i <= j) {
                  swap(i,j);
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
    f=fopen("int.in","r");
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d %d",&v[i].first,&v[i].second);
    }
    fclose(f);
    quickSort(1,n);
    for(i=1;i<=n;i++)
    {
        if(ultim<=v[i].first)
        {
            ultim=v[i].second;
            ctr++;
        }
    }
    g=fopen("int.out","w");
    fprintf(g,"%d",ctr);
    fclose(g);
    return 0;
}
