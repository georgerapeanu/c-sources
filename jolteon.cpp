#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
 
using namespace std;
 
FILE *f = fopen("jolteon.in","r");
FILE *g = fopen("jolteon.out","w");
 
class Batog{
 
private:
 
	const int BUCK_SZ = 230;
 
	int n;
	vector<int> bucket;
	vector<int> l;
	vector<int> r;
	vector<long long> bucket_xor;
	vector<long long> v;
	vector<pair<long long,int> > xors;
 
	int how_many_equal(int buck,long long val){
		int st = l[buck] - 1,dr = r[buck];
 
		while(dr - st > 1){
			int mid = (st + dr) / 2;
			if(xors[mid].first < val){
				st = mid;
			}
			else{
				dr = mid;
			}
		}
 
		int fpos = st;
 
		st = l[buck] - 1,dr = r[buck];
 
		while(dr - st > 1){
			int mid = (st + dr) / 2;
			if(xors[mid].first <= val){
				st = mid;
			}
			else{
				dr = mid;
			}
		}
 
		int lpos = st;
		return lpos - fpos;
	}
 
public:
 
	Batog(vector<long long> &v){
		this->v = v;
		n = v.size();
		bucket.resize(n);
		xors.resize(n);
 
		for(int i = 0,buck = 0;i < n;i += BUCK_SZ,buck++){
			l.push_back(i);
			r.push_back(min(n,i + BUCK_SZ));
			bucket_xor.push_back(0);
 
			long long xo = 0;
 
			for(int j = l[buck];j < r[buck];j++){
				bucket[j] = buck;
				bucket_xor[buck] ^= v[j];
				xo ^= v[j];
				xors[j] = make_pair(xo,j);
			}
			sort(xors.begin() + l[buck],xors.begin() + r[buck]);
		}
	}
 
	void update(int pos,long long val){
		for(int i = l[bucket[pos]];i < r[bucket[pos]];i++){
			if(xors[i].second >= pos){
				xors[i].first ^= val;
			}
		}
 
		sort(xors.begin() + l[bucket[pos]],xors.begin() + r[bucket[pos]]);
 
        bucket_xor[bucket[pos]] ^= val;
		v[pos] ^= val;
	}
 
	long long query(int pos){
		int buck = bucket[pos];
		int ans = 0;
		long long xo = 0;
		while(pos < r[buck]){
			xo ^= v[pos];
			ans += (xo == 0);
			pos++;
		}
 
		for(int j = buck + 1;j <= bucket[n - 1];j++){
			ans += how_many_equal(j,xo);
			xo ^= bucket_xor[j];
		}
 
		return ans;
	}
};
 
 
const int NMAX = 1e5;
const int VMAX = 1e6;
 
int n;
long long hsh[VMAX + 5];
int initial[NMAX + 5];
int last[VMAX + 5];
vector<long long> v;
 
const int LEN = 1 << 14;
char buff[LEN];
int ind = LEN - 1;
 
int i32(){
    int ans = 0;
 
    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }
 
    while(buff[ind] >= '0' && buff[ind] <= '9'){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }
    return ans;
}
 
 
int main(){
 
	for(int i = 0;i <= VMAX;i++){
		hsh[i] = (((long long)rand()) << 32) ^ (((long long)rand()));
	}
 
	n = i32();
 
	for(int i = 0;i < n;i++){
		initial[i] = i32();
		v.push_back(hsh[initial[i]]);
	}
 
	Batog stuff(v);
 
	long long ans = 0;
 
	for(int i = n - 1;i >= 0;i--){
		if(last[initial[i]]){
			stuff.update(last[initial[i]],hsh[initial[i]]);
		}
		last[initial[i]] = i;
		stuff.update(last[initial[i]],hsh[initial[i]]);
		ans += stuff.query(i);
	}
 
	fprintf(g,"%lld",ans);
 
	fclose(f);
	fclose(g);
 
	return 0;
}