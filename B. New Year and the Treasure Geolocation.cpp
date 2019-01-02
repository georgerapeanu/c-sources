#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int,int> > vec;
vector<pair<int,int> > points;

int main(){
	int n;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		points.push_back({x,y});
	}
	for(int i = 1;i <= n;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		vec.push_back({x,y});
	}
	sort(points.begin(),points.end());
	sort(vec.begin(),vec.end());
	printf("%d %d\n",points[0].first + vec.back().first,points[0].second + vec.back().second);
	return 0;
}