#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int n,m;
string s[2005];
int up[2005][2005];

struct dsu_node_t{
	int h,w,father,sz;
};

dsu_node_t dsu[2005];
bool active[2005];

int dsu_fi(int nod){
	if(!dsu[nod].father){
		return nod;
	}
	return dsu[nod].father = dsu_fi(dsu[nod].father);
}

void dsu_u(int x,int y,long long &ans){
	x = dsu_fi(x);
	y = dsu_fi(y);
			
	int h,w,w1;
	
	if(dsu[x].h < dsu[y].h){
		h = dsu[x].h;
		w = dsu[x].w;
		w1 = dsu[y].w;
	}
	else{
		h = dsu[y].h;
		w = dsu[y].w;
		w1 = dsu[x].w;
	}
	
	long long s1 = 1LL * (w) * (w + 1) / 2;
	long long s = 1LL * (w1) * (w1 + 1) / 2;
	
	ans += 1LL * (1LL * (1 + h) * h / 2) * (w1 * s1 + w * s);
	
	if(dsu[x].sz < dsu[y].sz){
		dsu[y].sz += dsu[x].sz;
		dsu[x].father = y;
		dsu[y].w += dsu[x].w;
		dsu[y].h = h;
	}
	else{
		dsu[x].sz += dsu[y].sz;
		dsu[y].father = x;
		dsu[x].w += dsu[y].w;
		dsu[x].h = h;
	}
}

void activate(pair<int,int> a,long long &ans){
	dsu[a.second] = {a.first,1,0,1};
	active[a.second] = true;
	ans += 1LL * (1 + a.first) * a.first / 2;

	
	if(active[a.second + 1]){
		dsu_u(a.second,a.second + 1,ans);
	}
	
	if(active[a.second - 1]){
		dsu_u(a.second,a.second - 1,ans);
	}
	
}

void init_dsu(){
	memset(dsu,0,sizeof(dsu));
	memset(active,0,sizeof(active));
}

int main(){
	
	cin >> n >> m;
	
	for(int i = 1;i <= n;i++){
		cin >> s[i];
		s[i] = " " + s[i];
	}
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			up[i][j] = (s[i][j] != '#') * (up[i - 1][j] + 1);
		}
	}
	
	long long ans = 0;
	
	for(int i = 1;i <= n;i++){
		vector<pair<int,int> > v;
		for(int j = 1;j <= m;j++){
			v.push_back({up[i][j],j});
		}
		sort(v.begin(),v.end());
		reverse(v.begin(),v.end());
		init_dsu();
		for(auto it:v){
			activate(it,ans);
		}
	}
	
	cout << ans;
	
	return 0;
}