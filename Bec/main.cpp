#include<map>
#include<vector>
#include<queue>
using namespace std;
map<int,pair<int,int> > fr;
struct Halving{
	int minSteps(vector<int> V){
		for(auto it:V){
			map<int,int> tmp;tmp.clear();
			queue<pair<int,int> > Q;
			Q.push({it,0});
			while(!Q.empty()){
				int x = Q.front().first;
				int cost = Q.front().second;
				Q.pop();
				if(!tmp.count(x)){
					tmp[x] = cost;
				}
				else{
					tmp[x] = min(tmp[x],cost);
				}
			}
			for(auto it:tmp){
				fr[it.first].first++;
				fr[it.first].second += it.second;
			}
		}
		int rez = 1 << 30;
		for(auto it:fr){
            if(it.second.first == V.size()){
                rez = min(rez,it.second.second);
            }
		}
		return rez;
	}
};
