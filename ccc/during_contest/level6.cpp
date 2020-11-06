#include <bits/stdc++.h>
#include <chrono>
using namespace std;

typedef int int32;
typedef long long int64;

int32 max_power;
int32 max_tasks;
int64 max_bill;
int n, m;

struct task_t {
    int id;
    int power;
    int left, right;
    vector<pair<int, int>> ans;

    bool operator<(const task_t &other) const {
        return power > other.power;
    }
};

struct power_provider_t {
    int price;
    int power;
    int id;
    int tasks;

  	int64 nextCost() const {
      return cost(power + 1) - cost(power);
    }
  
    bool operator<(const power_provider_t &other) const {
      	return this->nextCost() < other.nextCost();
        // return 1LL * max_power * (price - other.price) > (1LL * other.price * other.power - 1LL * this->price * this->power); /// for pq
    }

    int64 cost(int p = -1) const {
        if (p == -1 ) p = power;
      	// [power_consumed * base_price * (1 + power_consumed / max_power)];
      	// power_consumed * base_price * (1 + power_consumed / max_power) = 
		// power_consumed * base_price * (max_power + power_consumed) / max_power = 
      	// [power_consumed * base_price * (max_power + power_consumed) + max_power - 1] / max_power

      	//price + price * power / max_power < other.price + other.price * other.power / max_power;
      	//price * max_power + price * power < other.price * max_power + other.price * other.power
      	//(price - other.price) * max_power + price * power <  + other.price * other.power
      	return (1LL * p * price * (max_power + p) + max_power - 1) / max_power;
      
        // long double tmp = ((long double)power / max_power);
        // long double new_price = tmp * price;
        // long long real_price = ((long long)new_price) + (new_price - (new_price - (long long)new_price) < 1e-6);
        // return real_price * power;
    }
};

int main() {
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
	cin >> max_power >> max_bill >> max_tasks;
  
	cin >> n;
	vector<power_provider_t> power(n);
  	for (int i = 0; i < n; i += 1) {
    	cin >> power[i].price;
		power[i].id = i;
	}
	  
  	cin >> m;
  	vector<task_t> tasks(m);
	for (auto& itr : tasks) { 
      	cin >> itr.id >> itr.power >> itr.left >> itr.right;
      	itr.id -= 1;
    }
  
	priority_queue<power_provider_t> pq;

    for (auto it : power) {
        pq.push(it);
    }

    int64 ans = 0;
    while (pq.empty() == false) {
        bool ok = false;
        for (auto it : tasks) {
            ok |= (it.power != 0);
        }
      
        if (ok == false) {
            break;
        }
      
      /*
      	max_power = 600
		max_bill = 8000000000
		max_tasks = 3
      */
      
        power_provider_t pp = pq.top();
        pq.pop();
      
        int ind = pp.id;
        int pw_left = max_power - pp.power;
        int task_left = max_tasks - pp.tasks;
      
        shuffle(tasks.begin(), tasks.end(), gen);
        bool taken = false;
        for (auto &it : tasks) {
            if (it.left <= ind && ind <= it.right && it.power > 0 && pw_left > 0 && task_left > 0) {
                int tmp = min(pw_left, it.power);
                it.power -= tmp;
                pw_left -= tmp;
                pp.power += tmp;
                it.ans.push_back({ind, tmp});
                task_left--;
                pp.tasks++;
                taken = true;
              	break;
            }
        }
      
        if (taken && pp.power < max_power && pp.tasks < max_tasks) {
            pq.push(pp);
        } else {
          	ans += pp.cost();
        }
    }

    while (pq.size()) {
        power_provider_t pp = pq.top();
        pq.pop();
        ans += pp.cost();
    }

  	cerr << "Max bill .. \t" << ans << '\t' << max_bill << '\n';
    assert(ans <= max_bill);

    for (auto it : tasks) {
        if (it.power > 0)
            fprintf(stderr, "deb %d\n", it.power);
        assert(it.power == 0);
    }

    vector<unordered_map<int, int>> actual_answers(m, unordered_map<int, int>());

    for (auto it : tasks) {
        for (auto it2 : it.ans) {
            actual_answers[it.id][it2.first] += it2.second;
        }
    }

    for (int i = 0; i < m; i++) {
        cout << i + 1 << ' ';
        for (auto it : actual_answers[i]) {
            printf("%d %d ", it.first, it.second);
        }
        printf("\n");
    }

    ans = 0;
    for (auto it : power) {
        ans += it.cost();
    }

    assert(ans <= max_bill);
    return 0;
}
