#include <bits/stdc++.h>

using namespace std;

template<typename Type>
struct RandPoper {
    vector<int> fewnkick_tree;
    vector<int> raw_values;

    vector<Type> type_els;
    map<Type, int> id_cnt;

    long long sum = 0;
 
    struct RandPoperEl {
        RandPoper<Type>& rnd_pop;
        int pos;

        RandPoperEl& operator+=(int rhs) {
            rnd_pop.SetValue(pos, rnd_pop.raw_values[pos] + rhs);
            return *this;
        }

        RandPoperEl& operator-=(int rhs) {
            rnd_pop.SetValue(pos, rnd_pop.raw_values[pos] - rhs);
            return *this;
        }

        RandPoperEl& operator=(int rhs) {
            rnd_pop.SetValue(pos, rhs);
            return *this;
        }
    };

    RandPoper() : fewnkick_tree(1), raw_values(1) { }

    RandPoperEl operator[](const Type& el) {
        int pos;
        if (id_cnt.find(el) == id_cnt.end()) {
            type_els.push_back(el);
            id_cnt[el] = type_els.size();
            raw_values.push_back(0);
            fewnkick_tree.push_back(0);

            pos = type_els.size();

            int left = pos - (pos & (-pos));
            int right = pos - 1;
            fewnkick_tree[pos] = Sum(right) - Sum(left);
        } else {
            pos = id_cnt[el];
        }
        return RandPoperEl({*this, pos});
    };

    Type Rand() {
        long long x = rand() % (sum + 1);

        return type_els[FindSum(x) - 1];   
    }

    void SetValue(int pos, int val) {
        int old_value = raw_values[pos];
        raw_values[pos] = val;

        FenwickUpdate(pos, val - old_value);
        sum += val - old_value;
    }

    void FenwickUpdate(int pos, int val) {
        while (pos < (int)fewnkick_tree.size()) {
            fewnkick_tree[pos] += val;
            pos += pos & (-pos);
        }
    }

    int FindSum(long long val) {
        int ans = 0;
        for (int p = 25; p >= 0 ; p -= 1) {
            int c = (1 << p) + ans;
            if (c < (int)fewnkick_tree.size()) {
            } else {
                continue;
            }

            if (fewnkick_tree[c] <= val) {
                ans = c;
                val -= fewnkick_tree[c];
            }
        }

        return ans + 1;
    }

    long long Sum(int pos) {
        long long ans = 0;
        while (pos) {
            ans += fewnkick_tree[pos];
            pos -= pos & (-pos);
        }

        return ans;
    }
};


int main(){
    srand(time(NULL));
    RandPoper<int> rp;
    rp[1] = 1;
    rp[2] = 10;
    int x = rp.Rand();
    printf("%d\n",x);
    return 0;
}
