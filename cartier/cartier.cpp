#include<fstream>
#include<math.h>
using namespace std;
ifstream f("cartier.in");
ofstream g("cartier.out");
int n,m,l,hi[5000],i,k=0,maxh=0,nrmaxh=1,sl,a,b,r,o,j,gasit,maxc,sf;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>m;
       o=(int)sqrt((double)m);
        while(m%o!=0)
            o--;
		  if(o>m/o)
		  {
		    hi[i]=o;l=m/o;
          }
	 	  else
            {
                hi[i]=m/o;l=o;
            }

           sl+=l;
           if(hi[i]>maxh)
        {
                maxh=hi[i];nrmaxh=1;
        }
		else if(hi[i]==maxh)
		nrmaxh++;
	}
  maxc=1;sf=1;
	for(i=1;i<=n && maxc<n;i++)
	{
        for(j=n;j>=i && maxc<j-i+1;j--)
		{
			a=hi[i];b=hi[j];
			while(a!=b)
                if(a>b)a=a-b;
			    else b=b-a;

			if(a!=1){sf=j;break;}
	    }
		if(sf-i+1>maxc)maxc=sf-i+1;
	}
    g<<nrmaxh<<"\n"<<sl<<"\n"<<maxc;
    f.close();g.close();
    return 0;
}
