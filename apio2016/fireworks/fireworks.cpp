#include <bits/stdc++.h>

using namespace std;

struct vodoo_list_t{
    map<long long,int> slopes;
    long long a,b;

    vodoo_list_t(){
        slopes = map<long long,int>();
        a = 0;
        b = 0;
    }

    vodoo_list_t(int length){
        slopes = map<long long,int>();
        a = 1;
        b = -length;
        slopes[0] = -1;
        slopes[length] = 2;
    }

    void merge(vodoo_list_t &other){
        for(auto it:other.slopes){
            slopes[it.first] += it.second;
        }
        this->a += other.a;
        this->b += other.b;
    }

    void add_length(int length){
        while(a > 1){
            a--;
            b += slopes.rbegin()->first;
            slopes.rbegin()->second--;
            while(slopes.rbegin()->second == 0){
                slopes.erase(slopes.rbegin()->first);
            }
        }

        map<long long,int> :: iterator it = slopes.end();
        vector<long long> points;

        for(int k = 2;k > 0;k--){
            slopes.rbegin()->second--;
            points.push_back(slopes.rbegin()->first + length);
            while(slopes.rbegin()->second == 0){
                slopes.erase(slopes.rbegin()->first);
            }
        }

        for(auto it:points){
            slopes[it]++;
        }

        b -= 1LL * a * length;
    }

    long long get_min(){
        long long ans = 1e18;

        map<long long,int> :: iterator it = slopes.end();
        while(true){
            if(it == slopes.begin()){
                break;
            }
            it = prev(it);
            ans = min(ans,a * it->first + b);
            a -= it->second;
            b += it->second * it->first;
        }

        return ans;
    }

    int size(){
        return slopes.size();
    }

    void _swap(vodoo_list_t &other){
        swap(this->slopes,other.slopes);
        swap(this->a,other.a);
        swap(this->b,other.b);
    }
};

const int NMAX = 3e5;

int n,m;
vector<pair<int,int>> sons[NMAX + 5];
vodoo_list_t stuff[NMAX + 5];

void dfs(int nod,int tata,int edge){
    if(sons[nod].empty()){
        stuff[nod] = vodoo_list_t(edge);
        return ;
    }
    int bigChild = -1;
    for(auto it:sons[nod]){
        dfs(it.first,nod,it.second);
        if(bigChild == -1 || stuff[bigChild].size() < stuff[it.first].size()){
            bigChild = it.first;
        }
    }
    stuff[nod]._swap(stuff[bigChild]);
    for(auto it:sons[nod]){
        if(it.first == bigChild){
            continue;
        }
        stuff[nod].merge(stuff[it.first]);
    }
    if(tata != 0){
        stuff[nod].add_length(edge);
    }
}

int main(){
    scanf("%d %d",&n,&m);

    n += m;

    for(int i = 2;i <= n;i++){
        int p,c;
        scanf("%d %d",&p,&c);
        sons[p].push_back({i,c});
    }

    dfs(1,0,0);

    printf("%lld\n",stuff[1].get_min());

    return 0;
}
