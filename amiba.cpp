#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("amiba.in","r");
FILE *g = fopen("amiba.out","w");

int T,N,A,B;

int play(vector<int> &other,vector<int> &boss){
	int idx = 0,ans = 0;
	for(auto it:boss){
		while(idx < (int)other.size() && other[idx] < it){
			idx++;
		}
		if(idx == (int)other.size()){
			return ans;
		}
		idx++;
		ans++;
	}
	return ans;
}

void fill_rest(vector< pair<int,int> > &ans,vector<int> &junior,vector<int> &skinny,vector<int> &boss){
	vector<bool> used(3 * N,false);
	for(int i = 0;i < N;i++){
		used[boss[i]] = true;
		if(ans[i].first != -1){
			used[ans[i].first] = true;
		}
		if(ans[i].second != -1){
			used[ans[i].second] = true;
		}
	}
	int junior_idx = 0;
	int skinny_idx = 0;
	for(int i = 0;i < (int)ans.size();i++){
		if(ans[i].first == -1){
			while(used[junior[junior_idx]] == true){
				junior_idx++;
			}
			ans[i].first = junior[junior_idx];
			used[ans[i].first] = true;
		}
		if(ans[i].second == -1){
			while(used[skinny[skinny_idx]] == true){
				skinny_idx++;
			}
			ans[i].second = skinny[skinny_idx];
			used[ans[i].second] = true;
		}
	}
}

vector<int> ord,tmp;

bool cmp(int a,int b){
	return tmp[a] < tmp[b];
}

void prep_reorder(vector<int> &boss){
	ord.resize(N);
	for(int i = 0;i < N;i++){
		ord[i] = i;
	}
	tmp = boss;
	sort(ord.begin(),ord.end(),cmp);
}

void reorder(vector< pair<int,int> > &a){
	vector< pair<int,int> > tmp(N);
	for(int i = 0;i < N;i++){
		tmp[ord[i]] = a[i];
	}
	for(int i = 0;i < N;i++){
		a[i] = tmp[i];
	}
}

int main(){

	fscanf(f,"%d",&T);

	while(T--){
		fscanf(f,"%d %d %d",&N,&A,&B);

		vector<int> boss(N);
		vector<int> skinny(N);
		vector<int> junior(N);
		vector< pair<int,int> > ans(N,{-1,-1});

		for(int i = 0;i < N;i++){
			fscanf(f,"%d",&boss[i]);
			boss[i]--;
		}

		for(int i = 0;i < N;i++){
			fscanf(f,"%d",&junior[i]);
			junior[i]--;
		}

		for(int i = 0;i < N;i++){
			fscanf(f,"%d",&skinny[i]);
			skinny[i]--;
		}

		prep_reorder(boss);

		sort(boss.begin(),boss.end());
		sort(junior.begin(),junior.end());
		sort(skinny.begin(),skinny.end());

		int junior_wins = play(junior,boss);
		int skinny_wins = play(skinny,boss);

		if(A <= 2 * B){
			for(int i = 0;i < junior_wins;i++){
				ans[i].first = junior[N - junior_wins + i];
			}
			for(int i = 0;i < skinny_wins;i++){
                ans[i].second = skinny[N - skinny_wins + i];
			}
			fill_rest(ans,junior,skinny,boss);
		}
		else{
			vector<int> combined;
			merge(junior.begin(),junior.end(),skinny.begin(),skinny.end(),back_inserter(combined));
			int total_wins = play(combined,boss);
			int locul3Boss = junior_wins + skinny_wins - total_wins;
			for(int i = 0;i < locul3Boss;i++){
				ans[i].first = junior[N - junior_wins + i];
				ans[i].second = skinny[N - skinny_wins + i];
			}
			int junior_idx = N - junior_wins + locul3Boss;
			int skinny_idx = N - skinny_wins + locul3Boss;
			for(int i = locul3Boss;i < total_wins;i++){
				if(skinny_idx == N || (junior_idx < N && junior[junior_idx] > skinny[skinny_idx])){
					ans[i].first = junior[junior_idx++];
				}
				else{
					ans[i].second = skinny[skinny_idx++];
				}
			}
			fill_rest(ans,junior,skinny,boss);
		}
		reorder(ans);

		for(int i = 0;i < N;i++){
			fprintf(g,"%d ",ans[i].first + 1);
		}

		fprintf(g,"\n");

		for(int i = 0;i < N;i++){
			fprintf(g,"%d ",ans[i].second + 1);
		}

		fprintf(g,"\n");
	}

	fclose(f);
	fclose(g);

	return 0;

}
