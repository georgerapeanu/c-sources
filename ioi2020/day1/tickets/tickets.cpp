#include "tickets.h"
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


long long find_maximum(int k, vector<vector<int>> x) {
	int n = x.size();
	int m = x[0].size();
	vector<vector<int>> answer(n,vector<int>(m,-1));
    vector<int> cnt(x.size(),k);
    long long ans = 0;

    for(auto it:x){
        for(int i = 0;i < k;i++){
            ans -= it[i];
        }
    }

    priority_queue<pair<int,int>> pq;

    for(int i = 0;i < n;i++){
        pq.push({x[i][(int)x[i].size() - 1 - (k - cnt[i])] + x[i][cnt[i] - 1],i});
    }

    for(int i = 1;i <= n * k / 2;i++){
        pair<int,int> tmp = pq.top();
        pq.pop();
        cnt[tmp.second]--;
        ans += tmp.first;
        if(cnt[tmp.second] > 0){
            tmp.first = x[tmp.second][(int)x[tmp.second].size() - 1 - (k - cnt[tmp.second])] + x[tmp.second][cnt[tmp.second] - 1];
            pq.push(tmp);
        }
    }

    vector<int> free_left(k,n / 2);

    for(int i = 0;i < n;i++){
        vector<pair<int,int> > tmp;

        for(int j = 0;j < k;j++){
            tmp.push_back({free_left[j],j});
        }

        sort(tmp.begin(),tmp.end());
        reverse(tmp.begin(),tmp.end());

        for(int j = 0;j < cnt[i];j++){
            answer[i][j] = tmp[j].second;
            free_left[tmp[j].second]--;
        }
        for(int j = m - (k - cnt[i]);j < m;j++){
            answer[i][j] = tmp[cnt[i] + (j - (m - (k - cnt[i])))].second;
        }
    }


    allocate_tickets(answer);
	return ans;
}
