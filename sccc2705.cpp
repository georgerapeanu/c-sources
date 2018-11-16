#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
#include <vector>

using namespace std;

FILE * f = fopen("ccc.in","r");
FILE * g = fopen("ccc.out","w");

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

struct point_t{
	double x,y,z;
	
	bool operator < (const point_t &other)const{
		if(x != other.x)return x < other.x;
		if(y != other.y)return y < other.y;
		return z < other.z;
	}
	
	point_t(){
		x = y = z =0;
	}
	
	point_t(double x,double y,double z){
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	double dist(point_t &other){
		return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z));
	}

	double ground_dist(point_t &other){
		return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
	}
};

struct building_t{
	point_t center;
	vector<point_t > cell_centers;
	
	building_t(double x,double y,double z,vector<point_t > cell_centers = vector<point_t >()){
		this->center = point_t(x,y,z);
		this->cell_centers = cell_centers;
	}
	
	bool operator < (const building_t &other)const{
		return center < other.center;
	}
	
	double dist(building_t &other){
		return center.dist(other.center);
	}
};

pair<int,building_t > bfs(int i,int j,int val,int rows,int cols,vector<vector<int>> &v,vector<vector<int>> &viz){
	queue< pair<int,int> > q;
	vector<point_t > cells;
	viz[i][j] = 1;
	int ans = 0;
	
	double sx = 0,sy = 0;
	
	q.push({i,j});
	
	while(!q.empty()){
		int x = q.front().first;
		int y = q.front().second;
		sx += x - 0.5;
		sy += y - 0.5;
		cells.push_back(point_t(x - 0.5,y - 0.5,val));
		q.pop();
		ans++;
		for(int k = 0;k < 4;k++){
			int xx = x + dx[k];
			int yy = y + dy[k];
			if(xx > 0 && xx <= rows && yy > 0 && yy <= cols && v[xx][yy] == val && !viz[xx][yy]){
				viz[xx][yy] = 1;
				q.push({xx,yy});
			}
		}
	}
	
	sx /= ans;
	sy /= ans;
	
	return {ans,building_t(sx,sy,val,cells)};
}

int main(){


	int rows;
	int cols;
	int tresh;
	int velo;
	
	fscanf(f,"%d %d %d %d\n",&rows,&cols,&tresh,&velo);
	
	point_t site_center(double(rows) / 2,double(cols) / 2,0);
	
	vector<vector<int>> v(rows + 1,vector<int>(cols + 1,0));
	vector<vector<int>> viz(rows + 1,vector<int>(cols + 1,0));
	
	for(int i = 1;i <= rows;i++){
		for(int j = 1;j <= cols;j++){
			fscanf(f,"%d",&v[i][j]);
		}
	}
	
	vector<pair<int,building_t> > surface;
		
	for(int i = 1;i <= rows;i++){
		for(int j = 1;j <= cols;j++){
			if(v[i][j] && !viz[i][j]){
				surface.push_back(bfs(i,j,v[i][j],rows,cols,v,viz));
			}
		}
	}
	
	sort(surface.begin(),surface.end());
	
	// for(auto it:surface){
		// printf("%.7f %.7f\n",it.second.first,it.second.second);
	// }
	
	int m;
	
	fscanf(f,"%d",&m);
	
	vector<pair<int,int> > ranges;
	
	for(int i = 0;i < m;i++){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		ranges.push_back({x,y});
	}
	
	vector<pair<int,int>> buildings;
	vector<int> guard(surface.size(),0);
	vector<point_t> center(surface.size(),point_t(0,0,0));
	
	
	for(int i = 0;i < (int)surface.size();i++){
		auto it = surface[i];
		long long guards = 0;
		for(auto cell:it.second.cell_centers){
			double dist = cell.ground_dist(site_center);
			// printf("%.5f\n",dist);
			for(auto it2:ranges){
				if(dist <= it2.first){
					guards += it2.second;
					break;
				}
			}
		}
		// printf("\n");
		guard[i] = guards;
		center[i] = surface[i].second.center;
		// fprintf(g,"%d %lld\n",i,guards);
		for(int j = i + 1;j < (int)buildings.size();j++)buildings.push_back({i,j});
	}
		
	sort(buildings.begin(),buildings.end(),[&](pair<int,int> a,pair<int,int> b){
		return 0.5 * center[a.first].dist(center[a.second]) + guards[a.first] < 0.5 * center[b.first]
	});
	
	
	fclose(f);
	fclose(g);
	
	return 0;
}