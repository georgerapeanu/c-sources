#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 3e5;
const int inf = 1 << 30;

int n;
pair<int,int> p[NMAX + 5];

int xmax = -inf,xmin = inf,ymax = -inf,ymin = inf;
pair<int,int> st[NMAX + 5];
int len;

void rotate(){
	for(int i = 1;i <= n;i++){
		swap(p[i].first,p[i].second);
		p[i].second *= -1;
	}
}

int solve(){
	sort(p + 1,p + 1 + n,[&](pair<int,int> a,pair<int,int> b){if(a.second != b.second)return a.second > b.second;return a.first < b.first;});
	int ans = 0;
	int right = -inf;
	len = 0;
		
	for(int i = 1;i <= n;i++){
		if(right != -inf && len){
			if(st[len].first < p[i].first){
				goto pula;
			}
			int le = 0,hi = len;
			while(hi - le > 1){
				int mid = (le + hi) / 2;
				if(st[mid].first < p[i].first){
					le = mid;
				}
				else{
					hi = mid;
				}
			}
			
			ans = max(ans,2 * (st[hi].second - p[i].second + right - p[i].first));
		}
	
		pula:;
		right = max(right,p[i].first);
		if(!len){
			st[++len] = p[i];
		}
		else if(st[len].first <= p[i].first){
			st[++len] = p[i];
		}
	}
	return ans;
}

int main(){
	
	scanf("%d",&n);
	
	for(int i = 1;i <= n;i++){
		scanf("%d %d",&p[i].first,&p[i].second);
		xmax = max(p[i].first,xmax);
		xmin = min(p[i].first,xmin);
		ymax = max(p[i].second,ymax);
		ymin = min(p[i].second,ymin);
	}
	
	int ans = 0;
	
	for(int i = 1;i <= 4;i++){
		ans = max(ans,solve());
		rotate();
	}
	
	printf("%d ",ans);
	
	for(int i = 4;i <= n;i++){
		printf("%d ",2 * abs(xmax - xmin) + 2 * abs(ymax - ymin));
	}
	
	return 0;
}