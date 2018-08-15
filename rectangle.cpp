#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>

using namespace std;


const double PI = acos(-1);
int N;
pair<int,int> V[1505];

struct data{
	int Xcenter;
	int Ycenter;
	long long dist;
	double angle;
	bool operator < (const data &other)const{
		 if(Xcenter != other.Xcenter){
			 return Xcenter < other.Xcenter;
		 }
		 
		 if(Ycenter != other.Ycenter){
			return Ycenter < other.Ycenter;
		 }
		 
		 if(dist != other.dist){
			return dist < other.dist;
		 }
		 
		 return angle < other.angle;
	}
	
	void afis(){
		cerr << Xcenter << " ";
		cerr << Ycenter << " ";
		cerr << dist << " ";
		cerr << angle << "\n";
	}
};

vector< data > rectangle_generators; 

int main(){
	cin >> N;
	
	for(int i = 1;i <= N;i++){
		cin >> V[i].first >> V[i].second;
	}
	
	sort(V + 1,V + 1 + N);
	
	long long rez = 0;
	
	for(int i = 1;i <= N;i++){
		for(int j = 1;j < i;j++){
			data tmp;
			tmp.Xcenter = V[i].first + V[j].first;
			tmp.Ycenter = V[i].second + V[j].second;
			tmp.dist = 1LL * (V[i].first - V[j].first) * (V[i].first - V[j].first) + 1LL * (V[i].second - V[j].second) * (V[i].second - V[j].second);
			tmp.angle = atan2(V[i].second - tmp.Ycenter / 2.0,V[i].first - tmp.Xcenter / 2.0);
			rectangle_generators.push_back(tmp);
		}
	}
	
	sort(rectangle_generators.begin(),rectangle_generators.end());
	
	vector<double> angles;
	
	double ans = 0;
	
	for(int i = 0;i <= (int)rectangle_generators.size();i++){
		///rectangle_generators[i].afis();
		if(i && (i == (int)rectangle_generators.size() || rectangle_generators[i - 1].Xcenter != rectangle_generators[i].Xcenter || rectangle_generators[i - 1].Ycenter != rectangle_generators[i].Ycenter || rectangle_generators[i - 1].dist != rectangle_generators[i].dist)){
			int ind  = 0;
			for(int j = 0;j < (int)angles.size();j++){
				while(ind < (int)angles.size() && angles[ind] - angles[j] < PI / 2){
					ind++;
				}
				
				if(ind < (int)angles.size()){
					ans = max(ans,(double)rectangle_generators[i - 1].dist * sin(angles[ind] - angles[j]) / 2);
				}
				
				if(ind){
					ans = max(ans,(double)rectangle_generators[i - 1].dist * sin(angles[ind - 1] - angles[j]) / 2);
				}
			}
			angles.clear();
		}
		if(i < (int)rectangle_generators.size()){
			angles.push_back(rectangle_generators[i].angle);
		}
	}
	
	cout << (long long)round(ans);
	
	return 0;
}