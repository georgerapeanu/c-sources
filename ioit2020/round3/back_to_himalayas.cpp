#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 5e5;

int n;
int m; /// unused

int v;
const int g = 10;

int h[NMAX + 5];
int ans[NMAX + 5];

int main(){

    scanf("%d %d %d",&n,&m,&v);

    for(int i = 1;i <= n;i++){
        scanf("%d",&h[i]);
    }

    vector<pair<long long,int> > stuff;

    stuff.push_back({1e18,n + 1});

    for(int i = n;i;i--){
        

        long long value = 2LL * g * h[i] + 1LL * v * v;
        int l = -1;
        int r = stuff.size();

        while(r - l > 1){
            int mid = (l + r) / 2;
            if(stuff[mid].first <= value){
                r = mid; 
            }else{
                l = mid;
            }
        }

        ans[i] = stuff[l].second - 1;

        pair<long long,int> val;
        val.second = i;
        val.first = 2LL * h[i] * g;

        while(stuff.empty() == false && stuff.back().first <= val.first){
            stuff.pop_back();
        }
        stuff.push_back(val);
    }

    for(int i = 1;i <= n;i++){
        printf("%d ",ans[i]);
    }

    return 0;
}
