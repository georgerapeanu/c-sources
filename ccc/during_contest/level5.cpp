#include <bits/stdc++.h>
#include <chrono>

using namespace std;

int max_power;
int max_tasks;
long long max_bill;
int n,m;
vector<int> price;

struct task_t{
    int id;
    int p;
    int l,r;
    vector<pair<int,int> > ans;
    
    
    task_t(){
        id = 0;
        p = 0;
        l = 0;
        r = 0;
    }

    task_t(int id,int p,int l,int r){
        this->id = id;
        this->p = p;
        this->l = l;
        this->r = r;
        this->ans = vector< pair<int,int> >();
    }

    bool operator < (const task_t &other){
        return p > other.p;
    }
};

vector<task_t> task;
int main(){

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    scanf("%d",&max_power);
    scanf("%lld",&max_bill);
    scanf("%d",&max_tasks);
    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        price.push_back(0);
        scanf("%d",&price.back());
    }

    scanf("%d",&m);

    printf("%d\n",m);
    
    for(int k = 1;k <= m;k++){
        int id,p,l,r;
        scanf("%d %d %d %d",&id,&p,&l,&r);
        task.push_back(task_t(id,p,l,r));
    }

    vector<pair<int,int> > v;

    for(int i = 0;i < n;i++){
        v.push_back({price[i],i});
    }

    sort(v.begin(),v.end());

    long long ans = 0;
  
    for(auto it:v){
        int ind = it.second;
        int pw_left = max_power;
        int task_left = max_tasks;
        shuffle(task.begin(),task.end(),gen);
        for(auto &it:task){
            if(it.l <= ind && ind <= it.r && it.p > 0 && pw_left > 0 && task_left > 0){
                int tmp = min(pw_left,it.p);
                it.p -= tmp;
                pw_left -= tmp;
                it.ans.push_back({ind,tmp});
                ans += 1LL * tmp * price[ind];
                task_left--;
                
            }
        }
    }

    assert(ans <= max_bill);
    for(auto &it:task){
        assert(it.p == 0);
        printf("%d ",it.id);
        for(auto it2:it.ans){
            printf("%d %d ",it2.first,it2.second);
        }
        printf("\n");
    }


    return 0;
}
