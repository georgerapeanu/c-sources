#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

void YES(int n,map<char,char> &perm,map<char,char> &used){
		string ans;
		char mex = 'a';
		for(int i = 0;i < n;i++){
			while(used[mex]){
				mex++;
			}
			ans += (perm[i + 'a'] == 0 ? mex:perm[i + 'a']);
			used[(perm[i + 'a'] == 0 ? mex:perm[i + 'a'])] = 'a';
		}
		cout << "YES\n" << ans << "\n";
}

void do_test(int n,const string &s,const string &a,const string &b){
	map<char,char> perm;
	map<char,char> used;
	int ind = -1;
	for(int i = 0;i < (int)a.size();i++){
		if(perm[s[i]] != 0 && (a[i] > perm[s[i]] || b[i] < perm[s[i]])){
			cout << "NO\n";
			return ;
		}
		else if(perm[s[i]] != 0 && a[i] < perm[s[i]] && perm[s[i]] < b[i]){
			YES(n,perm,used);
			return ;
		}
		else if(perm[s[i]]){
			if(a[i] == b[i]){
				continue;
			}
			else if(perm[s[i]] == a[i]){
				int ind = i;
				map<char,char> tmp_perm = perm;
				map<char,char> tmp_used = used;
				
				for(int i = ind + 1;i < (int)a.size();i++){
					if(tmp_perm[s[i]] && tmp_perm[s[i]] < a[i]){
						cout << "NO\n";
						return ;
					}
					else if(tmp_perm[s[i]] && tmp_perm[s[i]] > a[i]){
						YES(n,tmp_perm,tmp_used);
						return ;
					}
					else if(tmp_perm[s[i]]){
						continue;
					}
					for(int j = a[i] + 1;j < 'a' + n;j++){
						if(!tmp_used[j]){
							tmp_used[j] = s[i];
							tmp_perm[s[i]] = j;
							YES(n,tmp_perm,tmp_used);
							return ;
						}
					}
					if(tmp_used[a[i]]){
						cout << "NO\n";
						return ;
					}
					
					tmp_used[a[i]] = s[i];
					tmp_perm[s[i]] = a[i];
				}
				YES(n,tmp_perm,tmp_used);
				return ;
			}
			else{
				int ind = i;
				map<char,char> tmp_perm = perm;
				map<char,char> tmp_used = used;
				tmp_perm[s[ind]] = b[ind];
				tmp_used[b[ind]] = s[ind];
				
				for(int i = ind + 1;i < (int)a.size();i++){
					if(tmp_perm[s[i]] && tmp_perm[s[i]] > b[i]){
						cout << "NO\n";
						return ;
					}
					else if(tmp_perm[s[i]] && tmp_perm[s[i]] < b[i]){
						YES(n,tmp_perm,tmp_used);
						return ;
					}
					else if(tmp_perm[s[i]]){
						continue;
					}
					
					for(int j = b[i] - 1;j >= 'a';j--){
						if(!tmp_used[j]){
							tmp_used[j] = s[i];
							tmp_perm[s[i]] = j;
							YES(n,tmp_perm,tmp_used);
							return ;
						}
					}
					if(tmp_used[b[i]]){
						cout << "NO\n";
						return;
					}
					
					tmp_used[b[i]] = s[i];
					tmp_perm[s[i]] = b[i];
				}
				YES(n,tmp_perm,tmp_used);
				return ;
			}
		}
		
		if(a[i] == b[i]){
			if(used[a[i]] != 0 || perm[s[i]]){
				cout << "NO\n";
				return ;
			}
			used[a[i]] = s[i];
			perm[s[i]] = a[i];
		}
		else{
			ind = i;
			break;
		}
	}

	if(ind == -1){
		YES(n,perm,used);
		return ;
	}
	
	if(a[ind] > b[ind]){
		cout << "NO\n";
		return ;
	}
	
	for(char i = a[ind] + 1;i < b[ind];i++){
		if(!used[i]){
			used[i] = s[ind];
			perm[s[ind]] = i;
			YES(n,perm,used);
			return ;
		}
	}
	
	if(used[a[ind]] == 0){///a <= s
		map<char,char> tmp_perm = perm;
		map<char,char> tmp_used = used;
		tmp_perm[s[ind]] = a[ind];
		tmp_used[a[ind]] = s[ind];
		
		for(int i = ind + 1;i < (int)a.size();i++){
			if(tmp_perm[s[i]] && tmp_perm[s[i]] < a[i]){
				goto failed1;
			}
			else if(tmp_perm[s[i]] && tmp_perm[s[i]] > a[i]){
				YES(n,tmp_perm,tmp_used);
				return ;
			}
			else if(tmp_perm[s[i]]){
				continue;
			}
			for(int j = a[i] + 1;j < 'a' + n;j++){
				if(!tmp_used[j]){
					tmp_used[j] = s[i];
					tmp_perm[s[i]] = j;
					YES(n,tmp_perm,tmp_used);
					return ;
				}
			}
			if(tmp_used[a[i]]){
				goto failed1;
			}
			
			tmp_used[a[i]] = s[i];
			tmp_perm[s[i]] = a[i];
		}
		YES(n,tmp_perm,tmp_used);
		return ;
	}
	
	failed1:;
	
	if(used[b[ind]] == 0){//s <= b
		map<char,char> tmp_perm = perm;
		map<char,char> tmp_used = used;
		tmp_perm[s[ind]] = b[ind];
		tmp_used[b[ind]] = s[ind];
		
		for(int i = ind + 1;i < (int)a.size();i++){
			if(tmp_perm[s[i]] && tmp_perm[s[i]] > b[i]){
				goto failed2;
			}
			else if(tmp_perm[s[i]] && tmp_perm[s[i]] < b[i]){
				YES(n,tmp_perm,tmp_used);
				return ;
			}
			else if(tmp_perm[s[i]]){
				continue;
			}
			
			for(int j = b[i] - 1;j >= 'a';j--){
				if(!tmp_used[j]){
					tmp_used[j] = s[i];
					tmp_perm[s[i]] = j;
					YES(n,tmp_perm,tmp_used);
					return ;
				}
			}
			if(tmp_used[b[i]]){
				goto failed2;
			}
			
			tmp_used[b[i]] = s[i];
			tmp_perm[s[i]] = b[i];
		}
		YES(n,tmp_perm,tmp_used);
		return ;
	}
	
	failed2:;
	
	cout << "NO\n";
}

int main(){
	
	cin.sync_with_stdio(false);cin.tie(0);
	cout.sync_with_stdio(false);cout.tie(0);
	
	int t;
	
	cin >> t;
	
	while(t--){
		int n;
		cin >> n;
		string a,b,s;
		cin >> s >> a >> b;
		do_test(n,s,a,b);
	}
	
	return 0;
}