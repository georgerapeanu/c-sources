#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("zalmoxis.in","r");
FILE *g = fopen("zalmoxis.out","w");

int n,k;
pair<int,int> v[(int)2e6];
int st[(int)2e6];
int len,sz;

int main(){
	
	fscanf(f,"%d %d",&n,&k);
	
	for(int i = 1;i <= n;i++){
		int val;
		fscanf(f,"%d",&val);
		while(len && st[len] < val){
			v[++sz] = {st[len],1};
			st[len]++;
			k--;
			while(len > 1 && st[len] == st[len - 1]){
				st[--len]++;
			}
		}
		v[++sz] = {val,0};
		st[++len] = val;
		while(len > 1 && st[len] == st[len - 1]){
			st[--len]++;
		}
	}
	
	while(len && st[len] < 30){
		v[++sz] = {st[len],1};
		st[len]++;
		k--;
		while(len > 1 && st[len] == st[len - 1]){
			st[--len]++;
		}
	}
	
	for(int i = 1;i <= sz;i++){
		if(v[i].second == 1 && k){
			if((1 << v[i].first) - 1 <= k){
				k = k - (1 << v[i].first) + 1;
				for(int j = 1;j <= (1 << v[i].first);j++){
					fprintf(g,"0 ");
				}
			}
			else{
				vector<int> secv = {v[i].first};
				
				while((int)secv.size() < k + 1){
					vector<int> nsecv;
					for(int i = 0;i < (int)secv.size();i++){
						if((int)secv.size() - i + 1 + (int)nsecv.size() <= k + 1){
							nsecv.push_back(secv[i] - 1);
							nsecv.push_back(secv[i] - 1);
						}
						else{
							nsecv.push_back(secv[i]);
						}
					}
					secv = nsecv;
				}
				
				for(auto it:secv){
					fprintf(g,"%d ",it);
				}
				
				k = 0;
			}
		}
		
		else{
			fprintf(g,"%d ",v[i].first);
		}
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}