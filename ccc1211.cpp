#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

FILE * f = fopen("ccc.in","r");
FILE * g = fopen("ccc.out","w");

struct pay_t{
	int day,val,tf,driver;
	bool operator < (const pay_t &other){
		if(day != other.day){
			return day > other.day;
		}
		
		if(1LL * val * other.val <= 0){
			return val > other.val;
		}
		
		if(val > 0){
			return val > other.val;
		}
		return driver > other.driver;
	}
};

bool can_do(pay_t target,vector<pay_t> &aval){
	
	sort(aval.begin(),aval.end(),[](pay_t a,pay_t b){if(a.day != b.day)return a.day < b.day;return a.val > b.val;});
	
	// printf("%d %d %d\n",target.day,target.val,target.tf);for(auto it:aval)printf("%d %d\n",it.val,it.day);printf("\n");
	
	for(int i = 0;i < (int)aval.size() && aval[i].day < target.day + target.tf;i++){
		if(target.val == aval[i].val){
			aval[i].val = 0;
			return true;
		}
	}
	
	for(int i = 0;i < (int)aval.size() && aval[i].day < target.day + target.tf;i++){
		for(int j = i + 1;j < (int)aval.size() && aval[j].day < target.day + target.tf;j++){
			if(target.val == aval[i].val + aval[j].val){
				aval[i].val = 0;
				aval[j].val = 0;
				return true;
			}
		}
	}
	// printf("%d ",target);for(auto it:aval)printf("%d ",it);printf("\n");
	
	for(int i = 0;i < (int)aval.size() && aval[i].day < target.day + target.tf;i++){
		for(int j = i + 1;j < (int)aval.size() && aval[j].day < target.day + target.tf;j++){
			for(int k = j + 1;k < (int)aval.size() && aval[k].day < target.day + target.tf;k++){
				if(target.val == aval[i].val + aval[j].val + aval[k].val){
					aval[i].val = 0;
					aval[j].val = 0;
					aval[k].val = 0;
					return true;
				}
			}
		}
	}
	
	for(int i = 0;i < (int)aval.size() && aval[i].day < target.day + target.tf;i++){
		for(int j = i + 1;j < (int)aval.size() && aval[j].day < target.day + target.tf;j++){
			for(int k = j + 1;k < (int)aval.size() && aval[k].day < target.day + target.tf;k++){
				for(int l = k + 1;l < (int)aval.size() && aval[l].day < target.day + target.tf;l++){
					if(target.val == aval[i].val + aval[j].val + aval[k].val + aval[l].val){
						aval[i].val = 0;
						aval[j].val = 0;
						aval[k].val = 0;
						aval[l].val = 0;
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

vector< pay_t > op;

int main(){
	
	char c;
	int day;
	int tf;
	int driver;
	int val;
	
	while(fscanf(f,"%c ",&c) == 1){
		if(c == 'F'){
			fscanf(f,"%d %d %d %d ",&day,&driver,&tf,&val);tf++;///so apparently if timeframe is 1 it does not mean that he has to pay this day. somehow there was no good example provided, neither a test case in the level it was introduced. shame on you, problem maker.
			op.push_back({day,-val,tf,driver});
		}
		else{
			fscanf(f,"%d %d ",&day,&val);
			op.push_back({day,val,0,0});
		}
	}
	
	sort(op.begin(),op.end());
	
	vector<pay_t> aval;
	vector<pair<int,int> > bad;
	
	for(int i = 0;i < (int)op.size();i++){
		if(op[i].val >= 0){
			aval.push_back(op[i]);
			continue;
		}
		
		if(!can_do({op[i].day,-op[i].val,op[i].tf},aval)){
			bad.push_back({op[i].day,op[i].driver});
		}	
	}
	
	
	reverse(bad.begin(),bad.end());
	sort(bad.begin(),bad.end());
		
	for(auto it:bad){
		fprintf(g,"%d:%d ",it.first,it.second);
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}

///problem not hard but statements so bad