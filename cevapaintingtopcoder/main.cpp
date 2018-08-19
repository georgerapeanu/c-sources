#include <iostream>
#include <vector>
using namespace std;
struct Painting
{
	int largestBrush(vector<string> a)
	{
		int N=a.size(),M=a[0].size();
		int mat[55][55];
		bool tmp[55][55];
		for(int i=0;i<=N||i<=M;i++)
			mat[i][0]=mat[0][i]=0;
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=M;j++)
			{
				mat[i][j]=mat[i-1][j]+mat[i][j-1]-mat[i-1][j-1]+(a[i-1][j-1]=='B');
			}
		}
		int rez=0;
        for(int i=(1<<30);i;i>>=1)
		{
			if(rez+i-1>N||rez+i-1>M)
				continue;
			rez+=i;
			bool ok=0;
			for(int i=0;i<=N;i++)
                for(int j=0;j<=M;j++)
                    tmp[i][j]=0;
            for(int i=1;i<=N-rez+1;i++)
			{
				for(int j=1;j<=M-rez+1;j++)
				{
                    if(mat[i+rez-1][j+rez-1]-mat[i+rez-1][j-1]-mat[i-1][j+rez-1]+mat[i-1][j-1]==rez*rez)
                    {
                        for(int i1=i;i1<i+rez;i1++)
                        {
                            for(int j1=j;j1<j+rez;j1++)
                            {
                                tmp[i1][j1]=1;
                            }
                        }
                    }
				}
			}
			for(int i=1;i<=N;i++)
                for(int j=1;j<=M;j++)
                    ok|=((!tmp[i][j])&&a[i-1][j-1]=='B');
			if(ok)
				rez-=i;
		}
		return rez;
	}
};
int main()
{
    Painting a;

    cout<<a.largestBrush({"BBBB",
 "BBBB",
 "WBBB",
 "BBBB",
 "BBBB",
 "BBBB"});
    return 0;
}
