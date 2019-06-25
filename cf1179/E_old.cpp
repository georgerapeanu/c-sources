#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000;

pair<int,int> func[NMAX + 5];
pair<int,int> tmp_func[NMAX + 5];
int initial[NMAX + 5];
pair<long long,long long> ans[NMAX + 5];

map<pair<int,long long>,int> memo;

int singular_query(int id,long long wh) {
    if(memo.count({id,wh}) == 0) {
        cout << "? " << id << " " << wh << endl;
        cin >> memo[ {id,wh}];
    }
    return memo[ {id,wh}];
}

void query_fun(int fst,int lst,long long wh) {
    for(int i = fst; i <= lst; i++) {
        func[i].first = singular_query(func[i].second,wh);
    }
}

///intervals should be (l,r]
void solve(int fst,int lst,long long l,long long r,int buck) {
//    printf("entered %d %d %lld %lld %d\n",fst,lst,l,r,buck);
    if(fst == lst) {
        ans[func[fst].second] = {l,r};
        return ;
    }

    int target_split = (lst + fst) / 2;///[fst,target_split] to the left
    long long st = l + 1LL * (target_split - fst + 1) * buck - 1,dr = r - 1LL * (lst - target_split) * buck + 1;

    while(dr - st > 1) {
//        printf("entered search %lld %lld\n",st,dr);
        long long mid = (st + dr) / 2;

        query_fun(fst,lst,mid);
        sort(func + fst,func + 1 + lst,[&](pair<int,int> &a,pair<int,int> &b) {
            return a.first - initial[a.second] > b.first - initial[b.second];
        });

        if(func[target_split].first - initial[func[target_split].second] >= buck * (target_split - fst + 1)) { ///since it is prefix query,it should be compared to prefix
            dr = mid;
            for(int i = fst; i <= lst; i++) {
                tmp_func[i] = func[i];
            }
        }
        else {
            st = mid;
        }
    }

    for(int i = fst; i <= lst; i++) {
        func[i] = tmp_func[i];
    }

//    printf("partition made %d %lld\n",target_split,dr);

    for(int i = target_split + 1; i <= lst; i++) {
        initial[func[i].second] += buck * (target_split - fst + 1);
    }

    solve(fst,target_split,l,dr,buck);
    solve(target_split + 1,lst,dr,r,buck);
}

int main() {

    int n,l;

    scanf("%d %d",&n,&l);

    for(int i = 1; i <= n; i++) {
        func[i] = {0,i};
        memo[ {i,0}] = 0;
        memo[ {i,1e18}] = 0;
    }

    solve(1,n,0,1e18,l / n);///modify this for submision

    cout << "!" << endl;
    for(int i = 1; i <= n; i++) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }

    return 0;
}
