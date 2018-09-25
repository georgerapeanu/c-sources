#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

FILE *f = fopen("rangemode.in","r");
FILE *g = fopen("rangemode.out","w");

const int NMAX = 1e5;
const int BUCK = 2000;

int n,q;
int v[NMAX + 5];
pair<int,int> ans[NMAX + 5];
int fr[NMAX + 5];
vector< pair<int,int> > query[NMAX + 5];
vector<int> pos[NMAX + 5];

class DynamicRMQ{
private:

    int sz;
    vector<int> bucket;
    vector<int> stuff;
    vector<int> precalc;
    vector<int> l;
    vector<int> r;

    int better(int a,int b){
        if(stuff[a] > stuff[b] || (stuff[a] == stuff[b] && v[a] < v[b])){
            return a;
        }
        return b;
    }

public:

    DynamicRMQ(int n){
        sz = sqrt(n);
        bucket.resize(n + 5);
        stuff.resize(n + 5);
        l.resize(sz + 5);
        r.resize(sz + 5);
        precalc.resize(sz + 5);
        for(int i = 1,buck = 1;i <= n;i += sz,buck++){
            l[buck] = i;
            r[buck] = min(i + sz - 1,n);
            precalc[buck] = i;
            for(int j = i;j < i + sz && j <= n;j++){
                bucket[j] = buck;
            }
        }
    }

    void update(int pos,int val){
        stuff[pos] += val;
        precalc[bucket[pos]] = better(pos,precalc[bucket[pos]]);
    }

    pair<int,int> query(int st,int dr){
        if(bucket[st] == bucket[dr]){
            int ans = st;
            for(int i = st;i <= dr;i++){
                ans = better(ans,i);
            }
            return {v[ans],stuff[ans]};
        }

        int ans = st;

        for(int i = st;i <= r[bucket[st]];i++){
            ans = better(ans,i);
        }

        for(int i = l[bucket[dr]];i <= dr;i++){
            ans = better(ans,i);
        }

        for(int i = bucket[st] + 1;i <= bucket[dr] - 1;i++){
            ans = better(ans,precalc[i]);
        }

        return {v[ans],stuff[ans]};
    }
	
	void afis(){
		for(int i = 1;i <= n;i++){
			printf("%d ",stuff[i]);
		}
		
		printf("\n");
		
		for(int i = 1;i <= sz;i++){
			printf("%d ",precalc[i]);
		}
	}

};

int main(){

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&v[i]);
        pos[v[i]].push_back(i);
    }

    for(int i = 1;i <= q;i++){
        int st,dr;
        fscanf(f,"%d %d",&st,&dr);
        query[dr].push_back({st,i});
    }

	DynamicRMQ a(n);
	
	for(int r = 1;r <= n;r++){
		if(pos[v[r]].size() <= BUCK){
			for(auto it:pos[v[r]]){
				if(it > r){
					break;
				}
				a.update(it,1);
			}
		
			for(auto l:query[r]){
				ans[l.second] = a.query(l.first,r);
			}
		}
	}
	
	for(int i = 1;i <= NMAX;i++){
		if(pos[i].size() > BUCK){
			for(int j = 1;j <= n;j++){
				fr[j] = fr[j - 1] + (v[j] == i);
				for(auto it:query[j]){
					int a = fr[j] - fr[it.first - 1];
					if(a > ans[it.second].second || (a == ans[it.second].second && i < ans[it.second].first)){
						ans[it.second] = {i,a};
					}
				}
			}
		}
	}
	
	for(int i = 1;i <= q;i++){
		fprintf(g,"%d\n",ans[i].first);
	}
	
    return 0;
}
