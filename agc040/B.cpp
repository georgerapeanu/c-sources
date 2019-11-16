#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

long long n;
pair<pair<long long,long long >,long long> segm[NMAX + 5];
pair<long long,long long> sect;
pair<long long,long long> suff_sect[NMAX + 5];

int main() {

    long long ans = 0;

    scanf("%lld",&n);

    sect = {0,1e9 + 5};

    for(int i = 1; i <= n; i++) {
        scanf("%lld %lld",&segm[i].first.first,&segm[i].first.second);
        sect.first = max(sect.first,segm[i].first.first);
        sect.second = min(sect.second,segm[i].first.second);
    }

    if(sect.first <= sect.second) {
        ans += 2 * (sect.second - sect.first + 1);
        long long max_len = 0;
        for(int i = 1; i <= n; i++) {
            max_len = max(max_len,segm[i].first.second - segm[i].first.first + 1);
        }
        for(int i = 1; i <= n; i++) {
            segm[i].first.second -= (sect.second - sect.first + 1);
            if(segm[i].first.second < segm[i].first.first) {
                printf("%lld\n",ans - (sect.second - sect.first + 1) + max_len);
                return 0;
            }
        }
    }

    vector<long long> posx;
    pair<long long,long long> fst = {1e9 + 5,1e9 + 5};

    for(int i = 1; i <= n; i++) {
        posx.push_back(segm[i].first.first);
        posx.push_back(segm[i].first.second);
        fst.first = min(fst.first,segm[i].first.first);
        fst.second = min(fst.second,segm[i].first.second);
    }

    sort(posx.begin(),posx.end());
    posx.resize(unique(posx.begin(),posx.end()) - posx.begin());

    for(int i = 0; i < (int)posx.size(); i++) {
        segm[++n] = {{posx[i],fst.second},1};
        if(posx[i] == fst.second) {
            break;
        }
    }

    sort(segm + 1,segm + 1 + n,
    [&](pair<pair<long long,long long>,long long> &a,pair<pair<long long,long long>,long long> &b) {
        if(a.first.first != b.first.first) {
            return a.first.first < b.first.first;
        }
        if(a.first.second != b.first.second) {
            return a.first.second > b.first.second;
        }
        return a.second < b.second;
    });

    suff_sect[n + 1] = {0,1e9 + 5};

    for(int i = n; i; i--) {
        if(segm[i].second == 1) {
            suff_sect[i] = suff_sect[i + 1];
            continue;
        }
        suff_sect[i].first = max(suff_sect[i + 1].first,segm[i].first.first);
        suff_sect[i].second = min(suff_sect[i + 1].second,segm[i].first.second);
    }

    long long max_len = 0;
    for(int i = 1; i <= n; i++) {
        max_len = max(max_len,segm[i].first.second - segm[i].first.first + 1);
    }

    long long tmp_ans = max_len;
    for(int i = 1; i <= n; i++) {
        if(segm[i].second == 1 && (suff_sect[i + 1].first != 0 || suff_sect[i + 1].second != 1e9 + 5)) {
            tmp_ans = max(tmp_ans,segm[i].first.second - segm[i].first.first + 1 + max(0LL,suff_sect[i + 1].second - suff_sect[i + 1].first + 1));
        }
    }

    ans += tmp_ans;

    printf("%lld\n",ans);

    return 0;
}
