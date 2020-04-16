#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("aliniere.in","r");
FILE *g = fopen("aliniere.out","w");

const int NMAX = 1e5;
const int QMAX = 1e4;

const int LEN = 1 << 14;
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

int n,q;
int v[NMAX + 5];
int lft[NMAX + 5];

int main() {

    n = i32();

    lft[0] = 1;

    for(int i = 1; i <= n; i++) {
        v[i] = i32();
        lft[i] = (v[i] < v[i - 1] ? i:lft[i - 1]);
    }

    q = i32();

    while(q--) {
        int len;
        len = i32();
        vector<pair<int,int> > groups;

        int lst = 1;

        for(int i = 1; i <= len; i++) {
            int pos = i32() + 1;
            if(lft[pos] <= lst) {
                groups.push_back({v[lst],v[pos]});
            }
            lst = pos + 1;
        }
        if(lst <= n) {
            if(lft[n] <= lst) {
                groups.push_back({v[lst],v[n]});
            }
            lst = n + 1;
            len++;
        }

        sort(groups.begin(),groups.end(),[&](const pair<int,int> &a,const pair<int,int> &b) {
            if(a.second != b.second)return a.second < b.second;
            return a.first < b.first;
        });
        lst = 0;

        int cnt = 0;
        for(auto it:groups) {
            if(it.first >= lst) {
                lst = it.second;
                cnt++;
            }
        }

        fprintf(g,"%d\n",len - cnt);
    }

    fclose(f);
    fclose(g);

    return 0;
}
