#include <cstdio>
#include <vector>

using namespace std;

FILE *f = fopen("in","r");
FILE *g = fopen("out","w");

class Bignum{
public:
	const int BASE = 1e3;
	vector<int> digits;
public:
	
	void operator = (const Bignum &other){
		this->digits = other.digits;
	}
	
	Bignum operator * (const int val)const{
		Bignum ans;
		ans.digits = this->digits;
		long long t = 0;
		for(int i = 0;i < (int)ans.digits.size() || t;i++){
			if(i >= (int)ans.digits.size()){
				ans.digits.push_back(0);
			}
			long long dig = 1LL * ans.digits[i] * val + t;
			ans.digits[i] = dig % BASE;
			t = dig / BASE;
		}
		return ans;
	}

	Bignum operator * (const Bignum &other)const{
		Bignum ans;
		ans.digits = vector<int>((this->digits.size() + other.digits.size()) - 1,0);
		
		for(int i = 0;i < (int)this->digits.size();i++){
			for(int j = 0;j < (int)other.digits.size();j++){
				ans.digits[i + j] += this->digits[i] * other.digits[j];
			}
		}
		
		int t = 0;
		
		for(int i = 0;i < (int)ans.digits.size() || t;i++){
			if(i >= (int)ans.digits.size()){
				ans.digits.push_back(0);
			}
			ans.digits[i] += t;
			t = ans.digits[i] / BASE;
			ans.digits[i] %= BASE;
		}
		
		return ans;
	}
	
	void afis(){
		fprintf(g,"%d",digits.back());
		for(int i = (int)digits.size() - 2;i >= 0;i--){
			int cb = BASE / 10;
			while(cb > 1 && cb > digits[i]){
				fprintf(g,"0");
				cb /= 10;
			}
			fprintf(g,"%d",digits[i]);
		}
	}
};

int n;
Bignum pref[10000];
Bignum suff[10000];
int v[10000];

int main(){
	
	fscanf(f,"%d",&n);
	
	for(int i = 1;i <= n;i++){
		pref[i].digits = {1};
		suff[i].digits = {1};
		fscanf(f,"%d",&v[i]);
	}
	
	for(int i = 1;i <= n;i++){
		if(i > 1){
			pref[i] = pref[i - 1];
		}
		pref[i] = pref[i] * v[i];
	}
	
	for(int i = n;i >= 1;i--){
		if(i < n){
			suff[i] = suff[i + 1];
		}
		suff[i] = suff[i] * v[i];
	}
	
	for(int i = 1;i <= n;i++){
		Bignum ans;ans.digits = {1};
		if(i > 1){
			ans = ans * pref[i - 1];
		}
		if(i < n){
			ans = ans * suff[i + 1];
		}
		ans.afis();
		fprintf(g," ");
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}