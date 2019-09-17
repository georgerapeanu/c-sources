#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int MMAX = 1e9;

int m,n;
int a[NMAX + 5];
int b[NMAX + 5];

pair<int,int> v[4 * NMAX + 5];
int pref_sum[4 * NMAX + 5];
int len;
int wh[NMAX + 5];

void add_edge(int a,int b){
    if(a > 0){
        swap(a,b);
    }
    wh[-a] = b;
}

struct data_t{
    int sum,pos;
    bool query;

    data_t(int sum,int pos,bool query){
        this->sum = sum;
        this->pos = pos;
        this->query = query;
    }

    bool operator < (const data_t &other)const{
        if(sum != other.sum){
            return sum < other.sum;
        }
        if(query != other.query){
            return query < other.query;
        }
        return pos < other.pos;
    }
};

long long aib[4 * NMAX + 5];

void update(int pos,long long val){
    for(;pos <= 4 * NMAX;pos += (-pos) & pos){
        aib[pos] += val;
    }
}

long long query(int pos){
    long long ans = 0;
    for(;pos;pos -= (-pos) & pos){
        ans += aib[pos];
    }
    return ans;
}

int main() {

    scanf("%d %d",&m,&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        v[++len].first = a[i];
        v[len].second = -i;
    }
    for(int i = 1;i <= n;i++){
        scanf("%d",&b[i]);
        v[++len].first = b[i];
        v[len].second = i;
    }

    for(int i = 1;i <= len;i++){
        v[i + len] = {v[i].first + m,v[i].second};
    }

    len += len;

    sort(v + 1,v + 1 + len);

    for(int i = 1;i <= len;i++){
        v[i].first *= (v[i].second < 0 ? -1:1);
        pref_sum[i] = -(v[i].second < 0 ? -1:1);
    }

    for(int i = 1;i <= len;i++){
        pref_sum[i] += pref_sum[i - 1];
    }

    for(int i = 1;i <= len;i++){
        update(i,v[i].first);
    }

    vector<data_t> queries;

    for(int i = 1;i <= len;i++){
        ///at the moment of the query,i want all the positions with bigger pref_sum to be the same,all with smaller to be changed,and all b's with equal to be changed
        if(v[i].second < 0){
            queries.push_back(data_t(pref_sum[i - 1] + 1,i,false));
        }
        else{
            queries.push_back(data_t(pref_sum[i - 1],i,false));
        }
    }

    for(int i = 1;i <= len / 2;i++){
        queries.push_back(data_t(pref_sum[i - 1],i,true));
    }

    sort(queries.begin(),queries.end());

    long long ans = 1LL << 60;
    int st_shift = 0;

    for(auto it:queries){
        if(it.query == false){
            update(it.pos,-2LL * v[it.pos].first);///to flip the signs
        }
        else{
            long long tmp = query(it.pos + len / 2 - 1) - query(it.pos - 1);
            if(ans > tmp){
                ans = tmp;
                st_shift = it.pos;
            }
        }
    }

    vector<int> to_pair;
    int cnt = 0;
    for(int i = st_shift;i < st_shift + len / 2;i++){
        if(v[i].second < 0){
            if(cnt <= 0){
                to_pair.push_back(v[i].second);
            }
            else{
                add_edge(to_pair.back(),v[i].second);
                to_pair.pop_back();
            }
            cnt--;
        }
        else{
            if(cnt >= 0){
                to_pair.push_back(v[i].second);
            }
            else{
                add_edge(to_pair.back(),v[i].second);
                to_pair.pop_back();
            }
            cnt++;
        }
    }

    printf("%lld\n",ans);
    for(int i = 1;i <= n;i++){
        printf("%d ",wh[i]);
    }

    return 0;
}
