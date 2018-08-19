#include <iostream>
using namespace std;
int i2,i1,v1[],v2[],v3[1000],i3,n1=4,n2=4;
int main()
{
i1 = 0;
i2 = 0;
i3 = 0;
while ( i1 < n1 && i2 < n2 )
{
  if ( v1[i1] < v2[i2] )
    {
    v3[i3] = v1[i1];
    i1++;
  } else
  {
    v3[i3] = v2[i2];
    i2++;
  }
  i3++;
}
while ( i1 < n1 )
{
  v3[i3] = v1[i1];
  i1++;
  i3++;
}
while ( i2 < n2 )
    {
  v3[i3] = v2[i2];
  i2++;
  i3++;
}
}
