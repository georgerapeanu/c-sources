#include <cstdio>
#include <algorithm>
#include <vector>
 
using namespace std;
 
FILE *f = fopen("magnet.in","r");
FILE *g = fopen("magnet.out","w");
 
const int NMAX = 1e4;
 
int t;
int n;
vector<int> a;
vector<int> b;
 
bool solve(vector<int> a,vector<int> b,vector< pair<int,int> > start){
	
	// fprintf(stderr,"\n\n\n");
	
	// fprintf(stderr,"init state: ");
	// fprintf(stderr,"a:{");for(auto it:a)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	// fprintf(stderr,"b:{");for(auto it:b)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	// fprintf(stderr,"start:{");for(auto it:start)fprintf(stderr,"{%d,%d},",it.first,it.second);fprintf(stderr,"}\n");
	
	vector<int> diff_a;
	vector<int> diff_b;
	
	for(int i = 1;i < (int)a.size();i++){
		diff_a.push_back(a[i] - a[i - 1]);
		diff_b.push_back(b[i] - b[i - 1]);
		
		if(diff_a.back() < diff_b.back()){
			return false;
		}
	}
	
	// fprintf(stderr,"diff_a:{");for(auto it:diff_a)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	// fprintf(stderr,"diff_b:{");for(auto it:diff_b)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	
	vector< pair<int,int> > ans;
	
	for(auto it:start){
		ans.push_back(it);
	}
	
	int last = -1;
	int off = 0;
	
	vector<int> mars(a.size(),0);
	
	for(int i = 0;i < (int)diff_a.size();i++){
		a[i + 1] -= off;
		if(diff_a[i] == 0){
			continue;
		}
		
		if((diff_a[i] - diff_b[i]) % 2 != 0){
			if(last == -1){
				last = i;
				off++;
				ans.push_back({a[i + 1],1});
				mars[i]++;
			}
			else{
				diff_a[last]--;
				diff_a[i]--;
				last = -1;
			}
		}
		else{
			if(last != -1){
				diff_a[last]--;
				diff_a[i]--;
				last = i;
				off++;
				ans.push_back({a[i + 1],1});
				mars[i]++;
			}
		}
	}
	
	if(last != -1){
		return false;
	}
 
	for(int i = (int)a.size() - 2;i >= 0;i--){
		mars[i] += mars[i + 1];
		a[i] += mars[i];
	}
	
	///a's in place
 
	vector<int> diff;
	
	for(int i = 0;i < (int)diff_a.size();i++){
		diff.push_back(diff_a[i] - diff_b[i]);
		if(diff.back() < 0){
			return false;
		}
	}
	
	// fprintf(stderr,"last:%d\n",last);
	// fprintf(stderr,"a:{");for(auto it:a)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	// fprintf(stderr,"b:{");for(auto it:b)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	// fprintf(stderr,"diff_a:{");for(auto it:diff_a)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	// fprintf(stderr,"diff_b:{");for(auto it:diff_b)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	// fprintf(stderr,"diff:{");for(auto it:diff)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	
	int offset = 0;
	
	for(int i = 0;i < (int)diff.size();i++){
		a[i] -= offset;
		a[i + 1] -= offset;
		if(!diff[i]){
			a[i + 1] += offset;
			continue;
		}
		ans.push_back({(a[i] + a[i + 1]) / 2,diff[i] /  2});
		a[i + 1] += offset;
		offset += diff[i] / 2;
	}
	
	a.back() -= offset;
	
	///add final offset of all
	if(b.back() < a.back()){
		ans.push_back({0,a.back() - b.back()});
	}
	else if(b.back() > a.back()){
		ans.push_back({1e9,-a.back() + b.back()});
	}
	
	fprintf(g,"%d\n",ans.size());
	for(auto it:ans){
		fprintf(g,"%d %d\n",it.first,it.second);
	}
	
	// fprintf(stderr,"a:{");for(auto it:a)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	// fprintf(stderr,"b:{");for(auto it:b)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	// fprintf(stderr,"diff_a:{");for(auto it:diff_a)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	// fprintf(stderr,"diff_b:{");for(auto it:diff_b)fprintf(stderr,"%d,",it);fprintf(stderr,"}\n");
	// fprintf(stderr,"\n\n\n");
 
	
	return true;
}
 
int main(){
	
	fscanf(f,"%d",&t);
	
	while(t--){
		fscanf(f,"%d",&n);
		
		a = vector<int>(n,0);
		b = vector<int>(n,0);
		
		for(int i = 0;i < n;i++){
			fscanf(f,"%d",&a[i]);
		}
 
		for(int i = 0;i < n;i++){
			fscanf(f,"%d",&b[i]);
		}
		
		sort(a.begin(),a.end());
		sort(b.begin(),b.end());
		
		if(solve(a,b,vector<pair<int,int> >())){
			continue;
		}
		
		vector<int> new_a;
		for(auto it:a){
			new_a.push_back(min(it + 1,a.back()));
		}
		
		if(solve(new_a,b,{{a.back(),1}})){
			continue;
		}
		
		new_a = vector<int>();
		
		for(auto it:a){
			new_a.push_back(max(it - 1,a[0]));
		}
		
		if(solve(new_a,b,{{a[0],1}})){
			continue;
		}
		
		new_a = a;
		
		for(auto &it:new_a){
			it = max(new_a[0],it - 1);
		}
		
		for(auto &it:new_a){
			it = min(new_a.back(),it + 1);
		}
		
		if(solve(new_a,b,{{a[0],1},{new_a.back(),1}})){
			continue;
		}
		
		fprintf(g,"-1\n");
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}