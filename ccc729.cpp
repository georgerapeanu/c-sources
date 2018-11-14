#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("in","r");
FILE *g = fopen("out","w");

const int NMAX = 1e3;
const int MMAX = 1e3;

struct car_t{
	int wh,en;
	int tm;
	int id;
	
	bool operator < (const car_t &other)const{
		if(wh != other.wh){
			return wh < other.wh;
		}
		
		if(en != other.en){
			return en < other.en;
		}
		
		return id < other.id;
	}
	
};

vector<int> lvl2_solver(int nn,int mm,vector<car_t> vv){

	int n,m;
	vector<car_t> v,unentered;
	vector<int> ans;
	bool occupied[NMAX + 5];
	n = nn;
	m = mm;
	unentered = vv;
	sort(v.begin(),v.end());
	ans = vector<int>(m,0);
	
	int cur_time = 0;
	
	while(v.size() || unentered.size()){
		cur_time++;
		
		memset(occupied,0,sizeof(occupied));
		sort(v.begin(),v.end());
		
		
		for(auto &it:v){
			occupied[it.wh] = 1;
		}
		
		vector<car_t> new_u;
		vector<car_t> new_v;
		
		for(auto it:unentered){
			ans[it.id]++;
			if(it.tm > cur_time){
				new_u.push_back(it);
				continue;
			}
			if(!occupied[it.wh - 1] && !occupied[it.wh]){
				new_v.push_back(it);
			}
			else{
				new_u.push_back(it);
			}
		}
		
		unentered = new_u;
		
				
		for(int i = 0;i < (int)v.size();i++){
			ans[v[i].id]++;
			if(v[i].wh == v[i].en){
				;
			}
			else if(i == (int)v.size() - 1 || v[i].wh + 1 != v[i + 1].wh){
				new_v.push_back({v[i].wh + 1,v[i].en,v[i].tm,v[i].id});
			}
			else{
				new_v.push_back(v[i]);
			}
		}
		swap(v,new_v);;
	}
	
	return ans;
}

int main(){
	
	int n,m;
	
	vector<car_t> v;
	
	fscanf(f,"%d\n",&n);
	fscanf(f,"%d\n",&m);

	
	v.resize(m);
	
	for(int i = 0;i < m;i++){
		fscanf(f,"%d,%d,%d\n",&v[i].wh,&v[i].en,&v[i].tm);
		v[i].id = i;
	}
	
	sort(v.begin(),v.end(),[&](car_t a,car_t b){return a.en - a.wh  < b.en - b.wh;});
	
	vector<car_t> input;		
	
	for(auto it:v){
		
		int st = 1,dr = 3e3;
		
		while(dr - st > 1){
			int mid = (st + dr) / 2;
			input.push_back({it.wh,it.en,mid,it.id});
			vector<int> ans = lvl2_solver(n,m,input);
			
			bool ok = true;
			
			if(ans[it.id] > it.tm){
				ok = false;
			}					
			input.pop_back();
			
			if(ok){
				st = mid;
			}
			else{
				dr = mid;
			}
		}
		input.push_back({it.wh,it.en,st,it.id});
	}
	
	vector<int> ans(m,0);
	
	for(auto it:input){
		ans[it.id] = it.tm;
	}
	
	for(int i = 0;i < m;i++){
		fprintf(g,"%d",ans[i]);
		if(i != m - 1){
			fprintf(g,",");
		}
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}