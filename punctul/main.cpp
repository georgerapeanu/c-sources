#include <fstream>
#include <algorithm>
using namespace std;
int tip,n,x,y;
ifstream fi("punctul.in");
ofstream fo("punctul.out");
void detxy(int n, int &x, int &y)
{
	int st, dr, nrt;
	nrt=0;
	st=dr=0;
	while (!(n>=st && n<=dr))
	{
		nrt++;
		st=dr+1;
		dr=(nrt+1)*(nrt+1)-1;
	}
	if (nrt%2==1)
		if (2*n<=st+dr)
		{
			x=nrt;
			y=n-st;
		}
		else
		{
			y=nrt;
			x=dr-n;
		}
	else
		if (2*n<=st+dr)
		{
			x=n-st;
			y=nrt;
		}
		else
		{
			x=nrt;
			y=dr-n;
		}
}

void detn(int x, int y, int &n)
{
	int nrt;
	nrt=max(x,y);
	n=nrt*nrt;
	if (x>=y)
		if (nrt%2==1)
			n+=y;
		else
			n+=2*nrt-y;
	else
		if (nrt%2==1)
			n+=2*nrt-x;
		else
			n+=x;
}

int main()
{
	fi>>tip;
	if (tip==1)
	{
		fi>>n;
		detxy(n,x,y);
		fo<<x<<" "<<y<<"\n";
	}
	else
	{
		fi>>x>>y;
		detn(x,y,n);
		fo<<n<<"\n";
	}
	fi.close();
	fo.close();
	return 0;
}
