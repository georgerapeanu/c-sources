#include "islands.h"
#include <cstdio>

using namespace std;

const int MAXC = 499;
const int NMAX = 1e4;

int n;
int query_batch[NMAX + 5];
bool taken[NMAX + 5];
vector<vector<int> > post_pairup;

vector<vector<int> > a;
vector<vector<int> > b;

int active_batch = 0;

void flush_pairup(){
    if(a.empty()){
        return ;
    }
    vector<int> leftover;
    for(int i = 0;i < n;i++){
        if(taken[i] == false){
            leftover.push_back(i);
        }
        taken[i] = false;
    }
    if((int)leftover.size() > 0){
        a.push_back(leftover);
    }
    b = ask(a);
    post_pairup.push_back(vector<int>(n,-2));
    for(auto pairup:b){
        if((int)pairup.size() == 2){
            post_pairup.back()[pairup[0]] = pairup[1];
            post_pairup.back()[pairup[1]] = pairup[0];
        }else if((int)pairup.size() == 1){
            post_pairup.back()[pairup[0]] = -1;
        }
    }
    active_batch++;
    a.clear();
}

void add_pairup(int x,int y){
    query_batch[x] = active_batch;
    if(y >= n){
        a.push_back({x});
        taken[x] = true;
    }else{
        a.push_back({x,y});
        taken[x] = taken[y] = true;
    }
    if(a.size() >= MAXC){
        flush_pairup();
    }
}

vector<int> solve(int N){
    n = N;
    vector<int> p(n,-1);
    
    for(int i = 0;i < n;i += 2){
        add_pairup(i,i + 1);
    }
    flush_pairup();

    for(int i = 1;i < n;i += 2){
        add_pairup(i,i + 1);
    }
    flush_pairup();

    a = {{0},{}};
    for(int i = 1;i < n;i++){
        a.back().push_back(i);
    }
    b = ask(a);
    if(b[0].size() > b[1].size()){
        swap(b[0],b[1]);
    }
    p[0] = b[0][0];


    for(int i = 0;i < n - 1;i++){
        int id = query_batch[i];
        p[i + 1] = post_pairup[id][p[i]];
    }
    
    return p;
}
