#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;

const int MOD_MAX = 500;
const int Q_MAX = 500;
const int V_MAX = (1 << 30);
const int LIKE_HOOD = 4;

FILE *g = fopen("in","w");

map<int,int> is;

int main(){
	
	srand(time(NULL));
	
	int MOD = rand() % MOD_MAX + 1;
	int Q = rand() % Q_MAX + 1;
	
	fprintf(g,"%d\n%d\n",MOD,Q);
	
	vector<pair<int,int> > cv;
	
	for(int i = 1;i <= Q;i++){
		int val = -1;
		while(1){
			val = rand() % V_MAX;
			if(!is[val]){
				break;
			}
		}
		is[val] = 1;
		cv.push_back({val,rand() % V_MAX});
	}
	
	sort(cv.begin(),cv.end());
	
	int sz = 0;
	int wh = 0;
	
	for(int i = 1;i <= Q;i++){
		int l = rand() % MOD;
		int r = rand() % MOD;
		
		if(l > r){
			swap(l,r);
		}
		
		if(sz && rand() % LIKE_HOOD == 0){
			sz--;
			fprintf(g,"2 0 0 %d %d\n",l,r);
		}
		else{
			sz++;
			fprintf(g,"1 %d %d %d %d\n",cv[wh].first,cv[wh].second,l,r);
			wh++;
		}
	}
	
	return 0;
}