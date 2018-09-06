#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

string s;
int q;
vector<int> pos[26];
vector<int> fst[26];
vector<int> lst[26];

int dpl[26][100005];
int dpr[26][100005];
vector<int> partial_xor[26];

int solve_slow(int l,int r){

	int xors = 0;

	for(int c = 0;c < 26;c++){
		if(pos[c].empty()){
			continue;
		}

		int fstpos = fst[c][l];
		int lstpos = lst[c][r];

		if(fstpos > lstpos){
			continue;
		}

		int xo = 0;

		if(l <= pos[c][fstpos] - 1){
			if(dpr[c][l] == -1){
				dpr[c][l] = solve_slow(l,pos[c][fstpos] - 1);
			}
			xo ^= dpr[c][l];
		}

		if(r >= pos[c][lstpos] + 1){
			if(dpl[c][r] == -1){
				dpl[c][r] = solve_slow(pos[c][lstpos] + 1,r);
			}
			xo ^= dpl[c][r];
		}

		for(int i = fstpos;i < lstpos;i++){
			xo ^= partial_xor[c][i];
		}

		xors |= 1 << xo;
	}

	for(int i = 0;;i++){
		if(!((xors >> i) & 1)){
			return i;
		}
	}
}

int solve_fast(int l,int r){

	int xors = 0;

	for(int c = 0;c < 26;c++){
		if(pos[c].empty()){
			continue;
		}

		int fstpos = fst[c][l];
		int lstpos = lst[c][r];

		if(fstpos > lstpos){
			continue;
		}

		int xo = 0;

		if(l <= pos[c][fstpos] - 1){
			if(dpr[c][l] == -1){
				dpr[c][l] = solve_fast(l,pos[c][fstpos] - 1);
			}
			xo ^= dpr[c][l];
		}

		if(r >= pos[c][lstpos] + 1){
			if(dpl[c][r] == -1){
				dpl[c][r] = solve_fast(pos[c][lstpos] + 1,r);
			}
			xo ^= dpl[c][r];
		}

		xo ^= (lstpos ? partial_xor[c][lstpos - 1] : 0) ^ (fstpos ? partial_xor[c][fstpos - 1] : 0);

		xors |= 1 << xo;
	}

	for(int i = 0;;i++){
		if(!((xors >> i) & 1)){
			return i;
		}
	}
}
int main(){

	cin >> s >> q;
	s = " " + s;

	for(int i = 1;i < s.size();i++){
		pos[s[i] - 'a'].push_back(i);
	}


	for(int c = 0;c < 26;c++){
		fst[c] = vector<int>(s.size() + 5,s.size() + 5);
		lst[c] = vector<int>(s.size() + 5);
		partial_xor[c].resize(pos[c].size() + 5);

		int idx = pos[c].size();

		for(int i = s.size() - 1;i;i--){
			while(idx && pos[c][idx - 1] >= i){
				idx--;
			}
			fst[c][i] = idx;
		}

		idx = -1;

		for(int i = 1;i < s.size();i++){
			while(idx < (int)pos[c].size() - 1 && pos[c][idx + 1] <= i){
				idx++;
			}
			lst[c][i] = idx;
		}

		for(int i = 0;i < s.size();i++){
            dpl[c][i] = dpr[c][i] = -1;
		}

		for(int i = 0;i < (int)pos[c].size() - 1;i++){
			partial_xor[c][i] = -1;
		}
	}

	vector< pair<int,int> > segments;

	for(int c = 0;c < 26;c++){
		for(int i = 0;i < (int)pos[c].size() - 1;i++){
			if(pos[c][i] + 1 <= pos[c][i + 1] - 1){
				segments.push_back(make_pair(c,i));
			}
			else{
				partial_xor[c][i] = 0;
			}
		}
	}

	sort(segments.begin(),segments.end(),[&](pair<int,int> c,pair<int,int> d){
		pair<int,int> a = make_pair(pos[c.first][c.second] + 1,pos[c.first][c.second + 1] - 1);
		pair<int,int> b = make_pair(pos[d.first][d.second] + 1,pos[d.first][d.second + 1] - 1);
		if(a.second - a.first != b.first - b.second){
			return a.second - a.first < b.second - b.first;
		}
		return a < b;
	});

	for(auto it:segments){
		pair<int,int> a = make_pair(pos[it.first][it.second] + 1,pos[it.first][it.second + 1] - 1);
		partial_xor[it.first][it.second] = solve_slow(a.first,a.second);
	}

	for(int c = 0;c < 26;c++){
		for(int i = 1;i < (int)partial_xor[c].size();i++){
			partial_xor[c][i] ^= partial_xor[c][i - 1];
		}
	}

	while(q--){
		int l,r;
		cin >> l >> r;
		cout << (solve_fast(l,r) == 0 ? "Bob\n":"Alice\n");
	}

	return 0;
}