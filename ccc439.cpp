#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("in","r");
FILE *g = fopen("out","w");

int rows,cols;
int dx[300];
int dy[300];

string dir = "NESW";


pair<int,int> id_to_coord(int pos){
	return {(pos + cols - 1) / cols,(pos - 1) % cols + 1};

}

int man_dist(pair<int,int> a,pair<int,int> b){
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int dotest_app(){
	
	// fprintf(stderr,"PROGRESS\n");
	
	dx['N'] = -1;dy['N'] = 0;
	dx['E'] = 0;dy['E'] = 1;
	dx['S'] = 1;dy['S'] = 0;
	dx['W'] = 0;dy['W'] = -1;
	
	int n,m;
	fscanf(f,"%d %d",&rows,&cols);
	fscanf(f,"%d",&n);

	vector<vector<int>> mat;
	vector<vector<int>> viz;
	vector<int> fst(n + 1,0);
	vector<int> snd(n + 1,0);
	vector<bool> conn(n + 1,0);
	
	mat.resize(rows + 1);
	viz.resize(rows + 1);
	
	for(auto &it:mat){
		it.resize(cols + 1);
	}
	for(auto &it:viz){
		it.resize(cols + 1);
	}
	
	for(int i = 1;i <= n;i++){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		mat[id_to_coord(x).first][id_to_coord(x).second] = y;
		if(fst[y]){
			snd[y] = x;
		}
		else{
			fst[y] = x;
		}
	}
	
	fscanf(f,"%d",&m);
	
	for(int i = 1;i <= m;i++){
		int cul;
		int st;
		pair<int,int> pos;
		int len;
		fscanf(f,"%d %d %d ",&cul,&st,&len);
		pos = id_to_coord(st);
		viz[pos.first][pos.second] = cul;
		
		bool ok = true;
		vector< pair<int,int> > wh(1,pos);

		for(int j = 1;j <= len;j++){
			char c;
			fscanf(f,"%c ",&c);
			pos.first += dx[c];
			pos.second += dy[c];

			if(ok == false){
				continue;
			}
			
			if(pos.first <= 0 || pos.first > rows || pos.second <= 0 || pos.second > cols){
				// if(ok){
					// fprintf(g,"-1 %d\n",j);
				// }
				ok = false;
				continue;
			}
			
			if(viz[pos.first][pos.second] || (mat[pos.first][pos.second] != cul && mat[pos.first][pos.second] != 0)){
				// if(ok){
					// fprintf(g,"-1 %d\n",j);
				// }
				ok = false;
				continue;
			}
			
			viz[pos.first][pos.second] = cul;
			wh.push_back(pos);
		}
		
		if(ok && (mat[pos.first][pos.second] != cul || pos == id_to_coord(st))){
			// if(ok){
				// fprintf(g,"-1 %d\n",len);
			// }
			ok = false;
		}
		
		if(ok){
			conn[cul] = true;
			// fprintf(g,"1 %d\n",len);
		}
		else{
			for(auto it:wh){
				viz[it.first][it.second] = 0;
			}
		}		
	}
	
	// fprintf(g,"%d %d\n",rows,cols);
	
	for(int i = 1;i <= rows;i++){
		for(int j = 1;j <= cols;j++){
			if(mat[i][j]){
				viz[i][j] = mat[i][j];
			}
			// fprintf(g,"%d",viz[i][j]);
		}
		// fprintf(g,"\n");
	}
	
	// for(int i = 1;i <= n / 2;i++){
		// pair<int,int> start = id_to_coord(fst[i]);
		// vector<vector<int>> viz2 = vector<vector<int>>(rows + 1,vector<int>(cols + 1,0));
		// viz2[start.first][start.second] = 1;
		// queue< pair<int,int> > q;
		// q.push(start);
		// while(!q.empty()){
			// start = q.front();
			// q.pop();
			// for(auto it:dir){
				// pair<int,int> tmp = {start.first + dx[it],start.second + dy[it]};
				// if(tmp.first <= 0 || tmp.first > rows || tmp.second <= 0 || tmp.second > cols || viz2[tmp.first][tmp.second] || (viz[tmp.first][tmp.second] && tmp != id_to_coord(snd[i]))){
					// continue;
				// }
				// viz2[tmp.first][tmp.second] = 1;
				// q.push(tmp);
			// }
		// }
		// if(conn[i]){
			// fprintf(g,"1 ");
		// }
		// else if(viz2[id_to_coord(snd[i]).first][id_to_coord(snd[i]).second]){
			// fprintf(g,"2 ");
		// }
		// else{
			// fprintf(g,"3 ");
		// }
	// }
	vector<pair<int,int>> pos;
	vector<vector<int>> cul = viz;
	vector<bool> completed(n + 1,false);
	for(int i = 1;i <= n / 2;i++){
		cul[id_to_coord(fst[i]).first][id_to_coord(fst[i]).second] = i;
		cul[id_to_coord(snd[i]).first][id_to_coord(snd[i]).second] = i + n / 2;
		pos.push_back(id_to_coord(fst[i]));
		pos.push_back(id_to_coord(snd[i]));
	}
	
	
	while(pos.size()){
		
		// for(auto it:pos){
			// fprintf(g,"%d %d\n",it.first,it.second);
		// }
		// fprintf(g,"\n\n");
		// fflush(g);
		
		vector<pair<int,int>> new_pos;
		bool advance = false;
		for(auto it:pos){
			if(completed[cul[it.first][it.second]]){
				advance = true;
				continue;
			}
			pair<int,int> start = it;
			pair<int,int> to;
			int cnt = 0;
			for(auto it:dir){
				pair<int,int> tmp = {start.first + dx[it],start.second + dy[it]};
				if(tmp.first <= 0 || tmp.first > rows || tmp.second <= 0 || tmp.second > cols || (cul[tmp.first][tmp.second] != 0 &&
				   (cul[tmp.first][tmp.second] != cul[start.first][start.second] + n / 2 && (cul[tmp.first][tmp.second] != cul[start.first][start.second] - n / 2 || 
				   (cul[tmp.first][tmp.second] == cul[start.first][start.second] - n / 2 && cul[start.first][start.second] == n / 2))))){
					continue;
				}
				to = tmp;
				cnt++;
			}
			if(cnt == 1){
				advance = true;
				if(((cul[to.first][to.second] == cul[start.first][start.second] - n / 2 && cul[start.first][start.second] != n / 2) || 
				   cul[to.first][to.second] == cul[start.first][start.second] + n / 2)){
				   completed[cul[to.first][to.second]] = true;
				   completed[cul[start.first][start.second]] = true;
				}
				else{
					cul[to.first][to.second] = cul[start.first][start.second];
					new_pos.push_back(to);
				}
				
			}
			else{
				new_pos.push_back(it);
			}
		}
		pos = new_pos;
		if(!advance){
			vector<pair<int,int>> new_pos;
			bool advance = false;
			for(auto it:pos){
				if(completed[cul[it.first][it.second]]){
					advance = true;
					continue;
				}
				
				if(advance){
					new_pos.push_back(it);
					continue;
				}
				
				pair<int,int> start = it;
				pair<int,int> to;
				int cnt = 0;
				for(auto it:dir){
					pair<int,int> tmp = {start.first + dx[it],start.second + dy[it]};
					if(tmp.first <= 0 || tmp.first > rows || tmp.second <= 0 || tmp.second > cols || (cul[tmp.first][tmp.second] != 0 &&
					   (cul[tmp.first][tmp.second] != cul[start.first][start.second] + n / 2 && (cul[tmp.first][tmp.second] != cul[start.first][start.second] - n / 2 || 
					   (cul[tmp.first][tmp.second] == cul[start.first][start.second] - n / 2 && cul[start.first][start.second] == n / 2))))){
						continue;
					}
					to = tmp;
					cnt++;
				}
				if(cnt >= 1){
					advance = true;
					if(((cul[to.first][to.second] == cul[start.first][start.second] - n / 2 && cul[start.first][start.second] != n / 2) || 
					   cul[to.first][to.second] == cul[start.first][start.second] + n / 2)){
					   completed[cul[to.first][to.second]] = true;
					   completed[cul[start.first][start.second]] = true;
					}
					else{
						cul[to.first][to.second] = cul[start.first][start.second];
						new_pos.push_back(to);
					}
					
				}
				else{
					new_pos.push_back(it);
				}
			}
			pos = new_pos;
		}
	}
	
	for(int i = 1;i <= n / 2;i++){
		if(completed[i]){
			for(int j = 1;j <= rows;j++){
				for(int k = 1;k <= cols;k++){
					if(cul[j][k] == i + n / 2){
						cul[j][k] = i;
					}
				}
			}
		}
	}
	
	
	fprintf(stderr,"\n\n\n");
	for(int i = 1;i <= rows;i++){
		for(int j = 1;j <= cols;j++){
			fprintf(stderr,"%d ",cul[i][j]);
		}
		fprintf(stderr,"\n");
	}
	fprintf(stderr,"\n\n\n");
	
	vector<pair<int,string> > paths;
	vector<vector<int> > afis_viz = vector<vector<int>>(rows + 1,vector<int>(cols + 1,0));
	
	for(int i = 1;i <= n / 2;i++){
		if(completed[i]){
			string a;
			pair<int,int> start = id_to_coord(fst[i]);
			afis_viz[start.first][start.second] = true;
			// fprintf(stderr,"begin2 %d\n",fst[i]);
			while(start != id_to_coord(snd[i])){
				// fprintf(stderr,"%d %d\n",start.first,start.second);
				for(auto it:dir){
					
					if(start.first + dx[it] <= 0 || start.first + dx[it] > rows || start.second + dy[it] <= 0 || start.second + dy[it] > cols)continue;
					
					if(!afis_viz[start.first + dx[it]][start.second + dy[it]] && cul[start.first + dx[it]][start.second + dy[it]] == cul[start.first][start.second]){
						start.first += dx[it];
						start.second += dy[it];
						afis_viz[start.first][start.second] = true;
						if(a.size()){
							a = a + " " + it;
						}
						else{
							a = a + it;
						}
						break;
					}
				}
			}
			// fprintf(stderr,"finished\n");
			paths.push_back({fst[i],a});
		}
		else{
			string a;
			pair<int,int> start = id_to_coord(fst[i]);
			// fprintf(stderr,"begin %d\n",fst[i]);
			afis_viz[start.first][start.second] = true;
			while(1){
				bool ok = false;
				for(auto it:dir){
					if(start.first + dx[it] <= 0 || start.first + dx[it] > rows || start.second + dy[it] <= 0 || start.second + dy[it] > cols)continue;
					if(!afis_viz[start.first + dx[it]][start.second + dy[it]] && cul[start.first + dx[it]][start.second + dy[it]] == cul[start.first][start.second]){
						start.first += dx[it];
						start.second += dy[it];
						ok = true;
						afis_viz[start.first][start.second] = true;
						if(a.size()){
							a = a + " " + it;
						}
						else{
							a = a + it;
						}
						break;
					}
				}
				if(!ok){
					break;
				}
			}
			// fprintf(stderr,"finished\n");
			paths.push_back({fst[i],a});
			
			a = "";
			start = id_to_coord(snd[i]);
			afis_viz[start.first][start.second] = true;
			while(1){
				bool ok = false;
				for(auto it:dir){
					if(start.first + dx[it] <= 0 || start.first + dx[it] > rows || start.second + dy[it] <= 0 || start.second + dy[it] > cols)continue;
					if(!afis_viz[start.first + dx[it]][start.second + dy[it]] && cul[start.first + dx[it]][start.second + dy[it]] == cul[start.first][start.second]){
						start.first += dx[it];
						start.second += dy[it];
						ok = true;
						afis_viz[start.first][start.second] = true;
						if(a.size()){
							a = a + " " + it;
						}
						else{
							a = a + it;
						}
						break;
					}
				}
				if(!ok){
					break;
				}
			}
			paths.push_back({snd[i],a});
		}
	}
	
	vector<pair<int,string> > new_paths;
	
	for(auto it:paths){
		if(it.second.size()){
			new_paths.push_back(it);
		}
	}
	paths = new_paths;
	
	cout << paths.size() << " ";
	
	for(auto it:paths){
		int real_cul = cul[id_to_coord(it.first).first][id_to_coord(it.first).second];
		if(real_cul > n / 2){
			real_cul -= n / 2;
		}
		cout << real_cul << " " << it.first << " " << it.second.size() / 2 + 1 << " " << it.second << " ";
	}
}

int main(){
	
	freopen("in","r",stdin);
	freopen("out","w",stdout);
	
	int t;
	fscanf(f,"%d",&t);
	cout << t << " ";
	while(t--){
		dotest_app();
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}