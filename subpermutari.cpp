#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("subpermutari.in","r");
FILE *g = fopen("subpermutari.out","w");

const int NMAX = 2005;

int n;
int v[NMAX + 5];

vector<int> hashes;

struct hash_t{
	int fst_hash,snd_hash,sign,id;
	
	hash_t(int fst_hash,int snd_hash,int sign,int id){
		this->fst_hash = fst_hash;
		this->snd_hash = snd_hash;
		this->sign = sign;
		this->id = id;
	}
	
	bool operator < (const hash_t &other)const{
		if(fst_hash != other.fst_hash){
			return fst_hash < other.fst_hash;
		}
		
		if(snd_hash != other.snd_hash){
			return snd_hash < other.snd_hash;
		}
		
		if(sign != other.sign){
			return sign < other.sign;
		}
		
		return id < other.id;
	}
	
	bool operator != (const hash_t &other)const{
		return fst_hash != other.fst_hash || snd_hash != other.snd_hash || sign != other.sign;
	}
};

int main(){
	
	fscanf(f,"%d",&n);
	
	for(int i = 1;i <= n;i++){
		fscanf(f,"%d",&v[i]);
		hashes.push_back(0);
	}
	
	long long ans = n * n;
	
	for(int l = 1;l < n;l++){
		vector<hash_t> new_hashes;
		for(int i = 0;i < (int)hashes.size() - 1;i++){
			new_hashes.push_back(hash_t(hashes[i],hashes[i + 1],(v[i + 1] < v[i + 1 + l]),i));
		}
		
		hashes.clear();
		
		sort(new_hashes.begin(),new_hashes.end());
		
		hash_t last_hash = hash_t(-1,-1,-1,-1);
		int fr = 0;
		int id = 0;
		
		vector< pair<int,int> > temp_hashes;
		
		for(int i = 0;i < (int)new_hashes.size();i++){
			if(last_hash != new_hashes[i]){
				ans += fr * fr;
				id++;
				last_hash = new_hashes[i];
				fr = 0;
			}
			
			fr++;
			temp_hashes.push_back(make_pair(new_hashes[i].id,id));
		}
		
		ans += fr * fr;
		
		sort(temp_hashes.begin(),temp_hashes.end());
		
		for(auto it:temp_hashes){
			hashes.push_back(it.second);
		}
	}
	
	fprintf(g,"%lld",ans);
	
	fclose(f);
	fclose(g);
	
	return 0;
}