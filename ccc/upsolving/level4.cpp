#include <bits/stdc++.h>

using namespace std;

int CASE = 0;

struct power_provider_t {
    int id;
    int price;
    int power;
    int max_power;

    long long cost(int p = -1){
        if(p == -1){
            p = power;
        }
        return 1LL * p * price;
    }

    bool operator < (const power_provider_t &other) const { 
        if(CASE & 1){
            return id < other.id;
        }
        if(price != other.price)return price < other.price;
        return id < other.id;
    }

    void set_max_power(int power_limit, long long cost_limit){
        int st = 0, dr = power_limit + 1;

        while(dr - st > 1){
            int mid = (st + dr) / 2;

            if(this->cost(mid) <= cost_limit){
                st = mid;
            }
            else{
                dr = mid;
            }
        }

        max_power = st;
    }

    void reset(){
        power = 0;   
    }
};

struct task_t{
    int id;
    int power;
    int left;
    int right;

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

vector<task_t> input_tasks;
vector<power_provider_t> input_power;

bool ok(long long mid, vector<power_provider_t> &power_providers, vector<task_t> &tasks, int max_power, long long max_bill) {
    for(auto &power_provider:power_providers){
        power_provider.reset();
        power_provider.set_max_power(max_power,mid);
    }

    for(auto &task:tasks){
        task.reset();
    }

    sort(power_providers.begin(),power_providers.end());

    for(int i = 0;i < (int)power_providers.size();i++){
        int id = power_providers[i].id;
        assert(power_providers[i].power == 0);
        assert(power_providers[i].max_power <= max_power);
        assert(power_providers[i].price == input_power[id].price);
    }
    
    for(int i = 0;i < (int)tasks.size();i++){
        int id = tasks[i].id;
        assert(tasks[i].power == input_tasks[id - 1].power);
        assert(tasks[i].left == input_tasks[id - 1].left);
        assert(tasks[i].right == input_tasks[id - 1].right);
    }

    for(auto &power_provider:power_providers) {
    
        sort(tasks.begin(),tasks.end());

        int left_power = power_provider.max_power - power_provider.power;
    
        for(auto &task:tasks) {
            if(left_power == 0){
                break;
            }
            if(task.power > 0 && task.left <= power_provider.id && power_provider.id <= task.right) {
                int power_transfer = min(left_power, task.power);
                
                task.power -= power_transfer;
                power_provider.power += power_transfer;
                left_power -= power_transfer;

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
    long long max_bill;
    int max_power;

    cin >> max_power;
    cin >> max_bill;
    cin >> n;

    vector<power_provider_t> power_providers(n);

    for(int i = 0;i < n;i++) {
        cin >> power_providers[i].price;
        power_providers[i].id = i;
        power_providers[i].power = 0;
        power_providers[i].max_power = max_power;
    }

    cin >> m;

    vector<task_t> tasks(m);

    cout << m << endl;

    for(auto &it:tasks) {
        cin >> it.id >> it.power >> it.left >> it.right;
    }

    input_tasks = tasks;
    input_power = power_providers;

    long long st = 0,dr = max_bill;

    while(dr - st > 1){

        long long mid = (st + dr) / 2;

        //cerr << st << " " << dr << " " << ok(mid,power_providers,tasks,max_power,max_bill) << ok(dr,power_providers,tasks,max_power,max_bill) << endl;
        if(ok(mid,power_providers,tasks,max_power,max_bill) == 0){
            st = mid;
        }
        else{
            dr = mid;
        }
    }

    cerr << dr << " " << ok(dr,power_providers,tasks,max_power,max_bill) << endl;
    long long bill = 0;
    for(auto power_provider:power_providers) {
        bill += power_provider.cost();
    }
    
    assert(bill <= max_bill);
    
    for(auto task:tasks) {
        assert(task.power == 0);
    }
    for(auto task:tasks) {
        printf("%d ",task.id);
        for(auto it:task.ans) {
            printf("%d %d ",it.first,it.second);
        }
        printf("\n");
    }
    
    return 0;
}
