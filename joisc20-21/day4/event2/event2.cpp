#include <bits/stdc++.h>

using namespace std;

const int LGMAX = 17;
const int NMAX = 1e5;

int n,k;
map<int,int> to_norm;
int skip_list[LGMAX + 1 + 1][2 * NMAX + 5];
pair<int,int> v[NMAX + 5];
int closest_endpoint[2 * NMAX + 5];

int get_segment_count(int l,int r){
    if(l > r){
        return 0;
    }
    int ans = 0;
    for(int h = LGMAX;h >= 0;h--){
        if(skip_list[h][l] != 0 && skip_list[h][l] <= r + 1){
            ans += (1 << h);
            l = skip_list[h][l];
        }
    }
    return ans;
}

int aib[2 * NMAX + 5];

void update(int pos){
    for(;pos <= 2 * n + 3;pos += (-pos) & pos){
        aib[pos] ^= 1;
    }
}

int query(int pos){
    int ans = 0;

    for(;pos;pos -= (-pos) & pos){
        ans ^= aib[pos];
    }

    return ans;
}

set<int> pos; 

int main(){

   
    scanf("%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
        scanf("%d %d",&v[i].first,&v[i].second);
        v[i].second--;
        to_norm[v[i].first] = 1;
        to_norm[v[i].second] = 1;
    }

    int lst = 0;

    for(auto &it:to_norm){
        it.second = ++lst;
    }

    for(int i = 1;i <= lst + 1;i++){
        closest_endpoint[i] = 1e9;
    }

    for(int i = 1;i <= n;i++){
        v[i].first = to_norm[v[i].first];
        v[i].second = to_norm[v[i].second];
        closest_endpoint[v[i].first] = min(closest_endpoint[v[i].first],v[i].second);
    }

    for(int i = lst;i;i--){
        skip_list[0][i] = skip_list[0][i + 1];
        if(closest_endpoint[i] != 1e9 && (skip_list[0][i] == 0 || closest_endpoint[i] + 1 < skip_list[0][i])){
            skip_list[0][i] = closest_endpoint[i] + 1;
        }
    }

    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= lst;i++){
            skip_list[h][i] = skip_list[h - 1][skip_list[h - 1][i]];
        }
    }

    pos.insert(0);
    pos.insert(2 * n + 3);

    int ans = get_segment_count(1,2 * n + 2);
    if(ans < k){
        printf("-1\n");
        return 0;
    }

    for(int i = 1;i <= n;i++){
        set<int> :: iterator it;
        it = pos.lower_bound(v[i].first);
        if(*it <= v[i].second || query(v[i].first)){
            continue;
        }
        int r = *it - 1;
        it--;
        int l = *it + 1;
        int local_ans = ans - get_segment_count(l,r) + get_segment_count(l,v[i].first - 1) + get_segment_count(v[i].second + 1,r);
        if(k > 0 && local_ans >= k - 1){
            k--;
            ans = local_ans;
            printf("%d\n",i);
            pos.insert(v[i].first);
            pos.insert(v[i].second);
            update(v[i].first);
            update(v[i].second + 1);
        }
    }

    return 0;
}
