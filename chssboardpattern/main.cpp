#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
class ChessboardPattern
{
	char C[3]=".X";
	int ind;
	public:
	vector<string> makeChessboard(int N,int M)
	{
		if(N%2==0) ind=1;
		else ind=0;
		vector<string> rez;
		string tmp;
		for(int i=0;i<N;i++)
		{
			tmp.clear();
			for(int j=0;j<M;j++)
			{
				tmp.push_back(C[ind]);
				ind=(ind+1)%2;
			}
			rez.push_back(tmp);
		}
		return rez;
	}
};
vector<string> t;
int main()
{
    ChessboardPattern a;
    t=a.makeChessboard(8,8);
    for(auto it:t)
    {
        for(auto it2:it)
            printf("%c",it2);
        printf("\n");
    }
    return 0;
}
