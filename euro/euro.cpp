#include <cstdio>
#include <cassert>
#include <iostream>
#include <set>

using namespace std;

FILE *f = fopen("euro.in","r");
FILE *g = fopen("euro.out","w");

const long long IS_QUERRY = 1LL << 60;

struct linear_function_t {
    long long a,b;
    mutable set<linear_function_t> :: iterator nxt;
    mutable bool is_last;

    linear_function_t() {
        a = b = 0;
        is_last = true;
    }

    linear_function_t(long long a,long long b) {
        this->a = a;
        this->b = b;
    }

    bool operator < (const linear_function_t &other)const {
        if(other.b != IS_QUERRY && this->b != IS_QUERRY) {
            if(a != other.a) {
                return a > other.a;
            }
            return b > other.b;
        }

        if(other.b == IS_QUERRY) {

            if(this->is_last) {
                return false;
            }

            assert((this->a - nxt->a));

            if(double(nxt->b - this->b) / (this->a - nxt->a) <= other.a) {
                return true;
            }
            return false;
        }

        return !(other < *this);
    }

    long long operator () (long long x)const {
        return a * x + b;
    }
};

class DynamicConvexHull {

private:

    set<linear_function_t> fun;
    long long offset;


    bool bad(set<linear_function_t> :: iterator it) {

        if(fun.size() == 1) {
            return false;
        }

        if(it == fun.begin()) {
            if(it->a == next(it)->a && it->b >= next(it)->b) {
                return true;
            }
            return false;
        }

        if(next(it) == fun.end()) {
            if(it->a == prev(it)->a && it->b >= prev(it)->b) {
                return true;
            }
            return false;
        }

        if(it->a == prev(it)->a) {
            return it->b >= prev(it)->b;
        }

        if(it->a == next(it)->a) {
            return it->b >= next(it)->b;
        }

        assert((prev(it)->a - next(it)->a));
        assert((prev(it)->a - it->a));

        if(double(next(it)->b - prev(it)->b) / (prev(it)->a - next(it)->a) < double(it->b - prev(it)->b) / (prev(it)->a - it->a)) {
            return true;
        }
        return false;
    }

public:

    DynamicConvexHull() {
        offset = 0;
        fun.clear();
    }

    void ins(linear_function_t a) {
        a.a -= offset;
        auto tmp = fun.insert(a);

        if(tmp.second == false) {
            return;
        }

        set<linear_function_t>::iterator it = tmp.first;

        if(bad(it)) {
            fun.erase(it);
            return;
        }

        while(it != fun.begin() && bad(prev(it))) {
            fun.erase(prev(it));
        }

        if(it != fun.begin()) {
            prev(it)->nxt = it;
            prev(it)->is_last = false;
        }

        while(next(it) != fun.end() && bad(next(it))) {
            fun.erase(next(it));
        }

        if(next(it) != fun.end()) {
            it->nxt = next(it);
            it->is_last = false;
        }
        else {
            it->is_last = true;
        }
    }

    long long query(long long x) {

        return (*fun.lower_bound({x,IS_QUERRY}))(x) + offset * x;
    }

    void add_offset(long long val) {
        offset += val;
    }

};

const int NMAX = 34567;

int n,t;
long long dp[NMAX + 5];

int main() {

    fscanf(f,"%d %d",&n,&t);

    DynamicConvexHull hull;
    hull.ins(linear_function_t(0,t));

    long long SP = 0;
    for(int i = 1; i <= n; i++) {
        int v;
        fscanf(f,"%d",&v);
        SP += v;

        dp[i] = -hull.query(i) + 1LL * SP * i;
        hull.ins(linear_function_t(SP,t - dp[i]));
    }

    fprintf(g,"%lld",dp[n]);

    fclose(f);
    fclose(g);

    return 0;
}
