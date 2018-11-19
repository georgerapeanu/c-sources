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

const double eps = 1e-5;

int app(double x){
	if(x - (int)x < eps){
		return (int)x - 1;
	}
	return x;
}

building_t bfs(int i,int j,int val,int rows,int cols,vector<vector<int>> &v,vector<vector<int>> &viz,int id){
	queue< pair<int,int> > q;
	vector<point_t > cells;
	viz[i][j] = id;	
	
	q.push({i,j});
	
	double sx = 0;
	double sy = 0;
	
	int ans = 0;
	
	while(!q.empty()){
		int x = q.front().first;
		int y = q.front().second;
		cells.push_back(point_t(x - 0.5,y - 0.5,val));
		sx += x - 0.5;
		sy += y - 0.5;
		ans++;
		q.pop();
		for(int k = 0;k < 4;k++){
			int xx = x + dx[k];
			int yy = y + dy[k];
			if(xx > 0 && xx <= rows && yy > 0 && yy <= cols && v[xx][yy] == val && !viz[xx][yy]){
				viz[xx][yy] = id;
				q.push({xx,yy});
			}
		}
	}

	sx /= ans;
	sy /= ans;
	
	return building_t(sx,sy,val,cells);
}

vector<point_t > cells_by_line(double r1,double c1,double r2,double c2,
							   vector<vector<int>> &v){///returns coord of cell and minimum height it traverses as point_t
		
	vector<point_t> ans;

	if(r1 == r2){
		for(int i = min(c1,c2);i <= max(c1,c2);i++){
			double ah = (v[r2][c2] - v[r1][c1]) / (c2 - c1);
			double bh = v[r1][c1] - ah * (c1 - 0.5);
			ans.push_back(point_t((int)r1,i,min(i == max(c1,c2) ? 1e18:ah * i + bh,i == min(c1,c2) ? 1e18:ah * (i - 1) + bh)));
		}
		return ans;
	}
	
	if(c1 == c2){
		for(int i = min(r1,r2);i <= max(r1,r2);i++){
			double ah = (v[r2][c2] - v[r1][c1]) / (r2 - r1);
			double bh = v[r1][c1] - ah * (r1 - 0.5);
			ans.push_back(point_t(i,(int)c1,min(i == max(r1,r2) ? 1e18:ah * i + bh,i == min(r1,r2) ? 1e18:ah * (i - 1) + bh)));
		}
		return ans;
	}
	
	for(int i = min(r1,r2);i <= max(r1,r2);i++){
		for(int j = min(c1,c2);j <= max(c1,c2);j++){
			double a = (c2 - c1) / (r2 - r1);
			double b = c1 - 0.5 - a * (r1 - 0.5);
			double ah = (v[r2][c2] - v[r1][c1]) / (r2 - r1);
			double bh = v[r1][c1] - ah * (r1 - 0.5);
			double x1 = i - 1;
			bool cond1 = (i == min(r1,r2));
			double x2 = i;
			bool cond2 = (i == max(r1,r2));
			double x3 = (j - 1 - b) / a;
			bool cond3 = (j == min(c1,c2));
			double x4 = (j - b) / a;
			bool cond4 = (j == max(c1,c2));
			
			// if(i == 11 && j == 10)printf("%lf %lf %lf %lf\n",x1,x2,x3,x4);
			
			if(x1 > x2){swap(x1,x2);swap(cond1,cond2);}
			if(x3 > x4){swap(x3,x4);swap(cond3,cond4);}
			
			if(x2 < x3 || x4 < x1){
				;
			}
			else{
				ans.push_back(point_t((int)i,(int)j,min(min(cond1 ? 1e18:ah * x1 + bh,cond2 ? 1e18:ah * x2 + bh),
														min(cond3 ? 1e18:ah * x3 + bh,cond4 ? 1e18:ah * x4 + bh))));
			}	
		}
	}

	return ans;
}

int main(){


	int rows;
	int cols;
	int s;
	
	fscanf(f,"%d %d %d\n",&rows,&cols,&s);
	
	point_t site_center(double(rows) / 2,double(cols) / 2,0);
	
	vector<vector<int>> v(rows + 1,vector<int>(cols + 1,0));
	vector<vector<int>> viz(rows + 1,vector<int>(cols + 1,0));
	vector<vector<int>> ids(rows + 1,vector<int>(cols + 1,0));
	
	for(int i = 1;i <= rows;i++){
		for(int j = 1;j <= cols;j++){
			fscanf(f,"%d",&v[i][j]);
		}
	}
	
	vector<building_t> surface;
		
	int last = 0;
		
	for(int i = 1;i <= rows;i++){
		for(int j = 1;j <= cols;j++){
			if(v[i][j] && !viz[i][j]){
				surface.push_back(bfs(i,j,v[i][j],rows,cols,v,viz,++last));
			}
			// fprintf(g,"%d ",viz[i][j]);
		}
		// fprintf(g,"\n");
	}
	
	ids = viz;
	
	vector<vector<int>> hot_map(rows + 1,vector<int>(cols + 1,0));
	for(int i = 1;i <= rows - s + 1;i++){
		for(int j = 1;j <= cols - s + 1;j++){
			int val = v[i][j];
			for(int k = i;k < i + s;k++){
				for(int l = j;l < j + s;l++){
					if(v[k][l] != val){
						goto done1;
					}
				}
			}
			
			for(int k = i;k < i + s;k++){
				for(int l = j;l < j + s;l++){
					hot_map[k][l] = v[k][l];
				}
			}
			
			done1:;
		}
	}
	
	// for(int i = 1;i <= rows;i++){
		// for(int j = 1;j <= cols;j++){
			// fprintf(g,"%d ",hot_map[i][j]);
		// }
		// fprintf(g,"\n");
	// }
	
	viz = vector<vector<int> >(rows + 1,vector<int>(cols + 1,0));
	
	vector<pair<int,int> > hot;
	
	for(int i = 1; i <= rows;i++){
		for(int j = 1;j <= cols;j++){
			if(hot_map[i][j] && !viz[i][j]){
				auto a = bfs(i,j,hot_map[i][j],rows,cols,hot_map,viz,1);
				
				double x1 = 1 << 30,x2 = 0;
				double y1 = 1 << 30,y2 = 0;
				
				for(auto it:a.cell_centers){
					x1 = min(x1,it.x);
					x2 = max(x2,it.x);
					y1 = min(y1,it.y);
					y2 = max(y2,it.y);
				}
				
				pair<int,int> center = make_pair(app((x1 + x2) / 2),app((y1 + y2) / 2));
				for(auto it:a.cell_centers){
					if(make_pair(app(it.x),app(it.y)) == center){
						hot.push_back(center);
						break;
					}
				}
			}
		}
	}
	
	sort(hot.begin(),hot.end());
	
	for(int i = 0; i < (int)hot.size();i++){
		fprintf(g,"%d %d %d ",i,hot[i].first,hot[i].second);
	}
	
	fprintf(g,"\n");
	
	for(int i = 0;i < (int)hot.size();i++){
		for(int j = i + 1;j < (int)hot.size();j++){
			vector<point_t> cells = cells_by_line(hot[i].first + 1,hot[i].second + 1,hot[j].first + 1,hot[j].second + 1,
												  v);
			bool valid = true;
			for(auto it:cells){
				if(it.z < v[(int)it.x][(int)it.y] && ids[(int)it.x][(int)it.y] != ids[hot[i].first + 1][hot[i].second + 1] && ids[(int)it.x][(int)it.y] != ids[hot[j].first + 1][hot[j].second + 1]){
					valid = false;
					break;
				}
			}
			if(valid){
				fprintf(g,"%d %d ",i,j);
			}
		}
	}
		
	fclose(f);
	fclose(g);
	
	return 0;
}