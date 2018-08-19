#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
struct NiceTable
{
	string isNice(vector<string> t)
	{
		for(int x=0;x<(1<<t.size());x++)
		{
			int y=0;
			for(int j=0;j<t[0].size();j++)
			{
				y|=((x&1)^(t[0][j]-'0'))<<j;
			}
			bool ok=1;
			for(int i=0;i<t.size();i++)
			{
				for(int j=0;j<t[i].size();j++)
				{
				   if((((x>>i)^(y>>j))&1)!=t[i][j]-'0')ok=0;
				}
			}
			if(ok)return "Nice";
		}
		return "Not nice";
	}
};
int main()
{
    NiceTable a;
    cout<<a.isNice({"01","10"});
}
