#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("in","r");
FILE *g = fopen("out","w");

vector<int> segm[10] = {
{1,1,1,1,1,1,0},
{0,1,1,0,0,0,0},
{1,1,0,1,1,0,1},
{1,1,1,1,0,0,1},
{0,1,1,0,0,1,1},
{1,0,1,1,0,1,1},
{1,0,1,1,1,1,1},
{1,1,1,0,0,0,0},
{1,1,1,1,1,1,1},
{1,1,1,1,0,1,1},
};

struct num{
	int sgn;
	vector<vector<int> >digs;
	
	bool is_int(){
		for(auto it:digs){
			bool ok = false;
			for(int i = 0;i < 10;i++){
				bool tmp = true;
				for(int j = 0;j < 7;j++){
					tmp &= (segm[i][j] == it[j]);
				}
				ok |= tmp;
			}
			if(!ok){
				return false;
			}
		}
		return true;
	}
	
	int to_int(){
		int ans = 0;
		
		for(auto it:digs){
			int ok = 0;
			for(int i = 0;i < 10;i++){
				bool tmp = true;
				for(int j = 0;j < 7;j++){
					tmp &= (segm[i][j] == it[j]);
				}
				if(tmp){
					ok = i;
				}
			}
			ans = ans * 10 + ok;
		}
		return ans * (sgn >= 0 ? 1:-1);
	}
};

bool eval(vector<num> a,vector<num> b){
	int tmp = 0;
	
	for(auto it:a){
		if(it.is_int()){
			tmp += it.to_int();
		}
		else{
			return false;
		}
	}
	
	for(auto it:b){
		if(it.is_int()){
			tmp -= it.to_int();
		}
		else{
			return false;
		}
	}
	
	return tmp == 0;
}

vector<num> parse(string a){
	a += '+';///flush char
	vector<num> ans;
	int sgn = 0;
	vector<vector<int> > val;
	
	for(int i = 0;i < (int)a.size();i++){
		if(a[i] == '+'){
			if(i != 0){
				ans.push_back({sgn,val});
			}
			sgn = 1;
			val.clear();
		}
		else if(a[i] == '-'){
			if(i != 0){
				ans.push_back({sgn,val});
			}
			sgn = -1;
			val.clear();
		}
		else{
			val.push_back(segm[a[i] - '0']);
		}
	}
	return ans;
}

void print(vector<num> a,vector<num> b){
	for(auto it:a){
		if(it.sgn){
			fprintf(g,"%c",(it.sgn == 1 ? '+':'-'));
		}
		fprintf(g,"%d",abs(it.to_int()));
	}
	fprintf(g,"=");
	for(auto it:b){
		if(it.sgn){
			fprintf(g,"%c",(it.sgn == 1 ? '+':'-'));
		}
		fprintf(g,"%d",abs(it.to_int()));
	}
	fprintf(g,"\n");
}

int main(){
	freopen("in","r",stdin);
	freopen("out","w",stdout);
	string ec;
	cin >> ec;
	
	string a[2];
	
	bool sw = 0;
	
	for(auto it:ec){
		if(it == '='){
			sw = 1;
			continue;
		}
		
		a[sw] += it;
	}
	
	vector<num> b = parse(a[0]);
	vector<num> c = parse(a[1]);
	
	for(auto &it:b){
		for(auto &it2:b){
			///num-num
			for(auto &dig:it.digs){
				for(auto &dig2:it2.digs){
					for(int i = 0;i < 7;i++){
						for(int j = 0;j < 7;j++){
							swap(dig[i],dig2[j]);
							if(eval(b,c)){
								print(b,c);
								return 0;
							}
							swap(dig[i],dig2[j]);
						}
					}
				}
			}
			///num-sgn
			if(it2.sgn == 1){
				it2.sgn = -1;
				
				for(auto &dig:it.digs){
					for(int i = 0;i < 7;i++){
						dig[i]++;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]--;
					}
				}
				
				it2.sgn = 1;
			}
			else if(it2.sgn == 0){
				it2.sgn = -1;
				
				for(auto &dig:it.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it2.sgn = 0;
			}
			else{
				it2.sgn = 1;
				
				for(auto &dig:it.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it2.sgn = -1;
			}
			///sgn-num
			if(it.sgn == 1){
				it.sgn = -1;
				
				for(auto &dig:it2.digs){
					for(int i = 0;i < 7;i++){
						dig[i]++;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]--;
					}
				}
				
				it.sgn = 1;
			}
			else if(it.sgn == 0){
				it.sgn = -1;
				
				for(auto &dig:it2.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it.sgn = 0;
			}
			else{
				it.sgn = 1;
				
				for(auto &dig:it2.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it.sgn = -1;
			}
			///sgn-sgn
			if(it.sgn == 0){
				if(it2.sgn == 1){
					it2.sgn *= -1;
					it.sgn = -1;
					if(eval(b,c)){
						print(b,c);
						return 0;
					}
					it2.sgn *= -1;
					it.sgn = 0;
				}
			}
			else if(it2.sgn == 0){
				if(it.sgn == 1){
					it.sgn *= -1;
					it2.sgn = -1;
					if(eval(b,c)){
						print(b,c);
						return 0;
					}
					it.sgn *= -1;
					it2.sgn = 0;
				}
			}
			else if(it.sgn && it2.sgn){
				swap(it.sgn,it2.sgn);
				if(eval(b,c)){
					print(b,c);
					return 0;
				}
				swap(it.sgn,it2.sgn);
			}
		}
		for(auto &it2:c){
			///num-num
			for(auto &dig:it.digs){
				for(auto &dig2:it2.digs){
					for(int i = 0;i < 7;i++){
						for(int j = 0;j < 7;j++){
							swap(dig[i],dig2[j]);
							if(eval(b,c)){
								print(b,c);
								return 0;
							}
							swap(dig[i],dig2[j]);
						}
					}
				}
			}
			///num-sgn
			if(it2.sgn == 1){
				it2.sgn = -1;
				
				for(auto &dig:it.digs){
					for(int i = 0;i < 7;i++){
						dig[i]++;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]--;
					}
				}
				
				it2.sgn = 1;
			}
			else if(it2.sgn == 0){
				it2.sgn = -1;
				
				for(auto &dig:it.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it2.sgn = 0;
			}
			else{
				it2.sgn = 1;
				
				for(auto &dig:it.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it2.sgn = -1;
			}
			///sgn-num
			if(it.sgn == 1){
				it.sgn = -1;
				
				for(auto &dig:it2.digs){
					for(int i = 0;i < 7;i++){
						dig[i]++;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]--;
					}
				}
				
				it.sgn = 1;
			}
			else if(it.sgn == 0){
				it.sgn = -1;
				
				for(auto &dig:it2.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it.sgn = 0;
			}
			else{
				it.sgn = 1;
				
				for(auto &dig:it2.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it.sgn = -1;
			}
			///sgn-sgn
			if(it.sgn == 0){
				if(it2.sgn == 1){
					it2.sgn *= -1;
					it.sgn = -1;
					if(eval(b,c)){
						print(b,c);
						return 0;
					}
					it2.sgn *= -1;
					it.sgn = 0;
				}
			}
			else if(it2.sgn == 0){
				if(it.sgn == 1){
					it.sgn *= -1;
					it2.sgn = -1;
					if(eval(b,c)){
						print(b,c);
						return 0;
					}
					it.sgn *= -1;
					it2.sgn = 0;
				}
			}
			else if(it.sgn && it2.sgn){
				swap(it.sgn,it2.sgn);
				if(eval(b,c)){
					print(b,c);
					return 0;
				}
				swap(it.sgn,it2.sgn);
			}
		}
	}
	
	for(auto &it:c){
		for(auto &it2:c){
			///num-num
			for(auto &dig:it.digs){
				for(auto &dig2:it2.digs){
					for(int i = 0;i < 7;i++){
						for(int j = 0;j < 7;j++){
							swap(dig[i],dig2[j]);
							if(eval(b,c)){
								print(b,c);
								return 0;
							}
							swap(dig[i],dig2[j]);
						}
					}
				}
			}
			///num-sgn
			if(it2.sgn == 1){
				it2.sgn = -1;
				
				for(auto &dig:it.digs){
					for(int i = 0;i < 7;i++){
						dig[i]++;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]--;
					}
				}
				
				it2.sgn = 1;
			}
			else if(it2.sgn == 0){
				it2.sgn = -1;
				
				for(auto &dig:it.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it2.sgn = 0;
			}
			else{
				it2.sgn = 1;
				
				for(auto &dig:it.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it2.sgn = -1;
			}
			///sgn-num
			if(it.sgn == 1){
				it.sgn = -1;
				
				for(auto &dig:it2.digs){
					for(int i = 0;i < 7;i++){
						dig[i]++;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]--;
					}
				}
				
				it.sgn = 1;
			}
			else if(it.sgn == 0){
				it.sgn = -1;
				
				for(auto &dig:it2.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it.sgn = 0;
			}
			else{
				it.sgn = 1;
				
				for(auto &dig:it2.digs){
					for(int i = 0;i < 7;i++){
						dig[i]--;
						if(eval(b,c)){
							print(b,c);
							return 0;
						}
						dig[i]++;
					}
				}
				
				it.sgn = -1;
			}
			///sgn-sgn
			if(it.sgn == 0){
				if(it2.sgn == 1){
					it2.sgn *= -1;
					it.sgn = -1;
					if(eval(b,c)){
						print(b,c);
						return 0;
					}
					it2.sgn *= -1;
					it.sgn = 0;
				}
			}
			else if(it2.sgn == 0){
				if(it.sgn == 1){
					it.sgn *= -1;
					it2.sgn = -1;
					if(eval(b,c)){
						print(b,c);
						return 0;
					}
					it.sgn *= -1;
					it2.sgn = 0;
				}
			}
			else if(it.sgn && it2.sgn){
				swap(it.sgn,it2.sgn);
				if(eval(b,c)){
					print(b,c);
					return 0;
				}
				swap(it.sgn,it2.sgn);
			}
		}
	}
	
	
	return 0;
}