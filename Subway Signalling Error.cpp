#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int M,N;

int V[100005];

double points[100005];

bool in(double pos,pair<double,double> wh){
	return wh.first <= pos && pos <= wh.second;
}

bool ok(double dist){

	int st = 2,dr = N;
	int points_st = 1,points_dr = N - 1;

	while(st <= dr){
        pair<double,double> LL = {max((double)0,(double)V[st] - dist),min((double)V[st] + dist,(double)2 * M)};
		pair<double,double> LR = {max((double)0,(double)2 * M - V[st] - dist),min((double)2 * M,(double)2 * M - V[st] + dist)};
		pair<double,double> RL = {max((double)0,(double)V[dr] - dist),min((double)2 * M,(double)V[dr] + dist)};
		pair<double,double> RR = {max((double)0,(double)2 * M - V[dr] - dist),min((double)2 * M,(double)2 * M - V[dr] + dist)};
        vector < pair < pair <double,int> , pair <double,double> > > V;
		V.push_back(make_pair(make_pair((double)0,1),LL));
		V.push_back(make_pair(make_pair((double)0,1),LR));
		V.push_back(make_pair(make_pair((double)0,2),RL));
		V.push_back(make_pair(make_pair((double)0,2),RR));

		for(auto &it:V){
            it.first.first = min(it.second.first,2 * M - it.second.second);
		}

		sort(V.begin(),V.end());

		if(points[points_st] <= 2 * M - points[points_dr]){
            for(auto it:V){
                if(in(points[points_st],it.second)){
                    points_st++;
                    if(it.first.second == 1){
                        st++;
                    }
                    else{
                        dr--;
                    }
                    goto done;
                }
            }
		}
		else{
			for(auto it:V){
                if(in(points[points_dr],it.second)){
                    points_dr--;
                    if(it.first.second == 1){
                        st++;
                    }
                    else{
                        dr--;
                    }
                    goto done;
                }
            }
		}
		return false;
		done:;
	}

	return points_st > points_dr;

}

int main(){

	cin >> M >> N;

	for(int i = 1;i <= N;i++){
		int  x;
		char c;
		cin >> x >> c;
		x = (c == 'L' ? x : 2 * M - x);
		V[i] = x;
	}

	sort(V + 1,V + 1 + N);


	double start = V[1],delta = ((double)2 * M) / N;

	while(start >= delta){
		start -= delta;
	}

	int len = 0;

	for(;start <= 2 * M;start += delta){
		if(start != V[1]){
			points[++len] = start;
		}
	}


	double st = 0,dr = 2.1e8;

	while(dr - st > 1e-7){
		double mid = (st + dr) / 2;
		if(ok(mid)){
			dr = mid;
		}
		else{
			st = mid;
		}
	}

	cout << fixed << setprecision(7) << st;

	return 0;
}
