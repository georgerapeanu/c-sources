#include <vector>
#include <bitset>
using namespace std;
class MappingABC2
{
	public:
	int countStrings(vector <int> t)
	{
		int N=t.size();
		long long rez=0,tmp;
		short pot[55];
		int nrval[]={0,1,1,2,1,2,2,3};
		const int MOD=1000000007;
		bitset<55> E;
		for(int i=0;i<N;i++)
			E[t[i]]=1;
		for(int i=0;i<N-2;i++)
		{
			for(int j=i+1;j<N-1;j++)
			{
				for(int k=j+1;k<N;k++)
				{
					for(int ind=0;ind<=51;ind++)
						pot[ind]=7;
					for(int ind=0;ind<i;ind++)
					{
						pot[t[ind]]&=3;
					}
					pot[t[i]]&=4;
					for(int ind=i+1;ind<j;ind++)
						pot[t[ind]]&=5;
					pot[t[j]]&=2;
					for(int ind=j+1;ind<k;ind++)
						pot[t[ind]]&=6;
					pot[t[k]]&=1;
					tmp=1;
					for(int i=0;i<=50;i++)
					{
						if(E[i])
							tmp=(tmp*nrval[pot[i]])%MOD;
					}
					rez=(rez+tmp)%MOD;
				}
			}
		}
		return rez;
	}
};
