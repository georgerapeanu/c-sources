#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("dragonball.in","r");
FILE *g = fopen("dragonball.out","w");

typedef long long ll;
const ll BASE = 1e14;
const int LGMAX = 800;

class Bignum {
public:
    ll cf[LGMAX];
    int lst_cf;

    Bignum() {
        lst_cf = 0;
    }

    void build(char *a) {
        lst_cf = 0;
        ll num = 0;
        int len = 0;

        while(*(a + len) != '\0' && *(a + len) != '\n') {
            len++;
        }

        ll p10 = 1;

        while(len > 0) {
            len--;
            if(p10 >= BASE) {
                p10 = 1;
                cf[lst_cf++] = num;
                num = 0;
            }
            num += p10 * (*(a + len) - '0');
            p10 *= 10;
        }

        if(num > 0 || lst_cf == 0) {
            cf[lst_cf++] = num;
        }
    }

    Bignum operator / (int val) {
        Bignum ans;
        ans.lst_cf = this->lst_cf;
        ll t = 0;

        for(int i = lst_cf - 1; i >= 0; i--) {
            t += cf[i];
            ans.cf[i] = (t / val);
            t %= val;
            t *= BASE;
        }

        t = (t > 0);

        for(int i = 0; t; i++) {
            t += ans.cf[i];
            ans.cf[i] = t % BASE;
            t /= BASE;
        }

        while(ans.lst_cf > 1 && ans.cf[ans.lst_cf - 1] == 0) {
            ans.lst_cf--;
        }
        return ans;
    }

    Bignum operator - (Bignum &other) {
        Bignum ans;
        ans.lst_cf = 0;

        int t = 0;

        for(int i = 0; i < lst_cf; i++) {
            ans.cf[ans.lst_cf++] = (t + cf[i] - other.cf[i]);
            if(ans.cf[ans.lst_cf - 1] < 0) {
                ans.cf[ans.lst_cf - 1] += BASE;
                t = -1;
            }
            else {
                t = 0;
            }
        }
        while(ans.lst_cf > 1 && ans.cf[ans.lst_cf - 1] == 0) {
            ans.lst_cf--;
        }
        return ans;
    }

    bool operator < (const Bignum &other)const {
        if(this->lst_cf != other.lst_cf) {
            return this->lst_cf < other.lst_cf;
        }
        int len = this->lst_cf - 1;
        while(len >= 0 && this->cf[len] == other.cf[len]) {
            len--;
        }
        if(len < 0) {
            return 0;
        }
        return this->cf[len] < other.cf[len];

    }

    void afis() {
        fprintf(g,"%lld",cf[lst_cf - 1]);
        for(int i = lst_cf - 2; i >= 0; i--) {
            ll cb = BASE / 10;
            while(cb > 1 && cb > cf[i]) {
                fprintf(g,"0");
                cb /= 10;
            }
            fprintf(g,"%lld",cf[i]);
        }
        fprintf(g,"\n");
    }

};

int n,t;

char tmp[10005];

Bignum stuff[1005];

Bignum residue[1005];
int cnt[1005];
int heap[1005];

int len = 0;

void heappush(int id) {
    len++;

    heap[len] = id;
    residue[id] = stuff[id] / cnt[id];

    int idx = len;
    while(idx > 1 && residue[heap[idx / 2]] < residue[heap[idx]]) {
        swap(heap[idx],heap[idx / 2]);
        idx /= 2;
    }
}

int heappop() {
    int ans = heap[1];

    swap(heap[1],heap[len]);
    len--;

    int idx = 1;

    while(idx * 2 <= len) {
        if(idx * 2 + 1 > len) {
            if(residue[heap[idx * 2]] < residue[heap[idx]]) {
                break;
            }
            swap(heap[idx * 2],heap[idx]);
            idx *= 2;
            continue;
        }
        if(residue[heap[idx * 2]] < residue[heap[idx]] && residue[heap[idx * 2 + 1]] < residue[heap[idx]]) {
            break;
        }
        if(residue[heap[idx * 2]] < residue[heap[idx * 2 + 1]]) {
            swap(heap[idx * 2 + 1],heap[idx]);
            idx = idx * 2 + 1;
        }
        else {
            swap(heap[idx * 2],heap[idx]);
            idx = idx * 2;
        }
    }
    return ans;
}

int main() {

    fscanf(f,"%d %d %s\n",&n,&t,tmp);
    stuff[++n].build(tmp);

    for(int i = 1; i < n; i++) {
        fscanf(f,"%s\n",tmp);
        stuff[i].build(tmp);
    }

    for(int i = n; i > 1; i--) {
        stuff[i] = stuff[i] - stuff[i - 1];
    }

    for(int i = 1; i <= n; i++) {
        cnt[i] = 1;
        heappush(i);
        //    heapafis();
    }

    while(t--) {
        int tmp = heappop();
//       tmp.first.first.afis();
//        printf("%d\n",tmp.second);

        cnt[tmp]++;
        heappush(tmp);
    }

    int ans = heappop();

    residue[ans].afis();

    fclose(f);
    fclose(g);

    return 0;

}
