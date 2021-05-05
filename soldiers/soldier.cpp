#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

class FenwickTree{
    int n;
    vector<int> aib;

public:

    FenwickTree(int n){
        this->n = n;
        this->aib = vector<int>(n + 1,0);
    }

    void update(int pos,int value){
        for(;pos;pos -= (-pos) & pos){
            aib[pos] += value;
        }
    }

    long long query(int pos){
        long long ans = 0;
        for(;pos <= n;pos += (-pos) & pos){
            ans += aib[pos];
        }
        return ans;
    }
};

struct slope_trick_stuff{
    map<int,int> slopes;
    int last_value;
    long long origin_y;

    slope_trick_stuff(){
        slopes = map<int,int>();
        last_value = 0;
        origin_y = 0;
    }

    void add_point(int x){
        origin_y += x + 1;
        slopes[0] -= 1;
        slopes[x + 1] += 2;
        last_value++;
        while(last_value > 0){
            int wh = slopes.rbegin()->first;
            if(last_value - slopes[wh] < 0){
                slopes[wh] = slopes[wh] - last_value;
                last_value = 0;
                break;
            }else{
                last_value -= slopes[wh];
                slopes.erase(wh);
            }
        }
    }

    long long get_min(){
        long long ans = origin_y;
        int slope = 0;
        int lst = 0;

        for(auto it:slopes){
            ans += 1LL * slope * (it.first - lst);
            slope += it.second;
            lst = it.first;
        }

        return ans;
    }
};

long long minimum_swap(vector<int> p,int k){
    FenwickTree aib(p.size());
    vector<int> positions(k + 1,0);

    long long answer = 0;
    int cnt = 0;

    for(int i = 0;i < (int)p.size();i++){
        if(p[i] <= k){
            positions[p[i]] = cnt;
            answer += aib.query(p[i]);
            aib.update(p[i],1);
        }else{
            cnt++;
        }
    }

    int _min = 0;

    for(int i = 1;i <= k;i++){
        _min = min(_min,positions[i]);
    }

    for(int i = 1;i <= k;i++){
        positions[i] -= _min;
    }

    slope_trick_stuff stuff = slope_trick_stuff();

    for(int i = 1;i <= k;i++){
        stuff.add_point(positions[i]);
    }

    answer += stuff.get_min();

    return answer;
}

int main(){

    int n,k;
    vector<int> p;

    scanf("%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
        int value;
        scanf("%d",&value);
        p.push_back(value);
    }

    printf("%lld\n",minimum_swap(p,k));

    return 0;
}
