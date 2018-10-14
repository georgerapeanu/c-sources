#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

const int R = 1105;
const pair<int,int> start = {1.e9 / 2,1e9 / 2};

bool ask(pair<int,int> a){
	cout << a.first << " " << a.second << endl;
	string ans;
	cin >> ans;
	return ans == "black";
}

int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a % b);
}

void answer(int a,int b,int c,int d){
	cout << a << " " << b << " " << c  << " "  << d << endl;
	exit(0);
}

int n;

int main(){
	vector< pair<int,int> >	circ;
	vector< pair<int,int> >	tmp_circ;
	
	for(int x = -R;x <= R;x++){
		int y = sqrt(((double)R) * R - ((double)x) * x);
		if(1LL * x * x + 1LL * y * y == 1LL * R * R){
			circ.push_back({start.first + x,start.second + y});
			if(y){
				tmp_circ.push_back({start.first + x,start.second - y});
			}
		}
	}
	
	reverse(tmp_circ.begin(),tmp_circ.end());
	for(auto it:tmp_circ){
		circ.push_back(it);
	}
	
	cin >> n;
	
	if(n == 1){
		ask(start);
		answer(start.first,start.second + 1,start.first + 1,start.second + 1);
	}
		
	int num = 0;
	
	int fst_type = -1;
	
	while(num < n){
		num++;
		int type = ask(circ[num - 1]);
		if(fst_type == -1){
			fst_type = type;
		}
		else if(type != fst_type){
			pair<int,int> fst_vector = {circ[num - 2].first - start.first,circ[num - 2].second - start.second};
			pair<int,int> snd_vector = {circ[num - 1].first - start.first,circ[num - 1].second - start.second};
			
			for(int i = num + 1;i <= n;i++){
				pair<int,int> new_vector = {fst_vector.first + snd_vector.first,fst_vector.second + snd_vector.second};
				
				int g = abs(gcd(new_vector.first,new_vector.second));
				
				new_vector.first /= g;
				new_vector.second /= g;
				
				if(ask({start.first + new_vector.first,start.second + new_vector.second}) == fst_type){
					fst_vector = new_vector;
				}
				else{
					snd_vector = new_vector;
				}
			}
			pair<int,int> new_vector = {fst_vector.first + snd_vector.first,fst_vector.second + snd_vector.second};
			
			
			int g = gcd(new_vector.first,new_vector.second);
			
			new_vector.first /= g;
			new_vector.second /= g;
				
			answer(start.first,start.second,start.first + new_vector.first,start.first + new_vector.second);
		}
	}
	
	answer(start.first,start.second,circ[n].first,circ[n].second);
	
	return 0;
}
