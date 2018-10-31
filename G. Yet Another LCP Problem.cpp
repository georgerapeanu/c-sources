#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 2e5;
const int LGMAX = 18;

int n,q;
char c[NMAX + 5];

int sa[NMAX + 5];
int inv_sa[NMAX + 5];
int lcp[NMAX + 5];
int pos[NMAX + 5];
int tmp[NMAX + 5];
int gap;

bool cmp(int i,int j){
	if(pos[i] != pos[j]){
		return pos[i] < pos[j];
	}
	
	i += gap;
	j += gap;
	
	if(i > n || j > n){
		return n - i + 1 <= n - j + 1;
	}
	return pos[i] < pos[j];
}

int RMQ[LGMAX + 1][NMAX + 1];
int lg2[NMAX + 5];

int q_RMQ(int st,int dr){
	int len = lg2[dr - st + 1];
	return min(RMQ[len][dr],RMQ[len][st + (1 << len) - 1]);
}

int get_lcp(int x,int y){
	if(x == y){
		return n - x + 1;
	}
	int st = inv_sa[x];
	int dr = inv_sa[y];
	if(st > dr){
		swap(st,dr);
	}
	return q_RMQ(st,dr - 1);
}

long long solve(vector<int> &a){
	vector<int> b;
	for(auto it:a){
		b.push_back(inv_sa[it]);
	}
	sort(b.begin(),b.end());
	
	vector< pair<int,int> > st;
	long long sum = 0;
	
	long long ans = 0;
	
	for(int i = 0;i < (int)b.size();i++){
		if(i){
			pair<int,int> up = make_pair(get_lcp(sa[b[i - 1]],sa[b[i]]),0);
		
			while(!st.empty() && st.back().first >= up.first){
				up.second += st.back().second;
				sum -= 1LL * st.back().second * st.back().first;
				st.pop_back();
			}
			
			if(up.second){
				st.push_back(up);
			}
			
			sum += 1LL * up.first * up.second;
			
			ans += sum;
		}
		st.push_back(make_pair(n - sa[b[i]] + 1,1));
		sum += n - sa[b[i]] + 1;
	}
	return ans;
}

int main(){

	fscanf(stdin,"%d %d\n",&n,&q);
	fgets(c + 1,NMAX + 5,stdin);
	
	for(int i = 1;i <= n;i++){
		sa[i] = i;
	}
	
	sort(sa + 1,sa + 1 + n,[&](int a,int b){return c[a] < c[b];});
	
	for(int i = 1;i <= n;i++){
		pos[sa[i]] = (c[sa[i]] != c[sa[i - 1]]) + pos[sa[i - 1]];
	}
	
	for(gap = 1;gap <= n;gap *= 2){
		sort(sa + 1,sa + 1 + n,cmp);
		tmp[sa[1]] = 1;
		for(int i = 2;i <= n;i++){
			tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1],sa[i]);
		}
		
		for(int i = 1;i <= n;i++){
			pos[i] = tmp[i];
		}
	}
	
	for(int i = 1;i <= n;i++){
		inv_sa[sa[i]] = i;
	}
	
	for(int i = 1;i <= n;i++){
		int wh = inv_sa[i];
		if(wh == n){
			continue;
		}
		int nxt = sa[wh + 1];
		while(i + lcp[wh] <= n && nxt + lcp[wh] <= n && c[i + lcp[wh]] == c[nxt + lcp[wh]]){
			lcp[wh]++;
		}
		lcp[inv_sa[i + 1]] = max(lcp[inv_sa[i + 1]],lcp[wh] - 1);
	}
	
	lg2[0] = -1;
	
	for(int i = 1;i <= n;i++){
		lg2[i] = 1 + lg2[i / 2];
		RMQ[0][i] = lcp[i];
	}
	
	for(int j = 1;j <= LGMAX;j++){
		for(int i = 1;i <= n;i++){
			RMQ[j][i] = RMQ[j - 1][i];
			if(i >= (1 << (j - 1))){
				RMQ[j][i] = min(RMQ[j][i],RMQ[j - 1][i - (1 << (j - 1))]);
			}
		}
	}

	while(q--){
		int k,l;
		vector<int> a,b;
		scanf("%d %d",&k,&l);
		for(int i = 1;i <= k;i++){
			int val;
			scanf("%d",&val);
			a.push_back(val);
		}
		for(int i = 1;i <= l;i++){
			int val;
			scanf("%d",&val);
			b.push_back(val);
		}
		
		long long ans = 0;
		ans -= solve(a);
		ans -= solve(b);
		for(auto it:b){
			a.push_back(it);
		}
		ans += solve(a);
		printf("%lld\n",ans);
	}
	
	return 0;
}