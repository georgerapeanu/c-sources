#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
using namespace std;
ifstream f("grad.in");
ofstream g("grad.out");
int n,i,nrcuv,k,nrgraduri;
char v[255],grad[255];
int main()
 {
  f>>n;
  while(f>>v)
  {
      nrcuv++;
      for(i=0;i<strlen(v);i++)
      {
          grad[k]+=v[i]-'a'+1;
      }
      k++;
  }
  sort(grad,grad+k);
  for(i=0;i<k;i++)
  {
      if(grad[i]!=grad[i-1])
      {
          nrgraduri++;
      }
  }
  g<<nrcuv<<"\n"<<nrgraduri;
  f.close();g.close();
    return 0;
}
