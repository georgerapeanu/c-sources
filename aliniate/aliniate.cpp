#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("aliniate.in","r");
FILE *g = fopen("aliniate.out","w");

typedef unsigned int ui;
const ui LGMAX = 32;

int t,n;


const int LEN = 1 << 15;
char buff[LEN];
int ind = LEN - 1;


ui u32() {
    ui ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(buff[ind] >= '0' && buff[ind] <= '9') {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

inline ui trail(ui val) {
    if(val == 0) {
        return LGMAX;
    }
    ui ans = 0;
    while(val % 2 == 0) {
        val >>= 1;
        ans++;
    }
    return ans;
}

struct data_t {
    ui val;
    bool has_empty;

    data_t() {
        val = 1;
        has_empty = true;
    }

    data_t(ui val) {
        this->val = val;
        this->has_empty = false;
    }

    data_t operator * (const data_t &other)const {
        data_t ans;
        ans.val = this->val * other.val;
        ans.has_empty = (this->has_empty | other.has_empty);
        return ans;
    }

    bool operator == (const data_t &other)const {
        return this->val == other.val;
    }

    bool operator != (const data_t &other)const {
        return this->val != other.val;
    }

    bool can_trans(const data_t &other)const {
        if(this->has_empty) {
            return trail(this-> val) <= trail(other.val);
        }
        return this->val == other.val;
    }

    bool operator < (const data_t &other)const {
        return this->has_empty < other.has_empty;
        if(this->val != other.val) {
            return this->val < other.val;
        }
    }
};

vector<pair<ui,data_t> > stuff[LGMAX + 1];

int main() {

    t = u32();

    while(t--) {

        for(ui h = 0; h <= LGMAX; h++) {
            stuff[h].clear();
        }

        n = u32();
        bool ok = true;
        for(int i = 1; i <= n; i++) {
            ui x,y,z;
            x = u32();
            y = u32();
            z = u32();
            stuff[trail(y - x + 1)].push_back({x,data_t(z)});
        }

        for(ui h = 0; h < LGMAX; h++) {
            sort(stuff[h].begin(),stuff[h].end());
            int len = 1;
            for(int i = 1; i < (int)stuff[h].size(); i++) {
                if(stuff[h][len - 1].first != stuff[h][i].first) {
                    stuff[h][len++] = stuff[h][i];
                }
                if(stuff[h][i].second.can_trans(stuff[h][len - 1].second) == false) {
                    ok = false;
                    goto done1;
                }
            }
            stuff[h].resize(len);

            for(int i = 0; i < (int)stuff[h].size(); i++) {
                if((stuff[h][i].first >> h) & 1) {
                    if(i != 0 && stuff[h][i].first - stuff[h][i - 1].first == (((ui)1) << h)) {
                        stuff[h + 1].push_back({stuff[h][i].first - ((ui)1 << h),stuff[h][i - 1].second * stuff[h][i].second});
                    }
                    else {
                        stuff[h + 1].push_back({stuff[h][i].first - ((ui)1 << h),data_t() * stuff[h][i].second});
                    }
                }
                else {
                    if(i < (int)stuff[h].size() - 1 && stuff[h][i + 1].first - stuff[h][i].first == (((ui)1) << h)) {
                        stuff[h + 1].push_back({stuff[h][i].first,stuff[h][i].second * stuff[h][i + 1].second});
                    }
                    else {
                        stuff[h + 1].push_back({stuff[h][i].first,stuff[h][i].second * data_t()});
                    }
                }
            }
        }

done1:
        ;

        fprintf(g,"%d\n",ok);
    }

    fclose(f);
    fclose(g);

    return 0;
}
