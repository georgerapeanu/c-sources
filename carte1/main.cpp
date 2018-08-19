#include<fstream>
using namespace std;
ifstream f("carte1.in");
ofstream g("carte1.out");
int n,u[10001],i,p,m,maxim,imax,z,nr;
int main()
{ f>>n;
  for(i=1;i<=n;i++) {f>>p;u[p]=i;}
  for(i=1;i<=n;i++)if(u[i]!=0){nr=1,p=i,m=u[i],z++;
		          while(p<n && u[p+1]>m)nr++,p++,m=u[p],u[p]=0;
		          if(nr>maxim)maxim=nr,imax=z;
		        }
  g<<z<<' '<<imax<<' '<<maxim<<' '<<'\n';
  f.close();g.close();
  return 0;
}
