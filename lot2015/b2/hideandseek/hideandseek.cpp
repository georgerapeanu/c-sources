#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

FILE *f = fopen("hideandseek.in","r");
FILE *g = fopen("hideandseek.out","w");

///1-indexed
class Perm {
    vector<int> perm;
    vector<vector<int> > cycle_decomp;

    void get_decomp() {
        cycle_decomp.clear();
        vector<int> viz(perm.size(),0);

        for(int i = 1; i < (int)perm.size(); i++) {
            if(viz[i] == 0) {
                vector<int> cycle = {};
                int nod = i;
                while(viz[nod] == false) {
                    viz[nod] = true;
                    cycle.push_back(nod);
                    nod = perm[nod];
                }
                cycle_decomp.push_back(cycle);
            }
        }
    }

public:

    Perm(const vector<int> &perm,bool check = true) {
        if(check) {
            this->perm = perm;
            sort(this->perm.begin(),this->perm.end());
            for(int i = 0; i < (int)this->perm.size(); i++) {
                assert(this->perm[i] == i);
            }
        }
        this->perm = perm;
        this->cycle_decomp = vector<vector<int> >();
    }

    Perm inverse()const {
        Perm ans(this->perm,false);
        for(int i = 1; i < (int)this->perm.size(); i++) {
            ans.perm[this->perm[i]] = i;
        }
        ans.cycle_decomp = this->cycle_decomp;
        for(auto &it:ans.cycle_decomp) {
            reverse(it.begin(),it.end());
        }
        return ans;
    }

    Perm operator * (const Perm &other)const {
        assert(other.perm.size() == this->perm.size());
        Perm ans(this->perm,false);

        for(int i = 1; i < (int)other.perm.size(); i++) {
            ans.perm[i] = this->perm[other.perm[i]];
        }

        return ans;
    }

    static Perm identity(const int order) {
        vector<int> v;
        for(int i = 0; i <= order; i++) {
            v.push_back(i);
        }
        Perm ans(v,false);
        for(int i = 1; i <= order; i++) {
            ans.cycle_decomp.push_back({i});
        }
        return ans;
    }

    Perm operator ^ (const long long &exp) {
        if(exp < 0) {
            return(this->inverse()) ^ (-exp);
        }
        else if(exp == 0) {
            return Perm::identity((int)this->perm.size() - 1);
        }

        if((int)cycle_decomp.size() == 0) {
            this->get_decomp();
        }

        Perm ans(this->perm,false);

        for(auto cycle:cycle_decomp) {
            for(int i = 0; i < (int)cycle.size(); i++) {
                ans.perm[cycle[i]] = this->perm[cycle[(i + exp - 1) % int(cycle.size())]];
            }
        }

        return ans;
    }

    void afis()const {
        for(int i = 1; i < (int)perm.size(); i++) {
            fprintf(g,"%d ",perm[i]);
        }
        fprintf(g,"\n");
    }
};

int n;
long long x,y;

long long ext_gcd(long long x,long long y,long long &a,long long &b) {
    if(y == 0) {
        a = 1;
        b = 0;
        return x;
    }

    long long ans = ext_gcd(y,x % y,a,b);
    long long n_a = b;
    long long n_b = a - b * (x / y);

    a = n_a;
    b = n_b;

    return ans;
}

const int LEN = 1 << 13;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

long long i64() {
    long long ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int main() {

    n = i32();
    x = i64();
    y = i64();

    vector<int> c(n + 1,0),d(n + 1,0);

    for(int i = 1; i <= n; i++) {
        c[i] = i32();
    }
    for(int i = 1; i <= n; i++) {
        d[i] = i32();
    }

    Perm s(c),t(d);

    long long a = 0,b = 0;

    ext_gcd(x,y,a,b);

    Perm ans = (s ^ a) * (t ^ b);

    ans.afis();

    fclose(f);
    fclose(g);

    return 0;
}
