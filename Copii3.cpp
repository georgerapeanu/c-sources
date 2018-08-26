#include <cstdio>
#include <cctype>
#include <cassert>
#include <vector>

using namespace std;

class InParser {
private:
  FILE *fin;
  char *buff;
  int sp;
 
  char read_ch() {
    ++sp;
    if (sp == (1<<18)) {
      sp = 0;
      fread(buff, 1, (1<<18), fin);
    }
    return buff[sp];
  }
 
public:
  InParser(const char* nume) {
    fin = fopen(nume, "r");
    buff = new char[(1<<18)]();
    sp = ((1<<18)-1);
  }
  InParser& operator >> (char &n) {
    char c;
    while (!isdigit(c = read_ch()) && c != '-');
    n = c;
    return *this;
  }
  InParser& operator >> (int &n) {
    char c;
    while (!isdigit(c = read_ch()) && c != '-');
    int sgn = 1;
    if (c == '-') {
      n = 0;
      sgn = -1;
    } else {
      n = c - '0';
    }
    while (isdigit(c = read_ch())) {
      n = 10 * n + c - '0';
    }
    n *= sgn;
    return *this;
  }
 
  InParser& operator >> (long long &n) {
    char c;
    n = 0;
    while (!isdigit(c = read_ch()) && c != '-');
    long long sgn = 1;
    if (c == '-') {
      n = 0;
      sgn = -1;
    } else {
      n = c - '0';
    }
    while (isdigit(c = read_ch())) {
      n = 10 * n + c - '0';
    }
    n *= sgn;
    return *this;
  }
};
 
class OutParser {
private:
    FILE *fout;
    char *buff;
    int sp;
 
    void write_ch(char ch) {
        if (sp == (1<<18)) {
            fwrite(buff, 1, (1<<18), fout);
            sp = 0;
            buff[sp++] = ch;
        } else {
            buff[sp++] = ch;
        }
    }
 
 
public:
  OutParser(const char* name) {
    fout = fopen(name, "w");
    buff = new char[(1<<18)]();
    sp = 0;
  }
  ~OutParser() {
    fwrite(buff, 1, sp, fout);
    fclose(fout);
  }
 
  OutParser& operator << (int vu32) {
    if (vu32 < 0) {
      write_ch('-');
      vu32 = -vu32;
    }
    if (vu32 <= 9) {
      write_ch(vu32 + '0');
    } else {
      (*this) << (vu32 / 10);
      write_ch(vu32 % 10 + '0');
    }
    return *this;
  }
 
  OutParser& operator << (long long vu64) {
    if (vu64 <= 9) {
      write_ch(vu64 + '0');
    } else {
      (*this) << (vu64 / 10);
      write_ch(vu64 % 10 + '0');
    }
    return *this;
  }
 
  OutParser& operator << (char ch) {
    write_ch(ch);
    return *this;
  }
  OutParser& operator << (const char *ch) {
    while (*ch) {
      write_ch(*ch);
      ++ch;
    }
    return *this;
  }
};

const int NMAX = 32e4;

int n,q;
char s[NMAX + 5];

long long prefix_sum[NMAX + 5];
int cnt_prefix_sum[NMAX + 5];

vector<int> pos0;
vector<int> pos1;

int last_0_in_prefix[NMAX + 5];
int first_0_in_suffix[NMAX + 5];

int taken_pos(int st,int dr){
	return cnt_prefix_sum[dr] - cnt_prefix_sum[st - 1];
}

int free_pos(int st,int dr){
	return (dr - st + 1) - (cnt_prefix_sum[dr] - cnt_prefix_sum[st - 1]);
}

long long sum_of_1_positions(int st,int dr){
	return prefix_sum[dr] - prefix_sum[st - 1];
}

long long sum_of_0_positions(int st,int dr){
	return 1LL * (dr - st + 1) * (st + dr) / 2 - (prefix_sum[dr] - prefix_sum[st - 1]);
}

long long check(int l,int r,int pos){///[l,pos][pos + 1,r]
	if(last_0_in_prefix[l - 1] - taken_pos(l,pos) + 1 < 0  || first_0_in_suffix[r + 1] + taken_pos(pos + 1,r) - 1 >= (int)pos0.size()){
		return 1LL << 62;
	}

	long long a = sum_of_1_positions(l,pos);
	long long b = last_0_in_prefix[l - 1] == -1 ? 0 : sum_of_0_positions(pos0[last_0_in_prefix[l - 1] - taken_pos(l,pos) + 1],pos0[last_0_in_prefix[l - 1]]);
	long long c = first_0_in_suffix[r + 1] == (int)pos0.size() ? 0 : sum_of_0_positions(pos0[first_0_in_suffix[r + 1]],pos0[first_0_in_suffix[r + 1] + taken_pos(pos + 1,r) - 1]);
	long long d = sum_of_1_positions(pos + 1,r);

	return a - b + c - d;
}

int first_good_pos(int l,int r){
    int st = -1,dr = pos1.size() - 1;

	while(dr - st > 1){
		int mid = (st + dr) / 2;
		if(pos1[mid] >= l && !(first_0_in_suffix[r + 1] + taken_pos(pos1[mid] + 1,r) - 1 >= (int)pos0.size())){
			dr = mid;
		}
		else{
			st = mid;
		}
	}

    return dr;
}

int last_good_pos(int l,int r){
    int st = 0,dr = (int)pos1.size();
    while(dr - st > 1){
        int mid = (st + dr) / 2;
        if(pos1[mid] <= r && !(last_0_in_prefix[l - 1] - taken_pos(l,pos1[mid]) + 1 < 0)){
            st = mid;
        }
        else{
            dr = mid;
        }
    }
    return st;
}


int main(){

	InParser f("copii3.in");
	OutParser g("copii3.out");
	
	f >> n >> q;
	for(int i = 1;i <= n;i++){
		f >> s[i];
	}

	last_0_in_prefix[0] = -1;

	for(int i = 1;i <= n;i++){
		prefix_sum[i] = (s[i] == '1' ? i : 0) + prefix_sum[i - 1];
		cnt_prefix_sum[i] = (s[i] == '1') + cnt_prefix_sum[i - 1];
		if(s[i] == '0'){
			pos0.push_back(i);
		}
		else{
			pos1.push_back(i);
		}
		last_0_in_prefix[i] = (int)pos0.size() - 1;
	}

	int ind = (int)pos0.size();

	for(int i = n;i;i--){
		if(ind && pos0[ind - 1] == i){
			ind--;
		}
		first_0_in_suffix[i] = ind;
	}

	first_0_in_suffix[n + 1] = pos0.size();


	while(q--){
		int l,r;
		f >> l >> r;
		if(pos1.empty()){
			g << "0\n";
			continue;
		}
		if(free_pos(1,l - 1) + free_pos(r + 1,n) < taken_pos(l,r)){
			g << "-1\n";
			continue;
		}

			int st,dr;
		 st = first_good_pos(l,r),dr = last_good_pos(l,r);
		long long ans = check(l,r,l - 1);
		while(dr - st >= 3){
			int mid1 = st + (dr - st) / 3;
			int mid2 = dr - (dr - st) / 3;
			long long cost1 = check(l,r,pos1[mid1]);
			long long cost2 = check(l,r,pos1[mid2]);
			if(cost1 > cost2){
				st = mid1;
			}
			else{
				dr = mid2;
			}
		}

		for(int i = st;i <= dr;i++){
			ans = min(ans,check(l,r,pos1[i]));
		}

		g << ans << "\n";
	}

	return 0;
}
