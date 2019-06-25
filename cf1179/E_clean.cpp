#include <bits/stdc++.h>

using namespace std;

const long long NMAX = 1000;

pair<long long,long long> func[NMAX + 5];
pair<long long,long long> tmp_func[NMAX + 5];
long long initial[NMAX + 5];
pair<long long,long long> ans[NMAX + 5];

map<pair<long long,long long>,long long> memo;

long long singular_query(long long id,long long wh) {
    if(memo.count({id,wh}) == 0) {
        cout << "? " << id << " " << wh << endl;
        cin >> memo[ {id,wh}];
    }
    return memo[ {id,wh}];
}

void query_fun(long long fst,long long lst,long long wh) {
    for(long long i = fst; i <= lst; i++) {
        func[i].first = singular_query(func[i].second,wh);
    }
}

void solve(long long fst,long long lst,long long l,long long r,long long buck) {
    if(fst == lst) {
        ans[func[fst].second] = {l,r};
        return ;
    }

    long long target_split = (lst + fst) / 2;
    long long st = l + 1LL * (target_split - fst + 1) * buck - 1,dr = r - 1LL * (lst - target_split) * buck + 1;

    while(dr - st > 1) {
        long long mid = (st + dr) / 2;

        for(long long i = fst; i <= lst; i++) {
            map<pair<long long,long long>,long long> :: iterator it = memo.lower_bound({func[i].second,mid});
            if(it != memo.end() && it->first.first == func[i].second && it->second - initial[func[i].second] < buck * (target_split - fst + 1)) {
                func[i].first = it->second;
            }
            else if(it != memo.begin()) {
                it--;
                if(it->first.first == func[i].second && it->second - initial[func[i].second] >= buck * (target_split - fst + 1)) {
                    func[i].first = it->second;
                }
                else {
                    func[i].first = singular_query(func[i].second,mid);
                }
            }
            else {
                func[i].first = singular_query(func[i].second,mid);
            }
        }

        sort(func + fst,func + 1 + lst,[&](pair<long long,long long> &a,pair<long long,long long> &b) {
            return a.first - initial[a.second] > b.first - initial[b.second];
        });

        if(func[target_split].first - initial[func[target_split].second] >= buck * (target_split - fst + 1)) { ///since it is prefix query,it should be compared to prefix
            dr = mid;
            for(long long i = fst; i <= lst; i++) {
                tmp_func[i] = func[i];
            }
        }
        else {
            st = mid;
        }
    }

    for(long long i = fst; i <= lst; i++) {
        func[i] = tmp_func[i];
    }

    for(int i = target_split + 1; i <= lst; i++) {
        initial[func[i].second] += buck * (target_split - fst + 1);
    }

    solve(fst,target_split,l,dr,buck);
    solve(target_split + 1,lst,dr,r,buck);
}

int main() {

    long long n;
    long long l;

    scanf("%lld %lld",&n,&l);

    for(long long i = 1; i <= n; i++) {
        func[i] = {0,i};
        memo[ {i,0}] = 0;
        memo[ {i,1e18}] = l;
    }

    solve(1,n,0,1e18,l / n);

    cout << "!" << endl;
    for(long long i = 1; i <= n; i++) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }

    return 0;
}
