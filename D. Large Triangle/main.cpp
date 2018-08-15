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
vector< pair<int,int> > u_slopes;

bool cmp(pair<int,int> slope,int a, int b){
	return det(points[slope.first],points[slope.second],points[a]) < det(points[slope.first],points[slope.second],points[b]);
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

	auto f = [&](pair<int,int> a, pair<int,int> b){
        point_data_t c,d,e,f;
        c = points[a.first];
        d = points[a.second];
        e = points[b.first];
        f = points[b.second];
		return 1LL * (d.y - c.y) * (f.x - e.x) < 1LL * (f.y - e.y) * (d.x - c.x);
	};

	auto g = [&](pair<int,int> a, pair<int,int> b){
        point_data_t c,d,e,f;
        c = points[a.first];
        d = points[a.second];
        e = points[b.first];
        f = points[b.second];
		return 1LL * (d.y - c.y) * (f.x - e.x) == 1LL * (f.y - e.y) * (d.x - c.x);
	};

	sort(slopes.begin(),slopes.end(),f);
	u_slopes = slopes;
	int k = 0;
	for(int i = 1;i < (int)u_slopes.size();i++){
        if(!g(u_slopes[k],u_slopes[i])){
            u_slopes[++k] = u_slopes[i];
        }
	}

	u_slopes.resize(k + 1);

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

	int ind = 0;

	for(int i = 0;i < (int)slopes.size();i++){
		int fst = pos[slopes[i].first];
		int snd = pos[slopes[i].second];

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

		while(f(u_slopes[ind],slopes[i]) == 1){
            ind++;
		}

		if(ind == (int)u_slopes.size() - 1 || (!cmp(u_slopes[ind + 1],points_order[fst],points_order[snd]) && fst < snd) || (!cmp(u_slopes[ind + 1],points_order[snd],points_order[fst]) && fst > snd)){
			swap(points_order[fst],points_order[snd]);
			swap(pos[slopes[i].first], pos[slopes[i].second]);
		}
	}


	fputs("No\n",stdout);
	return 0;
}
