#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>


using namespace std;

FILE *f = fopen("in","r");
FILE *g = fopen("out","w");

int pos[2005];
int cost[2005];
int weights[2005];
int wh1[2005];
int wh2[2005];

int main(){
	
	int n,m;
	
	fscanf(f,"%d %d\n",&n,&m);

	for(int i = 1;i <= n;i++){
		fscanf(f,"%d",&cost[i]);
	}
	
	vector<int> v(2 * m,0);
	set<pair<int,int> > not_in;
	priority_queue<int,vector<int>,greater<int> > slots;

	for(int i = 1;i <= n;i++){
		slots.push(i);
	}
	
	for(int i = 1;i <= m;i++){
		fscanf(f,"%d",&weights[i]);
	}
	
	int a = 0;
	int ans1 = 0;
	int ans2 = 0;
	long long ans = 0;
	
	for(int i = 0;i < 2 * m;i++){
		fscanf(f,"%d",&v[i]);
		if(v[i] < 0){
			wh2[-v[i]] = i;
			if(not_in.count({wh1[-v[i]],-v[i]})){
				not_in.erase({wh1[-v[i]],-v[i]});
				continue;
			}
			slots.push(pos[-v[i]]);
			if(!not_in.empty()){
				ans += 1LL * cost[slots.top()] * ((weights[not_in.begin()->second] + 99) / 100);
				pos[not_in.begin()->second] = slots.top();
				not_in.erase(not_in.begin());
				slots.pop();
			}
			else{
				a--;
			}
		}
		else{
			wh1[v[i]] = i;
			if(a < n){
				a++;
				ans += 1LL * cost[slots.top()] * ((weights[v[i]] + 99) / 100);
				pos[v[i]] = slots.top();
				slots.pop();
			}
			else{
				not_in.insert({i,v[i]});
			}
		}
		ans1 = max(a,ans1);
		ans2 = max((int)not_in.size(),ans2);
	}
	
	fprintf(g,"%lld\n",ans);
	
	fclose(f);
	fclose(g);
	
	return 0;
}