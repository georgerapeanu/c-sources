#include<fstream>
using namespace std;
ifstream f("paranteze.in");
ofstream g("paranteze.out");
int n,i,j,L,x[5001],v[5001],cap0,cap2,gasit;
int main()
{
f>>n;
for(i=1;i<=n;i++)
 {
    f>>L;
    for(j=1;j<=L;j++)
        f>>x[j];
    cap0=0;
    cap2=0;
    gasit=1;
    j=1;
    while ((gasit==1)&&(j<=L))
      {
        switch(x[j])
        {
          case 0:v[j]=cap0;cap0=j;break;
          case 2:v[j]=cap2;cap2=j;break;
          case 1: if (cap0==0) gasit=0;
             else
               if (cap2>cap0) gasit=0;
               else cap0=v[cap0];
               break;
          case 3: if (cap2==0) gasit=0;
             else
               if (cap0>cap2) gasit=0;
               else cap2=v[cap2];
               break;
        }
         j++;
      }
    if ((cap0>0)||(cap2>0)) gasit=0;
    if(gasit==1)  g<<1<<"\n";
    else g<<0<<"\n";
 }
  f.close();g.close();
  return 0;
}

