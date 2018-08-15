#include <cstdio>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-7;

struct point_data_t{
	int x,y;
	
	point_data_t(int x = 0,int y = 0){
		this->x = x;
		this->y = y;
	}
	
	bool operator == (const point_data_t &other)const{
		return x == other.x && y == other.y;
	}
	
	bool operator != (const point_data_t &other)const{
		return x != other.x || y != other.y;
	}
	
	long long sqr_dist(const point_data_t &other)const{
		return 1LL * (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
	}
	
	double dist(const point_data_t &other)const{
		return sqrt(this->sqr_dist(other));
	}
	
	pair<double,double> slope_intercept_form(const point_data_t &other)const{
		double m = (y - other.y) / (x - other.x);
		double b = y - x * m;
		return make_pair(m,b);
	}
};

long long det(point_data_t &a, point_data_t &b, point_data_t &c){
	return 1LL * a.x * (b.y - c.y) + 1LL * b.x * (c.y - a.y) + 1LL * c.x * (a.y - b.y);
}

int n;
long long s;

vector<point_data_t> points;
vector<int> points_order;
vector< pair<int,int> > slopes;
vector<int> pos;

bool cmp(pair<int,int> slope,int a, int b){
	return det(points[slope.first],points[slope.second],points[a]) <= det(points[slope.first],points[slope.second],points[b]);
}

int main(){
	
	fscanf(stdin,"%d %I64d",&n,&s);
	points.resize(n);
	points_order.resize(n);
	pos.resize(n);
	
	for(int i = 0; i < n; i++){
		fscanf(stdin, "%d %d", &points[i].x, &points[i].y);
		points_order[i] = i;
	}
	
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(points[i].x != points[j].x && points[i].y != points[j].y){
				slopes.push_back({i, j});
				if(points[i].x > points[j].x){
					swap(slopes.back().first,slopes.back().second);
				}
			}
		}
	}
	
	sort(slopes.begin(),slopes.end(),[&](pair<int,int> a, pair<int,int> b){
		return points[a.first].slope_intercept_form(points[a.second]) < points[b.first].slope_intercept_form(points[b.second]);
	});
	
	int k = 0;
	for(int i = 1;i < (int)slopes.size();i++){
		if(points[slopes[k].first].slope_intercept_form(points[slopes[k].second]).first != points[slopes[i].first].slope_intercept_form(points[slopes[i].second]).first){
			slopes[++k] = slopes[i];
		}
	}
	
	slopes.resize(k + 1);
	
	if(slopes.empty()){
		fputs("No\n",stdout);
		return 0;
	}
	
	sort(points_order.begin(),points_order.end(),[&](int a, int b){
		return det(points[slopes[0].first],points[slopes[0].second],points[a]) < det(points[slopes[0].first],points[slopes[0].second],points[b]);
	});
	
	for(int i = 0;i < n;i++){
		pos[points_order[i]] = i;
	}
	
	s *= 2;
	
	for(int i = 0;i < (int)slopes.size();i++){
		cout << i << "\n";
		for(int j = 0;j < n - 1;j++){
			assert(cmp(slopes[i],points_order[j],points_order[j + 1]) == 1);
		}
		int fst = pos[slopes[i].first];
		int snd = pos[slopes[i].second];
		if(fst > snd){
			swap(fst,snd);
		}
		
		int st,dr;
		
		st = 0,dr = n;
		
		while(dr - st > 1){
			int mid = (st + dr) / 2;
			if(det(points[points_order[fst]],points[points_order[snd]],points[points_order[mid]]) <= -s){
				st = mid;
			}
			else{
				dr = mid;
			}
		}
		
		if(det(points[points_order[fst]],points[points_order[snd]],points[points_order[st]]) == -s){
			fputs("Yes\n",stdout);
			fprintf(stdout,"%d %d\n",points[points_order[fst]].x,points[points_order[fst]].y);
			fprintf(stdout,"%d %d\n",points[points_order[snd]].x,points[points_order[snd]].y);
			fprintf(stdout,"%d %d\n",points[points_order[st]].x,points[points_order[st]].y);
			return 0;
		}
		
		st = 0,dr = n;
		
		while(dr - st > 1){
			int mid = (st + dr) / 2;
			if(det(points[points_order[fst]],points[points_order[snd]],points[points_order[mid]]) <= s){
				st = mid;
			}
			else{
				dr = mid;
			}
		}
		
		if(det(points[points_order[fst]],points[points_order[snd]],points[points_order[st]]) == s){
			fputs("Yes\n",stdout);
			fprintf(stdout,"%d %d\n",points[points_order[fst]].x,points[points_order[fst]].y);
			fprintf(stdout,"%d %d\n",points[points_order[snd]].x,points[points_order[snd]].y);
			fprintf(stdout,"%d %d\n",points[points_order[st]].x,points[points_order[st]].y);
			return 0;
		}
		
		if(i == (int)slopes.size() - 1 || !cmp(slopes[i + 1],points_order[fst],points_order[snd])){
			swap(points_order[fst],points_order[snd]);
			swap(pos[slopes[i].first], pos[slopes[i].second]);
		}
	}
	
	
	fputs("No\n",stdout);
	return 0;
}