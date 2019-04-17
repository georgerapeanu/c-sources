#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int a[20];

void get1(int pos,int fst,int num,vector<int> &v) {
    if(pos < 1) {
        if(fst != 0) {
            v.push_back(num);
        }
        return ;
    }

    if(fst == 0) {
        get1(pos - 1,fst,num,v);
    }

    for(int cf = 0; cf <= 9; cf++) {
        if(fst != 0) {
            if(cf == a[pos + 1]) {
                continue;
            }
            if(fst == pos + 1) {
                a[pos] = cf;
                get1(pos - 1,fst,num * 10 + cf,v);
            }
            else if((a[pos + 2] - a[pos + 1]) * (cf - a[pos + 1]) > 0) {
                a[pos] = cf;
                get1(pos - 1,fst,num * 10 + cf,v);
            }
        }
        else if(cf > 0) {
            a[pos] = cf;
            get1(pos - 1,pos,cf,v);
        }
    }

}

const int NMAX = 1e6;
vector<pair<long long,int> > sons[2];

int main() {
    vector <int> v;
    get1(7,0,0,v);

    long long n,k;

    scanf("%lld %lld",&n,&k);

    for(auto it:v) {
        if(it % n == 0) {
            k--;
            if(k == 0) {
                printf("%d\n",it);
                return 0;
            }
        }
    }
    for(auto it:v) {
        if(it >= 1e6) {
            if((it / 1000000) > (it / 100000) % 10) {
                sons[1].push_back({it % n,it});
            }
            else {
                sons[0].push_back({it % n,it});
            }
        }
        else if(it >= 1e5) { ///0x
            if(it / (100000) > (it / 10000) % 10) {
                sons[0].push_back({it % n,it});
            }
        }
    }

    sort(sons[0].begin(),sons[0].end());
    sort(sons[1].begin(),sons[1].end());

    for(auto it:v) {
        int fst = it;
        vector<int> sgn;
        if(it < 10) {
            sgn.push_back(1);
            sgn.push_back(0);
        }
        else {
            sgn.push_back(!(((it / 10) % 10) > (it % 10)));
        }

        long long r = (n - (1LL * it * 10000000 % n)) % n;

        for(auto wut:sgn) {
            vector<pair<long long,int> > :: iterator st = lower_bound(sons[!wut].begin(),sons[!wut].end(),make_pair(r,0));
            vector<pair<long long,int> > :: iterator dr = lower_bound(sons[!wut].begin(),sons[!wut].end(),make_pair(r + 1,0));
            ///[st,dr)
            if(wut == 0) { /// < at join so > first sgn
                vector<pair<long long,int> > :: iterator it2 = lower_bound(st,dr,make_pair(r,((it % 10) + 1) * 1000000));
                st = it2;
            }
            else {
                vector<pair<long long,int> > :: iterator it2 = lower_bound(st,dr,make_pair(r,(it % 10) * 1000000));
                dr = it2;
            }

            if(dr - st >= k) {
                while(st != dr) {
                    k--;
                    if(k == 0) {
                        printf("%lld\n",it * 10000000LL + st->second);
                        return 0;
                    }
                    st++;
                }
            }
            else {
                k -= (dr - st);
            }
        }

    }

    printf("-1\n");

    return 0;
}

