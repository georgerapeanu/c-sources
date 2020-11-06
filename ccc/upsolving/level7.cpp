#include <bits/stdc++.h>

using namespace std;

int CASE = 0;

struct power_provider_t {
    int id;
    int price;
    int power;
    int power_limit;
    int max_power;
    vector<int> left_tasks;
    vector<int> left_power;

    long long cost(int p = -1) const {
        if(p == -1){
            p = power;
        }
        return (1LL * price * (1LL * max_power + 1LL * p) * p + max_power - 1) / max_power;
    }

    bool operator < (const power_provider_t &other) const { 
        if(CASE & 1){
            return id < other.id;
        }
        return this->cost(power + 1) - this->cost(power) < other.cost(other.power + 1) - other.cost(other.power);
    }

    void set_max_power(int houses,int max_power, long long cost_limit){
        int st = 0, dr = houses * max_power + 1;

        while(dr - st > 1){
            int mid = (st + dr) / 2;

            if(this->cost(mid) <= cost_limit){
                st = mid;
            }
            else{
                dr = mid;
            }
        }

        this->power_limit = st;
    }

    void reset(int houses,int task_limit){
        power = 0;
        left_tasks = vector<int>(houses,task_limit);
        left_power = vector<int>(houses,max_power);
    }
};

struct task_t{
    int id;
    int power;
    int left;
    int right;
    int house;

    vector<pair<int,int> > ans;

    bool operator < (const task_t &other) const {
        if(CASE & 2){
            if(right != other.right) return right < other.right;
            return id < other.id;
        }
        if(power != other.power)return power > other.power;
        return id < other.id;
    }

    void reset(){
        for(auto it:ans){
            power += it.second;
        }
        ans.clear();
    }
};

bool ok(long long mid, vector<power_provider_t> &power_providers, vector<task_t> &tasks, int max_power, long long max_bill, int max_tasks,int houses) {
    for(auto &power_provider:power_providers) {
        power_provider.reset(houses,max_tasks);
        power_provider.set_max_power(houses,max_power,mid);

    }

    for(auto &task:tasks){
        task.reset();
    }

    sort(power_providers.begin(),power_providers.end());

    for(auto &power_provider:power_providers) {
    
        sort(tasks.begin(),tasks.end());

    
        for(auto &task:tasks) {
            int left_power = min(power_provider.power_limit - power_provider.power,power_provider.left_power[task.house]);
            int left_tasks = power_provider.left_tasks[task.house];
            if(left_power > 0 && left_tasks > 0 && task.power > 0 && task.left <= power_provider.id && power_provider.id <= task.right) {
                int power_transfer = min(left_power, task.power);
                
                task.power -= power_transfer;
                power_provider.power += power_transfer;
                power_provider.left_power[task.house] -= power_transfer;
                power_provider.left_tasks[task.house]--;

                task.ans.push_back({power_provider.id,power_transfer});

            }
        }
    }

    for(auto &task:tasks){
        if(task.power > 0){
            return false;
        }
    }

    return true;
}    

int main(int argc,char **argv) {
    assert(argc == 2);
    CASE = argv[1][0] - '0';

    int n,m;
    int h;
    long long max_bill;
    int max_power;
    int max_tasks;

    cin >> max_power;
    cin >> max_bill;
    cin >> max_tasks;
    cin >> n;

    vector<power_provider_t> power_providers(n);

    for(int i = 0;i < n;i++) {
        cin >> power_providers[i].price;
        power_providers[i].id = i;
        power_providers[i].power = 0;
        power_providers[i].power_limit = max_power;
        power_providers[i].max_power = max_power;
    }

    cin >> h;
    vector<task_t> tasks;

    for(int k = 0;k < h;k++){
        cin >> m;

        for(int i = 1;i <= m;i++) {
            task_t it;
            cin >> it.id >> it.power >> it.left >> it.right;
            it.house = k;
            tasks.push_back(it);
        }
    }

    long long st = 0,dr = max_bill;

    while(dr - st > 1){

        long long mid = (st + dr) / 2;

        //cerr << st << " " << dr << " " << ok(mid,power_providers,tasks,max_power,max_bill) << ok(dr,power_providers,tasks,max_power,max_bill) << endl;
        if(ok(mid,power_providers,tasks,max_power,max_bill,max_tasks,h) == 0){
            st = mid;
        }
        else{
            dr = mid;
        }
    }

    cerr << dr << " " << ok(dr,power_providers,tasks,max_power,max_bill,max_tasks,h) << endl;
    long long bill = 0;
    for(auto power_provider:power_providers) {
        bill += power_provider.cost();
    }
    
    assert(bill <= max_bill);
    
    for(auto task:tasks) {
        assert(task.power == 0);
    }
    vector< vector<task_t> > ans(h,vector<task_t>());
    for(auto task:tasks) {
        ans[task.house].push_back(task);
    }

    printf("%d\n",h);
    for(int i = 0;i < h;i++){
        printf("%d\n",i + 1);
        printf("%d\n",(int)ans[i].size());
        for(auto &it2:ans[i]){
            printf("%d ",it2.id);
            for(auto &it3:it2.ans){
                printf("%d %d ",it3.first,it3.second);
            }
            printf("\n");
        }
    }
    
    return 0;
}
