#include <bits/stdc++.h>

using namespace std;

int t;
int h;
int v;
int l_h[1005];
int l_v[1005];
bitset<1000005> dph[1005];
bitset<1000005> dpv[1005];

bool cmp(pair<int,int> a,pair<int,int> b){
    return atan2(a.second,a.first) < atan2(b.second,b.first);
}

int main(){

    scanf("%d",&t);

    while(t--){
        
        scanf("%d",&h);        

        int s_h = 0;
        int s_v = 0;

        for(int i = 1;i <= h;i++){
            scanf("%d",&l_h[i]);
            s_h += l_h[i];
        }

        scanf("%d",&v);
        
        for(int i = 1;i <= v;i++){
            scanf("%d",&l_v[i]);
            s_v += l_v[i];
        }

        if(h != v || s_h % 2 == 1 || s_v % 2 == 1){
            printf("no\n");
            continue;
        }

        dph[0][0] = 1;
        dpv[0][0] = 1;

        for(int i = 1;i <= h;i++){
            dph[i] = dph[i - 1] | (dph[i - 1] << l_h[i]);
            dpv[i] = dpv[i - 1] | (dpv[i - 1] << l_v[i]);
        }

        if(dph[h][s_h / 2] == 0 || dpv[v][s_v / 2] == 0){
            printf("No\n");
            continue;
        }
       
        vector<int> v_v[2],v_h[2];

        s_h /= 2;
        s_v /= 2;

        for(int i = v;i;i--){
            if(s_h >= l_h[i] && dph[i - 1][s_h - l_h[i]] == 1){
                v_h[0].push_back(l_h[i]);
                s_h -= l_h[i];
            }
            else{
                v_h[1].push_back(l_h[i]);
            }
            if(s_v >= l_v[i] && dpv[i - 1][s_v - l_v[i]] == 1){
                v_v[0].push_back(l_v[i]);
                s_v -= l_v[i];
            }
            else{
                v_v[1].push_back(l_v[i]);
            }
        }

        sort(v_v[0].begin(),v_v[0].end());
        sort(v_v[1].begin(),v_v[1].end());
        
        sort(v_h[0].begin(),v_h[0].end());
        sort(v_h[1].begin(),v_h[1].end());
        reverse(v_h[0].begin(),v_h[0].end());
        reverse(v_h[1].begin(),v_h[1].end());

        for(auto &it:v_h[1]){
            it *= -1;
        }
        
        for(auto &it:v_v[1]){
            it *= -1;
        }

        vector<pair<int,int> > vectors;

        for(int i = 0;i < h;i++){
            vectors.push_back({0,0});
        }

        int lst = 0;

        assert(h == v_h[0].size() + v_h[1].size());
        assert(h == v_v[0].size() + v_v[1].size());

        for(auto it:v_h[0]){
            vectors[lst++].first = it;
        }
        for(auto it:v_h[1]){
            vectors[lst++].first = it;
        }

        lst = 0;
        for(auto it:v_v[0]){
            vectors[lst++].second = it;
        }
        for(auto it:v_v[1]){
            vectors[lst++].second = it;
        }

        sort(vectors.begin(),vectors.end(),cmp);

        printf("Yes\n");
        int x = 0;
        int y = 0;

        for(auto it:vectors){
            x += it.first;
            printf("%d %d\n",x,y);
            y += it.second;
            printf("%d %d\n",x,y);
        }
    }

    return 0;
}
