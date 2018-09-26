#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("transform2.in","r");
FILE *g = fopen("transform2.out","w");

const int NMAX = 16e4;

int n;

int line[NMAX + 5];
int col[NMAX + 5];
bool viz[NMAX + 5];

pair<int,int> fst_points[NMAX + 5];
pair<int,int> snd_points[NMAX + 5];

vector<int> graph[NMAX + 5];

vector<int> fst_line[NMAX + 5];
vector<int> fst_col[NMAX + 5];

vector< vector<int> > fst;
vector< vector<int> > snd;

void switchL(int l,int r){
	fprintf(g,"L %d %d\n",l,r);

	for(auto it:fst_line[l]){
		fst_points[it].first = r;
	}
	
	for(auto it:fst_line[r]){
		fst_points[it].first = l;
	}
	
	swap(fst_line[l],fst_line[r]);
}

void switchC(int l,int r){
	fprintf(g,"C %d %d\n",l,r);
	
	for(auto it:fst_col[l]){
		fst_points[it].second = r;
	}
	
	for(auto it:fst_col[r]){
		fst_points[it].second = l;
	}
	
	swap(fst_col[l],fst_col[r]);
}

void match(vector<int> &a,vector<int> &b){
	
	bool go_fst_line = (fst_points[a[0]].first == fst_points[a[1]].first);
	bool go_snd_line = (snd_points[b[0]].first == snd_points[b[1]].first);
	bool go;
	
	if(go_fst_line != go_snd_line){
		for(int i = 1;i < (int)b.size();i++){
			swap(b[i - 1],b[i]);
		}
		go = go_fst_line;
	}
	
	else{
		go = go_fst_line;
	}
	
	if(fst_points[a[0]].first != snd_points[b[0]].first){
		switchL(fst_points[a[0]].first,snd_points[b[0]].first);
	}
	
	if(fst_points[a[0]].second != snd_points[b[0]].second){
		switchC(fst_points[a[0]].second,snd_points[b[0]].second);
	}
	
	for(int i = 1;i < (int)a.size();i++){
		if(go){
			if(fst_points[a[i]].second != snd_points[b[i]].second){
				switchC(fst_points[a[i]].second,snd_points[b[i]].second);
			}
		}
		
		else{
			if(fst_points[a[i]].first != snd_points[b[i]].first){
				switchL(fst_points[a[i]].first,snd_points[b[i]].first);
			}
		}
		go ^= 1;
	}
}

int main(){
	
	fscanf(f,"%d",&n);
	
	for(int i = 1;i <= 2 * n;i++){
		fscanf(f,"%d %d",&snd_points[i].first,&snd_points[i].second);
		
		if(line[snd_points[i].first]){
			graph[i].push_back(line[snd_points[i].first]);
			graph[line[snd_points[i].first]].push_back(i);
		}
		
		if(col[snd_points[i].second]){
			graph[i].push_back(col[snd_points[i].second]);
			graph[col[snd_points[i].second]].push_back(i);
		}
		
		line[snd_points[i].first] = i;
		col[snd_points[i].second] = i;
	}
	
	for(int i = 1;i <= 2 * n;i++){
		if(!viz[i]){
			vector<int> a;
			a.push_back(i);
			viz[i] = 1;
			for(int i = 0;i < (int)a.size();i++){
				int nod = a[i];
				for(auto it:graph[nod]){
					if(!viz[it]){
						a.push_back(it);
						viz[it] = 1;
						break;
					}
				}
			}
			snd.push_back(a);			
		}
	}

	for(int i = 1;i <= 2 * n;i++){
		graph[i].clear();
		line[i] = 0;
		col[i] = 0;
		viz[i] = 0;
	}	
	
	for(int i = 1;i <= 2 * n;i++){
		fscanf(f,"%d %d",&fst_points[i].first,&fst_points[i].second);
		
		if(line[fst_points[i].first]){
			graph[i].push_back(line[fst_points[i].first]);
			graph[line[fst_points[i].first]].push_back(i);
		}
		
		if(col[fst_points[i].second]){
			graph[i].push_back(col[fst_points[i].second]);
			graph[col[fst_points[i].second]].push_back(i);
		}
		
		line[fst_points[i].first] = i;
		col[fst_points[i].second] = i;
		
		fst_line[fst_points[i].first].push_back(i);
		fst_col[fst_points[i].second].push_back(i);
	}
	
	for(int i = 1;i <= 2 * n;i++){
		if(!viz[i]){
			vector<int> a;
			a.push_back(i);
			viz[i] = 1;
			for(int i = 0;i < (int)a.size();i++){
				int nod = a[i];
				for(auto it:graph[nod]){
					if(!viz[it]){
						a.push_back(it);
						viz[it] = 1;
						break;
					}
				}
			}
			fst.push_back(a);
		}
	}

	for(int i = 1;i <= 2 * n;i++){
		graph[i].clear();
		line[i] = 0;
		col[i] = 0;
		viz[i] = 0;
	}

	sort(fst.begin(),fst.end(),[](vector<int> &a,vector<int> &b){return a.size() < b.size();});
	sort(snd.begin(),snd.end(),[](vector<int> &a,vector<int> &b){return a.size() < b.size();});
	
	for(int i = 0;i < (int)fst.size();i++){
		match(fst[i],snd[i]);
	}
	
	fprintf(g,"0 0 0\n");
	
	return 0;
}