#include<fstream>
using namespace std;
int n;
int m;
int b;
int a;
int k;
int i, f, r, rmax = -1;
ifstream fin("cozonaci.in");
ofstream fout("cozonaci.out");
int main()
{
fin >> n;
		for (i = 1; i <= n; i++)
	{
		fin >> f >> r;
		if ( r > rmax )
			rmax = r;
		if ( i == 1 )
		{
			a = f - r;
			k += a;
			m = a;
		}
		else
		{
			b = f - r;
			a = m;
			k += b;
			if (a == 0)
				m = b;
			else
				if (b == 0)
					m = a;
				else
				{
					while (a != b)
						if (a > b)
							a = a - b;
						else
							b = b - a;
					m = a;
				}
			if ( m <= rmax )
			{
			    fout << "-1\n";
			    return 0;
			}
		}
	}

	fout << k << '\n';
	fout << m;
	fin.close();
	fout.close();
	return 0;
}
