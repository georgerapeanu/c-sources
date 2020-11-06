#include <bits/stdc++.h>
#include "wbtree.h"

using namespace std;

const int NMAX = 20;

int n;
vector<int> graph[NMAX + 5];
vector<int> subarbore[NMAX + 5];
int k;
int cnt[NMAX + 5];
vector<bitset<NMAX + 5> > v;
bitset<NMAX + 5> tmp;
bitset<NMAX + 5> full[NMAX + 5];

void predfs(int nod,int tata){
    subarbore[nod] = {nod};
    full[nod].set(nod);
    bool special_son = false;
    bool special = (cnt[nod] == 1);
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        predfs(it,nod);
        special_son |= (cnt[it] > 0);
        cnt[nod] += cnt[it];
        full[nod] |= full[it];
        for(auto it2:subarbore[it]){
            subarbore[nod].push_back(it2);
        }
    }
    bitset<NMAX + 5> rest = full[nod];
    for(int i = 1;i <= n;i++){
        rest.flip(i);
    }
    if(special){
        bitset<NMAX + 5> tmp = rest | full[nod];
        v.push_back(tmp);
    }
    if(special_son){
        v.push_back(rest);
//        cout << "added " << v.back() << "at 37 " << nod << endl;
    }
    if(cnt[nod] != k){
        v.push_back(full[nod]);
//        cout << "added " << v.back() << "at 41 " << nod << endl;
    }

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        if(cnt[it] != 0){
            v.push_back((full[nod] | rest) ^ full[it]);
//            cout << "added " << v.back() << "at  50" << nod << endl;
        }
    }
}

bool cmp(bitset<NMAX + 5> a,bitset<NMAX + 5> b){
    return a.to_string() < b.to_string();
}

int solve(int N, std::vector<int> p, std::vector<int> q, std::vector<int> r) {
    n = N;
    for(int i = 0;i < N - 1;i++){
        p[i]++;q[i]++;
        graph[p[i]].push_back(q[i]);
        graph[q[i]].push_back(p[i]);
    }
    k = (int)r.size();
    for(auto it:r){
        it++;
        cnt[it] = 1;
    }

    predfs(1,0);

    bitset<NMAX + 5> tmp;

    vector<bitset<NMAX + 5> > s = {tmp};
    
    for(auto it:v){
        vector<bitset<NMAX + 5> > tmp;
        for(auto it2:s){
            if((it & it2).count() == 0){
                tmp.push_back(it | it2);
            }
        }
        for(auto it2:tmp){
  //          cout << "adds " << it2 << "\n";
            s.push_back(it2);
        }
        sort(s.begin(),s.end(),cmp);
        tmp.clear();
        for(int i = 0;i < (int)s.size();i++){
            if(i == 0 || cmp(s[i - 1],s[i]) == 1){
                tmp.push_back(s[i]);
            }
        }
        s = tmp;
    }
//    for(auto it:s)cout << it << " ";cout << "\n";

    return (int)s.size();

}
