#include <fstream>
#include <cmath>
using namespace std;
ifstream f("cifru5.in");
ofstream g("cifru5.out");
int N,Apar[10],MAX,NrMin,Cif,Cate,i,j, Nr, x;
int main()
{
	f>>N; MAX = 0; Cif = -1; Cate = 0;
	for(i=1;i<=N;i++)
	{
		f>>x;
		Apar[x]++;
		if(MAX < x) MAX = x;
	}
	NrMin = 10 * N + 1;
	for(i=0;i<=9;i++)
	{
			Nr = 0;
			for(j=0;j<=9;j++)
				if(Apar[j] && j!=i)
				  Nr += abs(j-i) <= 10 - abs(j-i) ? Apar[j]*abs(j-i) : Apar[j]*(10 - abs(j-i));
			if(Nr<NrMin) NrMin = Nr, Cif = i, Cate = 1;
			else if(Nr==NrMin) Cate++;
	}
	g<<MAX<<'\n'<<NrMin<<'\n'<<Cif<<'\n'<<Cate<<'\n';

	g.close();
	f.close();
	return 0;
}
