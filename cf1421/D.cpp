#include <bits/stdc++.h>

using namespace std;

int t;
int x,y,xx,yy;
long long c[10];

long long dist(int x,int y,int xx,int yy){
    return max(0,xx - x) * c[2] + max(0,x - xx) * c[5] + max(0,yy - y) * c[6] + max(0,y - yy) * c[3];
}

int main(){

    srand(time(NULL));

    cin >> t;

    while(t--){
        int x = 0;
        int y = 0;
        cin >> xx >> yy;
        swap(x,y);
        swap(xx,yy);
        for(int i = 1;i <= 6;i++){
            cin >> c[i];
        }
    
        vector<int> ord = {1,2,3,4,5,6};

        for(int k = 0;k < 100;k++){
            reverse(ord.begin(),ord.end());
            int tmp = ord.back();
            ord.pop_back();
            reverse(ord.begin(),ord.end());
            ord.push_back(tmp);
            for(auto it:ord){
                c[it] = min(c[it],c[(it % 6) + 1] + c[((10 + it) % 6) + 1]);
            }
        }
        reverse(ord.begin(),ord.end());
        for(int k = 0;k < 100;k++){
            reverse(ord.begin(),ord.end());
            int tmp = ord.back();
            ord.pop_back();
            reverse(ord.begin(),ord.end());
            ord.push_back(tmp);
            for(auto it:ord){
                c[it] = min(c[it],c[(it % 6) + 1] + c[((10 + it) % 6) + 1]);
            }
        }

        long long ans = 2e18;

        vector<pair<int,int> > points;
        points.push_back({0,0});
        points.push_back({xx,xx});
        points.push_back({yy,yy});
        points.push_back({-xx,-xx});
        points.push_back({-yy,-yy});

        for(auto it:points){
            ans = min(ans,max(0,it.first) * c[1] + max(0,-it.first) * c[4] + dist(it.first,it.second,xx,yy));
        }

        cout << ans << "\n";

    }
    return 0;
}
